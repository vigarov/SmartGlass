Project proposal : Smart Glasses
===========================================

*Group Members* (in alphabetical last name order): Paolo Celati (325174), David Chernis (310298), Victor Garvalov (325375), Shrey Mittal (312275), Nicolas Szwajcok (315213), Tim Vaughan-Whitehead (328387)

I. Description
--------------

The main idea of this project is to make smart glasses. To keep things simple, only one of the lenses will have a screen/act as a graphic interface for the user. What would’ve been the glasses’ frames can be expanded to fit in electronics and batteries. A general sketch of the desired outcome would be the following:![A very-well-drawn and professional sketch illustrating the outline of the Smart Glasses the group will try to build](images/image3.jpg "Product Sketch")

Such glasses will be used for several things such as maintaining a connection between the user and his digital world, while not requiring him to be actively using his digital devices (such as his phone or PC). Furthermore, these glasses could be, coupled to vision corrective lenses, used as an additional tool for ensuring one’s safety and comfort.

Concretely, there are several applications and use cases for such glasses we would like to implement, namely:

*   Getting status and notifications from an Android device. This can be done through a bluetooth module establishing a connection with the device in question, and will make the glasses a true smart item.
*   Detecting whether a person has fallen and is unable to get up. This can be done analysing an accelerometer’s readings. Optionally, if there’s a camera on board we could also transmit an image of the place of the accident in case that helps whoever is coming to help the person in need. This will make the glass a potential life-saver
*   Finding your phone (or other paired device). This can be done using the bluetooth emitter as a beacon and analysing the signal’s strength. The advantage of doing so through the glasses is that the navigation would be straightforward, turning the glasses in a day-to-day must-have
*   Optionally, given enough time and adequate resource allocation, one might envision a GPS system, navigating the user throughout a path from point A to point B. This can either be done by interfacing through the Google Maps API, or, if restraining to local operations, one might envision fetching a small subset of the world’s map from OpenStreetMap (e.g.: focusing on the EPFL campus), and running a path finding [graph](https://www.google.com/url?q=https://help.openstreetmap.org/questions/7430/creating-graphnodes-edges-from-osm-xml-data&sa=D&source=editors&ust=1648263166162405&usg=AOvVaw1OelIgmtVHc6YDAtNZQdjP) algorithm on-chip, therefore providing local offline navigation.
*   Optionally, given we also have a somewhat decent camera, implementing various nice-to-have addons, such as any of the following:

*   Analysing a chess-game position, and hiniting the next best move to the user by dynamically showing what piece to move and where. This will make the glasses a tool engineered for fun
*   Analysing a text (in an OCR fashion) and either reading it out loud to the user or zooming it up and displaying it word by word. This will help the visually impaired

Finally, having user comfort in mind, we plan to build a web app, or Android(/iOS) application to interface with the various components ergonomically.

II. Related Projects
--------------------

There are several DIY-related projects, such as:

1.  [How To Make Smart Glasses DIY at Home](https://www.google.com/url?q=https://www.youtube.com/watch?v%3DIpJqzwXWg-k%26ab_channel%3DCreativityBuzz&sa=D&source=editors&ust=1648263166163574&usg=AOvVaw3JTffPK50Nvlv60jqDMJVC)
2.  [Smart Glasses Multimeter HOMEMADE | Arduino & Bluetooth](https://www.google.com/url?q=https://www.youtube.com/watch?v%3DcLiGWNM21XY%26ab_channel%3DElectronoobs&sa=D&source=editors&ust=1648263166163984&usg=AOvVaw2WNU8rMkqxc3m-M-vLaYUp)
3.  [DIY Working E.D.I.T.H SMART GLASSES! - Spider-Man Far From Home (Building Your Ideas #3)](https://www.google.com/url?q=https://www.youtube.com/watch?v%3DSj9ZQ20cgLA%26ab_channel%3DJLaservideo&sa=D&source=editors&ust=1648263166164294&usg=AOvVaw0aY9bluIhZyB2S40viikwg)
4.  [https://www.instructables.com/DIY-Smart-Glasses-ArduinoESP/](https://www.google.com/url?q=https://www.instructables.com/DIY-Smart-Glasses-ArduinoESP/&sa=D&source=editors&ust=1648263166164562&usg=AOvVaw3_Y3tRxSQvQnXVg1qudWJ_)

and much more on Google!

However, as one can see, most do not implement the idea of using a (semi-)transparent OLED screen, but rather use a projected image/text. More on that later.

III. Risks and challenges
-------------------------

Most of the challenges we will face with this project will be hardware-based. Indeed, when looking at the project outline, several things come to mind.

Firstly, connectivity and hardware in general. Several subjects fall under this category. Indeed, to make our project interesting and viable, one will have to fit all hardware components (described in the next sections) as tightly as possible, while maintaining desired functionality. To do so, we will probably need custom rigid-flex PCB design <I’ll let Paolo expand on what challenges one could face with that, and perhaps show an alternative to each? My 40minutte googling knowledge doesn’t seem to be sufficient to go in depth on the subject haha>.

Another important factor to take into account would be overall frame design, linked with cooling. Indeed, having that many sensors in such a tiny space (up to a STM32WB, Display+Controller, Camera, GPS module, Accelerometer) attached on a PCB, with a battery, things might get very hot very quickly. A very precise 3D design will therefore be needed to hold everything together, while keeping things cool. One might also think about adding cooling solutions (small fan perhaps) if things were to get out of hand, or simply redesigning the position of the different parts as to normalise average temperature.

Furthermore, long battery life is important. Being more or less size constrained, we will probably only be able to fit a 0.5-1 Ah LiPo. To achieve an acceptable usage time with good performance, while maintaining low power consumption, we will use a STM32WB (as can be seen in the next section) - a low power BLE MCU. Programming this MCU itself is going to be a challenge (a lot of resources and examples can be found online however), but, to cut on additional costs, we will try to find a fitting Nucleo in one of EPFL’s labs. If we were to fail finding that, we would have to order one, which would make us lose several weeks of development/testing time (before it would arrive).

Secondly, a different concern would be the user’s interaction with the device. Indeed, the simplified mode/sketch proposed in the “Description”’s segment could potentially not work. Using a transparent OLED display might harm the user’s eyesight and make it too unpleasant to look at if it were placed too close to the eye. Of course, this cannot be known in advance and will have to undergo a trial (and error) phase. To make it easier however, we have made sure to only research transparent OLED displays (indeed LCD ones would force having lit black LEDs which would further harm the user’s eyes if anything). To solve this problem, two options stand in front of us: we can “push” the display further back, to accommodate the user. This is (somewhat) represented in the following illustration:

![](images/image1.png)

Here, we can see under “2:” that the screen is shifted to the right, further from the eye. To make this design more natural and sophisticated, one might try to make the screen move up and down, similarly to a motorcycle helmet visor.

Another (possibly simpler) alternative would be to use a technique similar to what is done in the videos of section II, by simply reflecting a beam of light. The final device would therefore look like this:

![](images/image2.png)

<Any other risks challenges?>

IV Components needed
--------------------

<TODO: preferably discuss each component: are we actually going to plan on using it + approve optimal links>

*   STM32WB series MCU, probably [this](https://www.google.com/url?q=https://www.digikey.ch/en/products/detail/stmicroelectronics/STM32WB5MMGH6TR/13592597?s%3DN4IgTCBcDaIMoBUCyBmMB1AQiAugXyA&sa=D&source=editors&ust=1648263166166889&usg=AOvVaw0xnJo4xZiSB8IoxZCFzDvH) because it does all the RF part in a pre-made module and it’s cheap (also supports ZigBee if interested)
*   USB ESD protection IC: USB means we can do USB DFU, charging and a basic serial interface to do debugging when an ST Link is unavailable
*   During development of the hardware, >=1 NUCLEO-WB board (more or less any of them is fine) for firmware development (perhaps something is available in a lab?)
*   ST Link programmer - probably available from one of the labs
*   Transparent OLED display (only Sparkfun’s breakout board seems to be practical, and monochrome).  I can’t find the raw display’s model number so I assume it’s custom-made.  Alternative is to use the regular “reflected display” approach.
*   OLED display (if using “reflected display”): [this](https://www.google.com/url?q=https://www.digikey.ch/en/products/detail/adafruit-industries-llc/1673/5353658&sa=D&source=editors&ust=1648263166167743&usg=AOvVaw0Ub2yPmSCvRPgCt6e98NJy), so when doing development we use the breakout board and otherwise we unplug the display and use our own PCB with controller by modifying Adafruit’s schematic: SSD1351 controller apparently not buyable standalone so we need to transfer the one from the breakout
*   Camera ([this](https://www.google.com/url?q=https://www.digikey.ch/en/products/detail/adafruit-industries-llc/397/5638296&sa=D&source=editors&ust=1648263166168116&usg=AOvVaw23EJBjkxgtT79YeFZ1Kaqk))
*   Accelerometer: say [ADXL345](https://www.google.com/url?q=https://www.digikey.ch/en/products/detail/analog-devices-inc/ADXL345BCCZ/2034829&sa=D&source=editors&ust=1648263166168467&usg=AOvVaw0xGvFzSq5CYABoejR8YBpi)
*   Battery: probably single 0.5-1 Ah LiPo, needs to be bought in CH
*   Battery charge IC: [MCP73831](https://www.google.com/url?q=https://www.digikey.ch/en/products/detail/microchip-technology/MCP73831T-2ACI-OT/964301&sa=D&source=editors&ust=1648263166168816&usg=AOvVaw0ZF2rNkuM6oTEuN68xj6rr) for 1S LiPo
*   GPS Module: [Quectel L96](https://www.google.com/url?q=https://www.digikey.ch/en/products/detail/quectel/L96-M33/13278244&sa=D&source=editors&ust=1648263166169086&usg=AOvVaw3ps23Cedjw5-NFz3UWTo57)
*   PCB+stencil, should be able to do this at ACI in ELE unless we need 4 layer.  High chance we need rigid-flex PCBs because flex PCB from OLED is very short and buttons in different orientations needs.

V Structure for the upcoming weeks
----------------------------------

<TODO complete the milestone → week assignments function; must see who does what>

Week 5+6: Order Parts, start reading documentation (<PCB?,>STM32WB, Android Bluetooth communication+WebApp/Android App libraries)

#### Milestones

<table ><tbody><tr ><td   ><p ><span ></span></p></td><td   ><p ><span >Hardware</span></p></td><td   ><p ><span >Software</span></p></td><td   ><p ><span >Other</span></p></td></tr><tr ><td   ><p ><span >1</span></p></td><td   ><p ><span >Independently have:</span></p><ul ><li ><span >A PCB design</span></li><li ><span >A programmed STM32WB</span></li></ul></td><td   ><p ><span >Have a “lower-level” API to gather the different aspects of the data communicated to the Android - the backend</span></p></td><td   ><p ><span >Start thinking (and designing) a 3D design which would fit all the parts - coordinated with PCB</span></p></td></tr><tr ><td   ><p ><span >2</span></p></td><td   ><p ><span >Print the PCB, put it together (solder+test different aspects: temperature, easy to use screen,...) with all the components: output “Hello World!”</span></p></td><td   ><p ><span >Start working on a front end : whether it is a web app, or full fetched android app (both could, if remaining basic and simple, be probably be easily done with premade libraries; the latter could also not be a standalone app, but a “script” of the kind of Automate’s IFTTT). Independently of that, if the previous milestone has been reached, outputting simple status should be more or less easy → output notifications/battery status</span></p></td><td   ><p ><span >3D print and make the necessary adjustments to the (hopefully working) PCB and components</span></p><p ><span ></span></p><p ><span >Design simple icons adapted to the screen’s resolution for the notifications that will be displayed, and other graphic components if needed.</span></p></td></tr></tbody></table>
Final milestone: implement any of the additional proposed software and optimise the hardware (mainly the programmed STM32WB) to increase battery life (e.g.: implement aggressive sleep scheduler)