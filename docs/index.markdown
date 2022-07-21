--- 
author_profile: false
layout: single
classes: wide2
permarlink: /index/
---

<div id="glasses_images_container">
    <div class="column">
        <!-- The HTML for the animations is from Copyright (c) 2022 by Shaw (https://codepen.io/shshaw/pen/LBZyyM) -->
        <div class="glasses" style="background-image: url('{{ site.url }}{{ site.baseurl }}/assets/images/final_glasses_2.png'); --row-total: 5;">
            <img alt="The final version of the Smart Glasses, physically built, angle 1" src="{{ site.url }}{{ site.baseurl }}/assets/images/final_glasses_2.png">
            <div class="glasses__popup">
                <img src="{{ site.url }}{{ site.baseurl }}/assets/images/final_glasses_2.png" />
                <div class="glasses__row" style="--row-index: 0; --random: 0.23">
                    <div class="glasses__row-inner"></div>
                </div>
                <div class="glasses__row" style="--row-index: 1; --random: 0.72">
                    <div class="glasses__row-inner"></div>
                </div>
                <div class="glasses__row" style="--row-index: 2; --random: 0.11">
                    <div class="glasses__row-inner"></div>
                </div>
                <div class="glasses__row" style="--row-index: 3; --random: 0.50">
                    <div class="glasses__row-inner"></div>
                </div>
                <div class="glasses__row" style="--row-index: 4; --random: 0.39;">
                    <div class="glasses__row-inner"></div>
                </div>
            </div>
        </div>
    </div>
    <div class="column">
        <div class="glasses" style="background-image: url('{{ site.url }}{{ site.baseurl }}/assets/images/final_glasses_1.png'); --row-total: 5;">
            <img alt="The final version of the Smart Glasses, physically built, angle 2" src="{{ site.url }}{{ site.baseurl }}/assets/images/final_glasses_1.png">
            <div class="glasses__popup">
                <img src="{{ site.url }}{{ site.baseurl }}/assets/images/final_glasses_1.png" />
                <div class="glasses__row" style="--row-index: 0; --random: 0.23">
                    <div class="glasses__row-inner"></div>
                </div>
                <div class="glasses__row" style="--row-index: 1; --random: 0.72">
                    <div class="glasses__row-inner"></div>
                </div>
                <div class="glasses__row" style="--row-index: 2; --random: 0.11">
                    <div class="glasses__row-inner"></div>
                </div>
                <div class="glasses__row" style="--row-index: 3; --random: 0.50">
                    <div class="glasses__row-inner"></div>
                </div>
                <div class="glasses__row" style="--row-index: 4; --random: 0.39;">
                    <div class="glasses__row-inner"></div>
                </div>
            </div>
        </div>
    </div>
</div>

Smart Glasses are, as their name suggests, a pair of glasses built to keep you more easily in touch with your surroundings.

This project was built for the EPFL course <a href="https://edu.epfl.ch/studyplan/en/bachelor/computer-science/coursebook/making-intelligent-things-CS-358">CS-358</a> "Making Intelligence Things".
Weekly feedback and supervision was done by Federico Stella, and Q&A sessions were organised by Prof. Koch.

## The team

## Site Structure

The project naturally partitioned itself into three different parts, namely hardware (electronics and 3D design), firmware and software. 
As such, a quick start guide can be found under [Quick Start]({% post_url 2022-07-18-quick-start %}), giving a straigthforward explanation on how to recreate the glasses. A deeper explanation of the challenges and solutions applied to each one of them can be found in the relevant *Dive Downs*.

While reading those, you might notice several features have been cut off - this is mainly due to lack of time and the need for a stable build by the end of the course. If you intend to build this project, and would like to add even more features, take a look at our [Project Proposal]({% post_url 2022-07-18-project-proposal %}) which we used to present the project before it was accepted by the course's teaching team. It contains several ideas that we didn't have time to implement, such as custom PCB, or additional localization features.

On that note, I wish you a nice read-through!