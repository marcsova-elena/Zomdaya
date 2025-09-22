# Zomdaya

## Introduction

A brand new season of a show called "My life" is coming up and i thought of nothing better than to finally quit my procrastination and start coding again. I have lost my passion multiple times, had sudden bursts of determination to code something great, a live changing project, however my adhd had quickly gotten ahold of me and all my plans have turned to unfinished self promises.

This time it is different. The glooming danger of college is advancing near (starting my first semester in two days), but I have decided to start a new anime ark, this time becoming a coding mastermind. I plan on doing a bunch of cool little projects like these, reflexing upon them and getting them into as finished of a state as possible. In parallel I will also learn basic algorithmic theory and indulge in competitive programming. I believe an exciting journey awaits me.

This first project might seem very simple, maybe even insultingly arbitrary from the perspective of a seasoned programmer, however I would argue it can serve as a great medium for me to get back into coding and open gates for more ambitious projects in the future.

A great inspiration for this project was Pezzza and his work on YT: https://www.youtube.com/@PezzzasWork , particularly his own top down shooter in the same graphical library. So, rocking YT lofi and "Coding music for deep focus", let's dive into this.

## Getting SFML working

The first challenge was to get SFML working. I thought this wouldn't pose a challenge, as I previously had it set up quite nicely,
even having a sort of basic project template on my github. That would be too easy though, so the devs decided it would be hilarious to update SFML to a new version (SFML 3) forcing me to create an entirely new template, this time using CMake instead of the normal makefile. From what I understand, this isn't compulsory, however my brain thought it was a great opportunity to learn a new thing, so I forked their version of a template and kinda merged it with my old version to get it working. So far there haven't been any problems with it, except it seems I have to rerun cmake everytime I add a new file so it finds it for compilation. This might be due to the way I have it implemented, I'll have to see.

From what I understand, CMake is a full building system, so it is better suited for more complex programmes and makes handling things like different OSes easier. Overall a great choice I believe.

## Player and its movement

So I have managed to get it working and displaying shapes, now onto the movement.

I have some experience from previous projects, so I am aware of



