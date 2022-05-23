// this file is heavily adapted off of https://gist.github.com/arvidtp/d0ab689a5c2821a45c31103d7a3e256a
// the library used is here: https://github.com/jrowberg/i2cdevlib/tree/master
// the "motionapps" thing is mostly useful only if one cares about rotating the acceleration vector correctly.
// we just work off the magnitude of the aceleration because it means we save some power by not using the gyro, and more false positives but that's ok.

#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high

// hook up sda to 19, scl to 22, int to 27

// uncomment "OUTPUT_READABLE_REALACCEL" if you want to see acceleration
// components with gravity removed. This acceleration reference frame is
// not compensated for orientation, so +X is always +X according to the
// sensor, just without the effects of gravity. If you want acceleration
// compensated for orientation, us OUTPUT_READABLE_WORLDACCEL instead.
#define OUTPUT_READABLE_REALACCEL

// uncomment "OUTPUT_READABLE_WORLDACCEL" if you want to see acceleration
// components with gravity removed and adjusted for the world frame of
// reference (yaw is relative to initial orientation, since no magnetometer
// is present in this case). Could be quite handy in some cases.
#define OUTPUT_READABLE_WORLDACCEL

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// ==================================================

static int i2cCore = 1;

#define INTERRUPT_PIN_MPU 27

volatile bool mpuDataReady = false;
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

volatile int mpuDataCounter = 0;
int mpuDataCounterPrev = 0;

uint8_t zrmot_int_count = 0;

// ================================================================
// ===                INTERRUPT SERVICE ROUTINES                ===
// ================================================================

void IRAM_ATTR dmpDataReady() {
  mpuInterrupt = true;
  // set whether a zero motion or a free fall was detected
  
}

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
  // initialize serial communication

  Serial.begin(115200);

  delay(100);

  Serial.print("Creating i2c task on core ");
  Serial.println(i2cCore);
  xTaskCreatePinnedToCore(
    sensorTask,   /* Function to implement the task */
    "coreTask", /* Name of the task */
    10000,      /* Stack size in words */
    NULL,       /* Task input parameter */
    20,          /* Priority of the task */
    NULL,       /* Task handle. */
    i2cCore);  /* Core where the task should run */

  Serial.println("i2c task created.");
}


// ================================================================
// ===              I2C SENSOR READ TASK (CORE 0)               ===
// ================================================================

void imu_startup() {
  // below are calibrated using MPU6050_raw from the i2cdev library
  // also instructions here help: https://www.i2cdevlib.com/forums/topic/91-how-to-decide-gyro-and-accelerometer-offsett/?do=findComment&comment=257
  mpu.setXAccelOffset(-2730);
  mpu.setYAccelOffset(-35);
  mpu.setZAccelOffset(700);
  // empirically, after compensating for orientation (requires gyro though) anything with absolute value <1500 is "at rest"

  mpu.setMotionDetectionThreshold(7500); // LSB=2mg
  mpu.setMotionDetectionDuration(2); // so you get an interrupt when falling LSB=1ms
  mpu.setMotionDetectionCounterDecrement(2); // when a sample does not count as falling how much to penalise the counter for this

  mpu.setZeroMotionDetectionThreshold(7500); // LSB=2mg
  mpu.setZeroMotionDetectionDuration(255); // maximum interval, get an int after 16320 ms.  LSB=64 ms

  //disable unused gyro with setStandbyXGyroEnabled(false) & Y&Z, register map says there's power optimisation like this
  mpu.setStandbyXGyroEnabled(false);
  mpu.setStandbyYGyroEnabled(false);
  mpu.setStandbyZGyroEnabled(false);
  
  mpu.setInterruptMode(0); // aka active high
  mpu.setInterruptLatch(1); // latch rather than pulse
  mpu.setInterruptLatchClear(0); // so reading INT_STATUS clears the interrupt
  mpu.setIntDataReadyEnabled(false); // in our case we are not interested in raw data so don't bother
  mpu.setIntFIFOBufferOverflowEnabled(false); // again, not reading raw data so this doesn't matter
  mpu.setTempSensorEnabled(false); // unused and needs to be disabled for accelerator only low power mode

  mpu.setIntZeroMotionEnabled(false);
  mpu.setIntMotionEnabled(false);
  mpu.setIntFreefallEnabled(false);
}

void imu_full_on() {
  mpu.setIntZeroMotionEnabled(true);
  mpu.setIntMotionEnabled(true);
  mpu.setWakeCycleEnabled(false);
  mpu.setSleepEnabled(false);
  
}

void sensorTask( void * pvParameters ) {

  // ================== SETUP ==================

  delay(100);

  String taskMessage = "sensorTask running on core ";
  taskMessage = taskMessage + xPortGetCoreID();

  Serial.println(taskMessage);

  // join I2C bus (I2Cdev library doesn't do this automatically)

  Wire.begin(19, 22);
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  //      Wire.setClock(100000); // 100kHz I2C clock. Comment this line if having compilation difficulties

  delay(1000);

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();

  delay(100);

  pinMode(INTERRUPT_PIN_MPU, INPUT);

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // wait for ready
  //    Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  //    while (Serial.available() && Serial.read()); // empty buffer
  //    while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again

  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();



  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    delay(5000);
    imu_startup(); // our own setup for the imu

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_MPU), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }

  while (true) {
    delay(100);
  }

} // end sensorTask

void loop() {
  delay(2000);
  int16_t ax = mpu.getAccelerationX();
  int16_t ay = mpu.getAccelerationY();
  int16_t az = mpu.getAccelerationZ();
  float a_abs = sqrt(pow((float)ax,2)+pow((float)ay,2)+pow((float)az,2));
  Serial.print("curr accel x: ");
  Serial.print(mpu.getAccelerationX());
  Serial.print(", y: ");
  Serial.print(mpu.getAccelerationY());
  Serial.print(", z: ");
  Serial.print(mpu.getAccelerationZ());
  Serial.print(", abs: ");
  Serial.println(a_abs);
  
  // if programming failed, don't try to do anything
  if (!dmpReady) {
    Serial.println("dmpNotReady");
    delay(100);
  }

  if (mpuInterrupt) {
    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
    Serial.print("interrupt received: 0x");
    Serial.println((uint8_t)mpuIntStatus, HEX);

    if (mpuIntStatus & (1<<MPU6050_INTERRUPT_MOT_BIT)) {
      // motion detect occurred
      Serial.println("Detected motion, wake up");
    }
    
    if (mpuIntStatus & (1<<MPU6050_INTERRUPT_ZMOT_BIT)) {
      // zero motion detect
      // note: this interrupt also occurs when motion occurs after there having been no motion
      // to disambiguate the two, use getZeroMotionDetected which gets bit 0 of MOT_DETECT_STATUS
      // motion to no motion is a 1, no motion to motion is a 0
      bool now_no_motion = mpu.getZeroMotionDetected();
      if (now_no_motion) {
        zrmot_int_count++;
        Serial.println("got another zeromotion");
        // if wating for 2 s of continuous no activity, then with 16320 ms per zero motion interrupt it's ~2 interrupts
        if (zrmot_int_count>2) {
          zrmot_int_count=0;
          Serial.println("Switch to lower power state");
        }
      } else {
        zrmot_int_count=0;
        // I was woken up
        Serial.println("I'm awoken");
      }
    }
  }
}
