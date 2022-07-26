--- 
author_profile: false
layout: single
classes: wide2
permarlink: /index/
title: " "
---
# Smart Glasses

<div id="glasses_images_container">
    <!-- The HTML for the animations is adapted from Copyright (c) 2022 by Shaw (https://codepen.io/shshaw/pen/LBZyyM) -->
    {%- for i in (1..2) -%}
    {%- capture pic_link -%} {{ site.url }}{{ site.baseurl }}/assets/images/final_glasses_{{i}}.png {%- endcapture -%}
    <div class="column elements_no_2">
        <div class="glasses" style="background-image: url('{{pic_link}}'); --row-total: 5;">
            <img alt="The final version of the Smart Glasses, physically built, angle {{i}}" src="{{pic_link}}">
            <div class="glasses__popup">
                <img src="{{pic_link}}" /><div class="glasses__row" style="--row-index: 0; --random: 0.23"><div class="glasses__row-inner"></div>
                </div><div class="glasses__row" style="--row-index: 1; --random: 0.72">
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
    {%- endfor -%}
</div>


Smart Glasses are, as their name suggests, a pair of glasses built to keep you more easily in touch with your surroundings.

This project was built for the EPFL course <a href="https://edu.epfl.ch/studyplan/en/bachelor/computer-science/coursebook/making-intelligent-things-CS-358">CS-358</a> "Making Intelligent Things".
Weekly feedback and supervision was done by Federico Stella, and Q&A sessions were organised by Prof. Koch.

## The team

<div id="team_cards">
{% for person in site.data.team %}
    <p style="display: none;">{{ person | json}}</p>
    <div class="column elements_no_{{ site.data.team.size }} team_member">
        <div class="pic_or_avatar">
            {%- capture pic_link -%} 
                assets/images/home_profiles/
                {%- if person.pic -%}
                    {{person.name | downcase | split: " " | first}}
                {%- else -%}
                    default
                {%- endif -%}
                .png
            {%- endcapture -%}
            <img src="{{ pic_link }}" alt="Picture of {{ person.name }}">
        </div>
        <div class="info"> 
            <h3 class="name">{{ person.name }}</h3>
            <h4 class="role">{{ person.role }}</h4>
        </div>
        <ul class="socials">
        {% for social in person.socials %}
            {%- capture social_link -%}
                {%- unless social.type == "mail" -%}
                    https://www. 
                    {%- case social.type -%}
                        {%- when "github" -%} 
                        github.com/
                    {%- endcase -%}
                {%- else -%}
                    mailto:
                {%- endunless -%}
                {{ social.data }}
            {%- endcapture -%}
            {% capture logo_classes -%}
                {%- case social.type -%}
                    {%- when "mail" -%}
                        fa fa-envelope
                    {%- when "github" -%}
                        fab fa-github
                {%- endcase -%}
            {% endcapture %}
            <li> 
                <a href="{{social_link}}">
                    <i class="{{logo_classes}}" aria-hidden="true"> </i>
                </a>
            </li>
        {% endfor %}
        </ul>
    </div>
{% endfor %}
</div>



## Site Structure

The project naturally partitioned itself into three different parts, namely hardware (electronics and 3D design), firmware and software. 
As such, a quick start guide can be found under [Quick Start]({% post_url 2022-07-18-quick-start %}), giving a straigthforward explanation on how to recreate the glasses. A deeper explanation of the challenges and solutions applied to each one of them can be found in the relevant [Dive Downs]({{ site.url }}{{ site.baseurl }}/categories/#dive-down).

While reading those, you might notice several features have been cut off - this is mainly due to lack of time and the need for a stable build by the end of the course. If you intend to build this project, and would like to add even more features, take a look at our [Project Proposal]({% post_url 2022-07-18-project-proposal %}) which we used to present the project before it was accepted by the course's teaching team. It contains several ideas that we didn't have time to implement, such as custom PCB, or additional localization features.

On that note, I wish you a nice read-through!

<script>
    let glass_images = document.getElementsByClassName("glasses");
    let masthead = document.getElementsByClassName("masthead")[0];
    let m_text = document.getElementById("site-nav");
    var previous_bo = masthead.style.border;
    var previous_ba = m_text.style.background;
    for(let i=0; i< glass_images.length;i++){
        glass_images[i].addEventListener('mouseover',function(){masthead.style.border = "0";
                                                                m_text.style.background = "inherit"});
        glass_images[i].addEventListener('mouseout',function(){masthead.style.border = previous_bo;
                                                                m_text.style.background = previous_ba;});
    }
</script>