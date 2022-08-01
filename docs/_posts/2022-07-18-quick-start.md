---
title: "Quick-Start"
permalink: /quick-start/
---

Although this page is labelled as a "quick-start", it might not be as quick as you think. Indeed, you'll first need to get all the relevant parts. For this, see the [Parts Choice section]({{ site.url }}{{ site.baseurl }}/dive-down/hardware/#parts-choices) of the hardware dive-down.

Once you have all the parts, you'll have to put them together. For that, two options stand in front of you: custom PCB and protoboard. Both options are reasoned about in our hardware dive-down and, although custom PCB is the desired one, we have opted for protoboard mainly due to lack of time. A detailed description on how to solder everything together can be found [here]({{ site.url }}{{ site.baseurl }}/dive-down/hardware/#protoboard-steps).

Congrats! You should now have all the parts soldered together and ready to work! Just plug them in a battery and... Wait, have we not forgotten anything? Well, for now, we've only got "bare-metal" hardware, which is not programmed to do anything. We must therefore program the ESP32, our glasses' brain. For that, simply flash our firmware, as explained [here]({{ site.url }}{{ site.baseurl }}/dive-down/firmware/#instructible--running-the-firmware),or thoroughly read the whole dive-down to help you make your own!

Perfect! Your glasses should be functional upon plug-in, displaying an "empty" home screen. Now to use them, simply install our Android app, whose code can also be found on [our repo](https://github.com/vigarov/SmartGlass). Take a look at our Android [dive-down]({{ site.url }}{{ site.baseurl }}/dive-down/software/) to find out all the challenges of making such an app!

Finally, once you've made sure everything is working, or if you're confident enough and would like to start it in advance, make the glasses more... physically attractive. Indeed for now, if you've followed the protoboard version of our hardware implementation, you probably have quite an open air, metally design. As such, we have designed a custom case in order to fit all the components, and add that "glasses" look we are after. You can find our 3D design file [here]({{ site.url }}{{ site.baseurl }}/assets/3d/3D-Design.f3d) and, once again, read through our dive-down showcasing the many different iterations [here]({{ site.url }}{{ site.baseurl }}/dive-down/3d/).


We all hope our explanations were as clear as possible. Feel free to open an issue on the repo, if one was to occur. We would also be quite happy to see your own implementations, so feel free to contact us and showing them off!