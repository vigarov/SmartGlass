---
permalink: /project-proposal/
title: "Project Proposal"
toc: true
toc_sticky: true
---

# I. Description

The main idea of this project is to make smart glasses. To keep things simple, only one of the eyes will have a screen/act as a graphic interface for the user. What would’ve been the glasses’ frames will be expanded to fit in electronics and batteries. A general sketch of the desired outcome would be the following: 

General idea for the design of the glasses :


![Basic sketch of a face wearing glasses, on which are designated the areas we'd put electronics, support structures and the screen itself]({{ site.url }}{{ site.baseurl }}/assets/images/basic_face_sketch.jpg)

Example user view of the display (96x64 pixels in the frame) and icon examples


![Small header menu showing the status of the device : battery, bluetooth connection, notifications, and time]({{ site.url }}{{ site.baseurl }}/assets/images/menu.png)

Realistically we need separate views for the following sections: status, Bluetooth signal strength, details from the GNSS module like altitude/lon/lat/velocity, notifications, basic time display, show destination address for directions feature, direction view with distance to next turn+ ideally road name.



The current goals established discussed with and approved by Federico and the whole group are:



* Getting status and notifications from an Android device
* Letting a user input a destination on the Android application, and then displaying directions on the glasses (similar to google maps notifications) 
* Finding your phone. This can be done using the bluetooth transmitter on the phone as a beacon and analysing the signal’s strength
* Detecting whether a person has fallen and is unable to get up

The current optional goals are:


* Using the ESP32’s WiFi and GNSS to make “find my glasses”.  This would work basically identically to how the usual Android device manager or the like work, so a small publicly routable webserver collects the location and pushes commands to the ESP32.
* Incorporating offline maps navigation on smaller areas (such as restricting it to the EPFL campus), by having locally cached information if the phone “turns off” after a navigation has started.

Unlike the previous revision of the proposal, we have struck the camera because we already have enough on our plate.

Basic implementation strategy :


<table>
  <tr>
   <td>Application
   </td>
   <td>Implementation
   </td>
  </tr>
  <tr>
   <td>Notifications
   </td>
   <td>
    <p>Bluetooth connection between device and phone <br>
Upon new notifications, the Android application triggers and sends the notification to the glasses.  To conserve battery life, if doing the advanced power management optional goal we can set the glasses to modem-sleep, and the Bluetooth wakes up periodically to check for notifications.  This is ok because most notifications are not urgent. </p>
   </td>
  </tr>
  <tr>
   <td>Maps directions
   </td>
   <td>The glasses’ GPS module collects the current location, the phone forwards this to Google’s directions API and returns directions to the glasses. 
   </td>
  </tr>
  <tr>
   <td>Finding phone
   </td>
   <td>Bluetooth transmitter on the phone acts as a beacon and the ESP32 picks up the signal’s strength
   </td>
  </tr>
  <tr>
   <td>Falling person
   </td>
   <td>Analysing an accelerometer’s readings, and alerting the connected Android app.
   </td>
  </tr>
  <tr>
   <td>Optional : Finding glasses
   </td>
   <td>Project goal: use a similar approach to the “finding phone” in the other way.  The phone picks up the Bluetooth signal strength from the glasses’ transmitter.
<p>
Optional goal, and similar to the Android device manager : a small publicly routable web server collecting the location (collected from the esp32’s wifi and gnss) and pushes commands to the ESP32. </p>
   </td>
  </tr>
</table>


Finally, having user comfort in mind, the glasses will connect to an Android application in order to interact seamlessly with the user:



* Modify glasses’ settings like falling user detection threshold, change RTC time, set GNSS location polling interval when using directions feature, set WiFi SSID and key, anything else that comes along the way
* View glasses’ status: current application, Bluetooth signal strength, battery level, details from GNSS
* Set destination for directions feature, preview directions
* Change glasses’ mode&view between the views at the top of page 2.

Hardware components (more on that later) :



* GNSS module
* ESP32
* Display
* LEDs (power, status, maybe another one that’s application-defined)
* Buttons (power, another application-defined probably for starting search for paired device)
* Accelerometer
* Battery


# II. Related Projects

There are several DIY-related projects, such as:



1. [How To Make Smart Glasses DIY at Home](https://www.youtube.com/watch?v=IpJqzwXWg-k&ab_channel=CreativityBuzz)
2. [Smart Glasses Multimeter HOMEMADE](https://www.youtube.com/watch?v=cLiGWNM21XY&ab_channel=Electronoobs)

    Here the guy from Electronoobs seems to be making the most similar project to ours.  He’s using an atmega328, one of the HC-05 bluetooth modules (the bare module with castellated holes) an OLED display very similar to ours, and a custom PCB together with a multimeter from another video to get readings on an OLED on the glasses.  The idea is to not need to look for the multimeter display.  The main difficulty he was saying is to get the focus right when the screen is very close, so he put the display at the back of the box and used a lens to reflect the light into his eye.  In his case he was trying to make the thing usable, so compact.  In our case though the lack of highly integrated PCB is the main thing driving bulk, so a 5-10 cm boom as described below should be fine.

3. [DIY Working E.D.I.T.H SMART GLASSES!](https://www.youtube.com/watch?v=Sj9ZQ20cgLA&ab_channel=JLaservideo)

    If we want a transparent display, he seems to have done most of the research necessary already.  The main takeaway was a Fresnel lens is necessary to deal with the very close focus.  He’s using the Sparkfun transparent display it seems.

4. [Instructables](https://www.instructables.com/DIY-Smart-Glasses-ArduinoESP/)

    He also goes with a lens, but interestingly made an Android application to go with it.  The thing is ESP8266-based so WiFi but no Bluetooth, but this is probably useful inspiration.  Unclear how well or not the lens worked out.


and much more on your favourite search engine!

However, as one can see, most do not implement the idea of using a (semi-)transparent OLED screen, but rather use a projected image/text. More on that later.


# III. Risk and Challenges

Most of the challenges we will face with this project will be hardware-based. Indeed, when looking at the project outline, several things come to mind.

Firstly, connectivity and hardware in general. Several subjects fall under this category. Indeed, to make our project interesting and viable, one will have to fit all hardware components (described in the next sections) as tightly as possible, while maintaining desired functionality. To do so, the ideal would be to make PCBs for the left and right halves. However, as discussed with the professor and TA, **_<span style="text-decoration:underline;">this will be optional</span>_** because realistically only Paolo has the relevant knowledge, and although many other members are willing to learn, the task will be difficult. Further a PCB design flaw takes a long time to get new boards manufactured - the challenges with PCB design are therefore still relevant (although the feature is optional). The left and right halves would likely be connected with FFCs (flat flex cables), and we’d make an FPC (flexible printed circuit) for the display.  FFCs can be bought off the shelf, while FPCs are a type of PCB which ACI can do.  Unfortunately since this takes some time, PCBs are going to be a stretch goal doable if and only if the rest of the project advances quicker than expected.  However, the long lead time means they need to be sent for manufacture by around week 4.  By default however, the glasses will be bulky and probably more similar to a hat in terms of bulk because we use breakout boards for everything.  The PCB version is a nice to have, although the frame for it is much simpler because a single PCB is the only thing to design around.  

Another important factor to take into account would be overall frame design, since it will have to merge all of our product’s components, while making sure we don’t create weight or thermal hotspots. The latter should however be unlikely since the nature of our device would be ultra low power consumption.

Furthermore, long battery life is important. Being more or less size constrained, we will probably only be able to fit a 0.5-1 Ah LiPo. To achieve an acceptable usage time with good performance, while maintaining low power consumption, we will use the ESP32 platform.  Details about power management on ESP32s are in the [technical reference manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf#section.31).  Basic power management like shutting down peripherals when the glasses are on sleep is certainly a critical platform feature, but if we have time going for more advanced options like the ESP32’s modem-sleep or using the ULP coprocessor to do very basic housework would be useful stretch goals.

Secondly, a different concern would be the user’s interaction with the device. Indeed, the simplified mode/sketch proposed in the “Description”’s segment could potentially not work. Using a transparent OLED display might harm the user’s eyesight and make it too unpleasant to look at if it were placed too close to the eye. Of course, this cannot be known in advance and will have to undergo a trial (and error) phase. To solve this problem, two options stand in front of us: we can “push” the display further back, to accommodate the user. This is (somewhat) represented in the following illustration: 



![Basic sketch describing the two aforementioned ideas for screen positionning]({{ site.url }}{{ site.baseurl }}/assets/images/screen_positions.png)



Since transparent OLEDs are a rarity and none of us have ever dealt with these before, we don’t know what exactly to expect.  The main questions at the moment are how the following potential difficulties compare to opaque OLEDs:



* Are they usable in outdoor daylight?
* Can we make a usable UI knowing the panel is 1-bit?
* Do these have more or less problems with focus?
* Given we want to take advantage of the transparency, does the 3d design get difficult if the back of the display needs to be unobstructed?
* Is the (in practice for DIYers) single supply - Sparkfun - going to pose issues  in terms of stock given opaque OLEDs can be sourced from many suppliers?

Since the only way to answer these question is through trial and error, we have opted to also buy an alternative display, as shown in the bill of material below.

Here, we can see under option “_2:_” that the screen is shifted to the right, further from the eye. To make this design more natural and sophisticated, one might try to make the screen move up and down, similarly to a motorcycle helmet visor.  In the default version (breakout board everything), we just solder short wires going to a protoboard, and can use heatshrink for the wires.  

Using such a screen, mounted on a short distance off the forehead would allow for flexibility in our component choices. Indeed, if something were to go wrong with the chosen display, we could replace by any other hobbyist-grade one, which would be easy and quick to order.  Another advantage is the easier focus, and if bulk is not a problem at a larger distance conventional TFT LCDs can be used to get better resolutions, maybe 320x240 for instance.  This means the firmware is not as constrained by what fits on a low resolution display.  If the boom is too cumbersome, some way to fold or detach it with say a 3d-printed hinge would be useful.

For a PCB version, some codesign with the FFC (flat flex cable) for the display would be necessary to ensure that it doesn't tear or get in the way.

Another (perhaps a little less simpler) alternative would be to use a technique similar to what is done in the videos of section II, by simply reflecting a beam of light. The final device would therefore look like this:


![Basic sketch of describing the idea of projecting onto the glasses, namely using mirrors]({{ site.url }}{{ site.baseurl }}/assets/images/projection_idea.png)


As custom PCBs will almost certainly be necessary to get a compact device, this entails some risk in case of major design flaws and design+manufacturing will undoubtedly take a minimum of 3 weeks but probably 5.  As a result, we need to have a protoboard-based version of the glasses to test the software aspects.  Unfortunately this means some time will be spent on this and the cost of the project increases dramatically because commercial breakout boards are fairly pricey.  All parts chosen for the breakout version are easily available in a standalone version, so PCB design is doable if we opt for it.

Finally, as you can see, we’ve decided to build an Android app to interface with the glasses. This might be subject to additional difficulties since Android App development is known to not always be a piece of cake. In the case where it becomes too complicated, we can try building on already done work (such as sensor integrations), and making it interface with pre-existing applications such as Automate.


# IV. Components needed

All in stock as of 28/03/2022



* ESP32-WROVER-E MCU

    Among the ESP32 line, these (and the WROOM) seem to be the ones with best expansion options and they’re active parts.


    Dev board (10.9 CHF): [https://www.digikey.ch/en/products/detail/espressif-systems/ESP32-DEVKITC-VE/12091812](https://www.digikey.ch/en/products/detail/espressif-systems/ESP32-DEVKITC-VE/12091812)

* Transparent OLED display (only Sparkfun’s breakout board seems to be practical, and monochrome).  The model seems quite new, so it might be complicated to buy.

    Sparkfun display (40 CHF): [https://www.digikey.ch/en/products/detail/sparkfun-electronics/LCD-15173/9962476](https://www.digikey.ch/en/products/detail/sparkfun-electronics/LCD-15173/9962476)


    And seems equivalent to the one found [here](https://www.crystalfontz.com/product/cfal12856a00151b-128x56-transparent-oled-screen), [here](https://lcdstore.de/128x56-transparent-OLED-Display-CFAL12856A0-0151-B), or [here](https://www.digikey.com/en/products/detail/crystalfontz/CFAL12856A0-0151-B-E1-2/13982920) (US digikey only though).


    Alternative is to use the regular “reflected display” approach below.


    OLED display: 


    Parallax module (33.4): [https://www.digikey.ch/en/products/detail/parallax-inc/28087/6561022](https://www.digikey.ch/en/products/detail/parallax-inc/28087/6561022)


    The display can be interfaced with SPI and Adafruit also has a version [here](https://www.adafruit.com/product/684), with associated library.


    **_<span style="text-decoration:underline;">Important Note</span>_**: As discussed above, we have listed two displays: one transparent OLED and one with a hard-back. The transparent one is 1-bit, whereas the hard-back is full colour, and opens to the possibility of adding wiring to its back. Since we do not know which will be easier to interface with rest of the hardware, the 3D design and cable routing, and the ease of use, we have opted to list both of them and have a trial and error stage.



* Wanting both an accelerometer and gyro, an IMU would be a good choice.  A [BMI160](https://www.digikey.ch/en/products/detail/bosch-sensortec/BMI160/6136300) integrates both for instance.

    DFrobot breakout (9.8 CHF): [https://www.digikey.ch/en/products/detail/dfrobot/SEN0250/9356335](https://www.digikey.ch/en/products/detail/dfrobot/SEN0250/9356335)

* Battery: probably single 0.5-1 Ah LiPo, needs to be bought in CH.  Maybe even 2 of [these](https://www.conrad.ch/de/p/emmerich-14500-spezial-akku-14500-flat-top-li-ion-3-7-v-800-mah-1362894.html) if bulk is ok, buying 2 for breakout and 2 for PCB version 48 CHF
* GNSS Module

    PA1616


    Adafruit breakout board (29.7 CHF): [https://www.digikey.ch/en/products/detail/adafruit-industries-llc/746/5353613](https://www.digikey.ch/en/products/detail/adafruit-industries-llc/746/5353613)

* Buck-boost converter to get stable 3.3V from the cell: 

    Breakout module: [https://www.digikey.ch/en/products/detail/dfrobot/DFR0568/9559258](https://www.digikey.ch/en/products/detail/dfrobot/DFR0568/9559258)

* Paolo has a bunch of TP4056 boards we can use for charging a 1S LiPo during development time, and we can order some more meanwhile

Only with custom PCB (all parts to communicate with from software are the non-breakout versions of the above): 



* Only applicable if we make custom PCBs: USB-UART bridge like an FT232 for programming.  If not in stock, Paolo has some or also an external bridge.
* PCB+stencil, should be able to do this at ACI in ELE unless we need 4 layer.  High chance we need rigid-flex PCBs because flex PCB from OLED is very short.

    Cost should be reasonable as long as we stay &lt;=4 layer.  Looking at Aisler, 3x ~53 cm<sup>2</sup> 4 layer boards including stencils (microcontroller boards for Xplore) are about €60 from Aisler. Best case using 2 layer : 40$

* Other basic ICs, connectors and discretes will be sorted out during schematics design because there are undoubtedly small parts we can’t foresee before.
* Only applicable if we make custom PCBs: Module (3.86 CHF): [https://www.digikey.ch/en/products/detail/espressif-systems/ESP32-WROVER-E-N16R8/11613135](https://www.digikey.ch/en/products/detail/espressif-systems/ESP32-WROVER-E-N16R8/11613135)
* Only applicable if we make custom PCBs: Bare opaque display (21.2 CHF): [https://www.digikey.ch/en/products/detail/newhaven-display-intl/NHD-0-95-9664G/9842781](https://www.digikey.ch/en/products/detail/newhaven-display-intl/NHD-0-95-9664G/9842781)

    The main difficulty with this is unlike the previous idea the bare panel has a pin pitch of 0.7 mm, for which FPC connectors seem to not exist.  We need to see if ACI has a hot bar machine, or otherwise we need to solder that by hand.

* BMI160 Chip (6.3 CHF): [https://www.digikey.ch/en/products/detail/bosch-sensortec/BMI160/6136300](https://www.digikey.ch/en/products/detail/bosch-sensortec/BMI160/6136300)
* Buck-boost converter IC for stable 3.3V [https://www.digikey.ch/en/products/detail/renesas-electronics-america-inc/ISL91107IRTNZ-T7A/6097373](https://www.digikey.ch/en/products/detail/renesas-electronics-america-inc/ISL91107IRTNZ-T7A/6097373)
* GNSS Module (19.8 CHF): [https://www.digikey.ch/en/products/detail/adafruit-industries-llc/5186/15204092?s=N4IgTCBcDaIAoEECMA2VIC6BfIA](https://www.digikey.ch/en/products/detail/adafruit-industries-llc/5186/15204092?s=N4IgTCBcDaIAoEECMA2VIC6BfIA)
* Battery charge IC: [MCP73831](https://www.digikey.ch/en/products/detail/microchip-technology/MCP73831T-2ACI-OT/964301) for 1S LiPo


# V. Software Requirements

In order to implement our smart glasses prototype, we will also need to create a lot of software that will utilise the hardware components already present on the glasses to give the user the features that we have discussed above. In order to communicate with the user’s smartphone and to provide the user with a decent UI to interact with the glasses, we will be developing a small android app. Some of the things this android app will do include:



* We will configure a notification listener on the android app (using this library: [https://github.com/lamydev/Android-Notification](https://github.com/lamydev/Android-Notification)) in order to detect notifications. If the listener is triggered, the data will be transferred to the smart glasses for them to display the information to the user
* We can use this library: [https://developers.google.com/maps/documentation/directions/get-directions](https://developers.google.com/maps/documentation/directions/get-directions) in order to get directions (such as left, right, etc) to show on the glasses screen via google maps. Again, we can make listeners so that if a direction change is required and is triggered by this library, we display it on the glasses screen and it allows for easy navigation for the user
* For the find-my-glasses feature: we can use the android directives for bluetooth (link: [https://developer.android.com/guide/topics/connectivity/bluetooth](https://developer.android.com/guide/topics/connectivity/bluetooth)) along with the help of an existing library (link: [https://altbeacon.github.io/android-beacon-library/distance-calculations.html](https://altbeacon.github.io/android-beacon-library/distance-calculations.html)), helping us know the distance between our android device and the glasses, which can be extremely helpful if one of them gets lost

On the onboard processor, we won’t have dedicated applications, but we will still perform the following computations:



* Using the data transferred by the smartphone to display relevant information on the screen.
* Data from the IMU will be treated onboard the glasses, hence seeing if the user is in an “emergency situation” will be done onboard the glasses themselves. 


# VI. Tasks Breakdown

Mini tasks (hardware+firmware).  Parts prefixed with F are firmware, with A are Android, with H are hardware, with HP are hardware but only applicable if making custom PCBs, and O other.  These can be either omitted or delayed without too many problems.  Unlike what seems to have been initially misunderstood, 1x does not mean Paolo.  It just means “1 person needs to do this”.

To aid in the first couple of weeks where hardware is in shipping, Paolo has 2xESP32s and 2xESP8266s, 1x0.96” OLED with i2c and an old version of Adafruit’s ultimate GPS module.  We can use these to familiarise ourselves especially with the onboard programming.  Somewhere at home there should also be an ADXL345 accelerometer.

**<span style="text-decoration:underline;">Important Disclaimer</span>**:The following tasks-to-people map is only a preview of what is predicted to be done. It will be used as a baseline to know who will work on what. It is however obvious that during development, some tasks might seem more complicated than others, and the mapping can change as the project advances



1. Week 1:
    1. H Hardware features freeze
    2. H Check compatibility of all major parts (protocols, special packages, operating voltages, availability, comparable breakout versions, etc)
    3. H+F Research hardware design guides + libraries (if any) (ended up being more or less just researching for breakouts’ schematics + displays’ datasheets)
    4. H Finalise hardware architecture
    5. F hook up one of Paolo’s ESP32s to display on breakout board (using either headers or a breadboard), make boilerplate for this and try getting text on the screen. 
    6. F hook up other ESP32 to an ADXL345 accelerometer at least to get familiar with i2c on ESP32. 
    7. H+F order remaining parts for breakout version for firmware dev, required people: 
        1. Batteries
        2. Adafruit display
        3. ESP32 dev kit(s)
        4. BMI160 breakout
        5. 3.3V buck/boost module
        6. Adafruit GNSS
2. Week 2:
    1. H Schematics+ (HP) PCB routing
    2. F Get Bluetooth serial link between ESP32 and Android device or PC. 
    3.  F wait for parts to arrive
    4.  F make firmware architecture plan, required people
    5.  A Get Google’s directions into something usable for sending to the ESP32. 
    6.  A/F make serializer/deserializer for exchanging ESP32-Android data.   
    7.  A Start building the app and familiarising with Android libraries: have home screen with buttons

Note: Tasks f.g. will most likely work closely together



3. Week 3:
    1.  A get Android status (for now battery, time, Internet connectivity, others as necessary) into serialised form for sending to ESP32 + start making sketches of how the information will be displayed on the glasses (e.g.: make a battery icon, choose font,...), 
    2.  A Continue familiarisation with Android’s APIs - start building the final (simple) look of the application 
    3.  F drive display with text from Android status
    4.  A/F Get location from GNSS module and send to Android device
    5.  F Display signal strength of connected Bluetooth device upon long-pressing the application-defined button
    6.  H solder a protoboard with all breakouts on it (ideally using male/female headers to make them easily removable)
4. Week 4:
    1.  H good time for **_<span style="text-decoration:underline;">hardware milestone 1</span>_**
    2.  F **_<span style="text-decoration:underline;">firmware milestone 1</span>_** for “can interface with all peripherals at least so far as to say get readings over debug serial”
    3.  F make text stream on display from Bluetooth serial to prepare for Android notifications, required people
    4.  F Set glasses to sleep on power button long-press, aka disable all peripherals and set power button to be a wakeup pin, required people
    5.  A Android side needs to make ESP32’s Bluetooth transmitter go in high power transmit and final Android app design modifications 

        This will complete **_<span style="text-decoration:underline;">software milestone 1</span>_**

5. Week 5, On parts arrival:
    1.  A/F configure glasses’ settings from Android application, and finish tests of overall connectivity; required people
    2.  Buffer week for in case stuff from previous weeks slips
    3.  H+F more advanced power management like ULP coprocessor monitoring IMU periodically in case there’s movement, test power management features (multimeter + oscilloscope across R)
6. Week 6:
    1.  Good time for **_<span style="text-decoration:underline;">milestone 2 </span>_**- status/notifications on glasses, and working BLE signal strength display, plus low power consumption on idle
    2.  3D Design enclosure for breakout and (HP) SMD version
    3.  A enter destination on Android application and retrieve directions following work from before
    4.  F display Google directions on glasses and update Android application every 30 s or so about location, required people
7. Week 7:
    1.  F integrate off board functionality into main system
    2.  Good spot for 2nd hardware/firmware milestone
    3.  F fall detection and alerting
    4.  A forward fall detection

If we have time to optionally implement custom PCBs, the tasks will be done in the following order, and we will try to parallelize them with the above-mentioned schedule:



8. Week 1:
    37. HP Contact ACI for PCB advice (gotchas with rigid-flex if we go with it, design rules, costs at ACI), required people
9. Week 2:
    38. HP Make BOM, final stock check, send BOM+PCB for order/manufacture
10. On (HP)PCB arrival (probably week 4/5) :
    39. HP Basic tests - any shorts to ground, manufacturing errors + check BOM is complete
    40. HP Solder all SMD components

        At this point the following components should be left out, to make sure any faults found are found quickly: battery, display

    41. HP Inspect soldering and test for shorts
    42. SMD version, and adapt 3D design 
11. From this point on: 
    1.  Try transitioning from breadboard version, have several weeks of “buffer” to be able to rollback if anything goes wrong


## Milestones


<table>
  <tr>
   <td>
   </td>
   <td>Hardware and Firmware
   </td>
   <td>Software
   </td>
   <td>Other
   </td>
  </tr>
  <tr>
   <td>1
   </td>
   <td>Hardware features freeze
    <p>
    Block diagram of parts <br>
    Schematic ready<br>
    On “breakout” version:</p>  
    <ul>
        <li>A programmed ESP32 dev kit (hello world) </li>
        <li>Test display output</li>
        <li>Test accelerometer/gyro </li>
    </ul>
   </td>

   <td>
   <p>Have a “lower-
   level” API to gather the different aspects of the data communicated to the Android - the backend. <br><br>
Start to work on the Application’s design </p>
   </td>
   
   <td>Start thinking (and designing) a 3D design which would fit all the parts - coordinated with PCB if applicable
   </td>
  </tr>


  <tr>

   <td>2
   </td>

   <td>
   <p>Have critical components tested+integrated into main functionalities <br>
Implement (and test) basic power management techniques by turning on and off the glasses.</p>
   </td>

   <td>
   <p>Have the Android app ready to interface with glasses, as well as maps feature ready.</p>
   </td>

   <td> <p>3D print and make the necessary adjustments to the (hopefully working) PCB and components <br><br>

Design simple icons adapted to the screen’s resolution for the notifications that will be displayed, and other graphic components if needed.
</p>
   </td>
  </tr>
</table>


Final milestone: implement any of the additional proposed software.  Beyond basic power management (turn on or off hardware when the glasses are on or off), explore more advanced options (turn off clock domains, MCU/modem sleep modes)



References to useful documentation:



* General details on ESP32 architecture (for firmware development): [https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
* Bluetooth:
    * [https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/](https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/)
    * [https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/](https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/)
    * [https://randomnerdtutorials.com/esp32-ble-server-client/](https://randomnerdtutorials.com/esp32-ble-server-client/)
    * Getting BLE signal strength from ESP32: [https://github.com/nkolban/esp32-snippets/issues/236#issuecomment-378937725](https://github.com/nkolban/esp32-snippets/issues/236#issuecomment-378937725)
* Power management:
    * [https://randomnerdtutorials.com/esp32-deep-sleep-arduino-ide-wake-up-sources/](https://randomnerdtutorials.com/esp32-deep-sleep-arduino-ide-wake-up-sources/)
* IMU:
    * Datasheet: [https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmi160-ds000.pdf](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmi160-ds000.pdf)
    * DFrobot library: [https://github.com/DFRobot/DFRobot_BMI160](https://github.com/DFRobot/DFRobot_BMI160)
* Sending alerts from the ESP32 directly, to complement Android application’s
    * [https://randomnerdtutorials.com/esp32-send-email-smtp-server-arduino-ide/](https://randomnerdtutorials.com/esp32-send-email-smtp-server-arduino-ide/)
* OLED display:
    * [https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide/](https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide/)
    * [https://randomnerdtutorials.com/esp32-esp8266-dht-temperature-and-humidity-oled-display/](https://randomnerdtutorials.com/esp32-esp8266-dht-temperature-and-humidity-oled-display/)
* PCB for ESP32-WROVER-E module:
    * Reference design of dev boards: [https://www.espressif.com/sites/default/files/documentation/esp32-devkitc-v4_reference_design.zip](https://www.espressif.com/sites/default/files/documentation/esp32-devkitc-v4_reference_design.zip)
    * Module’s datasheet: [https://www.espressif.com/sites/default/files/documentation/esp32-wrover-e_esp32-wrover-ie_datasheet_en.pdf](https://www.espressif.com/sites/default/files/documentation/esp32-wrover-e_esp32-wrover-ie_datasheet_en.pdf)
    * Family datasheet: [https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
* Common ESP32 Pinout: [https://randomnerdtutorials.com/esp32-pinout-reference-gpios/](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
* Unlikely to be necessary, but if we need it i2c multiplexing is straightforward: [https://randomnerdtutorials.com/tca9548a-i2c-multiplexer-esp32-esp8266-arduino/](https://randomnerdtutorials.com/tca9548a-i2c-multiplexer-esp32-esp8266-arduino/)