#ifndef PRO_CPU
#define PRO_CPU 0
#endif
#ifndef APP_CPU
#define APP_CPU 1
#endif

#define ARDUINO 1

#define DEBUG 1
#ifdef DEBUG
#define IFD(x) x
#else
#define IFD(x)
#endif



void 
#ifdef ARDUINO
setup
#else
app_main
#endif(void){
    IFD(Serial.begin(115200));
}