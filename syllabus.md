---
layout: page
title: Syllabus
description: >-
  Course policies and information.
---

<!-- {:.no_toc} -->

<!-- ## Table of contents

{: .no_toc .text-delta }

1. TOC
   {:toc} -->

---

## <center> Designing Your Voice: Synthetic Sounds from Circuits </center>

<center> Meeting Time: Mon. 9:30am-12pm </center>
<center> Location: 370 Jay St, 4th Floor, rm 408, ITP NYU </center> 
<center> Instructor: Jesse Simpson </center> 
<center> Email: Jesse.Simpson@nyu.edu </center> 
<center> Office Hours: In-Person: Mon, 12:15-2:15pm || Remote: Fri, 12:00-2:00pm </center>

![A gif where there are five rows of different shapes with a line at each of their center points. The line is rotating in a circle and follows the edge of the shape, measuring the distance. To the right, of the shape, a waveform is drawn, mapping the distance to an amplitude](assets/images/waveshapes.gif){:style="display:block; margin-left:auto; margin-right:auto" width="150"}

# **Course Description:**

In this 14-week course, students will explore sound design fundamentals through modular synthesizers, leveraging the capabilities of microcontrollers. Modular synthesizers are a type of electronic musical instrument used to generate, manipulate, and shape sound through the interconnection of individual modules, or components. This course is designed to equip students with the skills and creative prowess required to craft their own unique devices that adhere to the Eurorack design format; a popular modular synthesizer standard.

The curriculum blends the art of sound design with the technical aspects of hardware synthesizer architecture, building skills so that by the end of this course students will have the competence to bring their sonic visions to life in physical form through thoughtful interaction. By harnessing the modular nature of these components, students will work independently, taking into consideration the designs of their peers to ensure seamless compatibility between their devices, resulting in a distinct ‘voice’; a term used to describe a collection of components that define the signal path of a synthesizer.

The first half of the course will focus on sound design coding techniques utilizing the Teensy microcontroller, with the second half dedicated to developing tangible hardware design skills.

**This is a live document and will be updated over the course of the semester**

Pre-requisites: Intro to Physical Computing or equivalent experience. No sound design/experience in music is required.

# **Grading System:**

ITP has a pass/fail grading system, which will be awarded based on the following breakdown:

Participation & Attendance: 20%  
Homework Assignments/Documentation: 20%  
Midterm Project: 30%  
Final Project: 30%

Homework is due at the beginning of each class. You are expected to be prepared to present on the development of your work and to keep a blog.

**Class Pledge:** This document isn’t solely a roadmap of what we will accomplish over the course of the semester. It is an agreement between all of us to commit our efforts to seeing that it happens. My pledge as your instructor is to present these materials and do my best to help you succeed in understanding and implementing them in your work. Conversely I expect that you will do your best to learn and showcase your new skills in the project objectives.

Above all, we must respect each other’s opinions, abilities, backgrounds, and presence here at all times. Learning in a class setting is a collective experience. Let’s have an awesome semester!

# **Learning Objectives:**

Upon completion of this course you will have learned how to:

**Navigate the Teensy Audio Design Tool:** Demonstrate proficiency in using the Teensy Audio Design Tool to create and visualize signal flows, establishing the groundwork for your synthesizer design.

**Write Code Using the Audio Library:** Utilize the Teensy Audio library to implement essential sound design techniques within the specified signal flow, fostering a deeper understanding of audio processing and programming.

**Craft Eurorack-Formatted Hardware:** Design and assemble hardware devices adhering to the eurorack format.

**Scale Audio/CV Signals to/from Eurorack/Teensy Standards:** Scale audio and control voltage (CV) signals between Teensy and eurorack standards.

**Interface with External Systems:** Communicate with external software and hardware.

**Use Analog Components for Signal Processing:** Utilize analog components to create simple filters, and utility circuits to further manipulate and shape audio signals.

**Design Faceplates:** Develop your own faceplate for your module(s).

**Complete a Eurorack Module:** Produce at least one eurorack module, creating a tangible component of a larger modular synthesizer system.

**Key Course Dates:**
2/19: No class due to President’s Day
3/11: Midterm Presentations
3/18: No class due to Spring Break
5/6: Final Presentations

**Note:** This course requires hardware circuitry/fabrication materials throughout the semester. ITP has lots of things to borrow and also scavenge. If you are unable to financially support your project for this class please see me and we can hopefully find an alternative arrangement.

## Week by Week

**Week 1: Introductions, History of Synthesis, and Introduction to Sine Waves**

- Syllabus review
- Synthesis Overview
  - History of Synthesis
  - Hardware synthesizers
  - Modular Synthesis
  - Analog vs. Digital Synthesis
  - Software Synthesizers
  - Embedded audio
- Intro to Sine Waves

**Homework:**

**Watch:**  
1970 Moog Synthesizer - Wendy Carlos  
Oscillators and Filters (Only watch 3:57-5:30) - Berklee Online

**Recommended Listening:**  
Silver Apples of the Moon – Morton Subotnick
Switched on Bach - Wendy Carlos https://www.moogmusic.com/media/switched-bach-how-world-met-moog

**Get:** Obtain a Teensy 4.0 or Teensy 4.1 (only one of them), and an audio shield. There are some available in the shop to checkout for short term use however we will need them on an ongoing basis. I recommend buying your teensy without pins so that you have more flexibility in your design. Mine will be configured in the manner below, with female headers on the teensy to allow for the shield to sit on top of it.

{INSERT PHOTO}

This class will be taught primarily using a teensy 4.1 with Audio Shield. You are welcome to use a different teensy with/without the audio shield, or alternate microcontroller altogether, with the understanding that this class is structured to support the hardware mentioned above. I will do my best to support alternative platforms.

:**Write::** Write a blog post on your experience with sound, and your interests in building synthesizers. Feel free to discuss your personal tastes/aesthetics that you’re drawn to. Everyone will present for 3-5 mins in Week 2. In later weeks, not everyone will present.

**Optional Prompts:**
On day 1, how do you envision your final project? What do you want to create in this class?

Describe your favorite and least favorite sounds. What do they sound like and how do they make you feel? Imagine that you are describing them to someone who hasn’t heard them before and be as descriptive as possible.

Who are some musicians/composers who you admire?

Talk about interesting sounds from your daily life. What memories or feelings do you associate with these sounds?

**Week 2: Elements of a Synth Voice: Oscillators and Filters**
Teensy hardware
Intro to Teensy Audio Design Tool and Library
Oscillators
Filters
In-Class Activity: Fabricate a physical instrument using items from the floor that uses the concepts of oscillators and filters

**Homework:**

Watch:

**Recommended Listening:**
Geogaddi – Boards of Canada

**Make:** Construct a design using the Teensy Audio Design Tool that incorporates an oscillator(s), filter, and optionally a mixer object, and a corresponding hardware circuit to control elements of it using analog sensors. Document your work using a blog post.

**Week 3: Elements of a Voice: Modulation (VCAs, LFOs, Envelopes)**
Modulation: Control Signals
Voltage Controlled Amplifiers
Low Frequency Oscillators
ADSR Envelopes
In-Class Activity - **\*\*\*\***

Homework:

Watch: LFOs, VCAs, Modulation (watch in full) - Berklee Online

Recommended Listening:
Guardian Suite - Lightbath

Make: Build off of your sketch from last week to incorporate an envelope, VCA, and LFO. Build upon your breadboard circuit to control elements of them using sensors. Document your work using a blog post.

Week 4: Elements of a Voice: Basic Effects
Delay
Reverb
Wavefolder
Bitcrusher

Homework:

Watch:

Alessandro Cortini - In the Studio

Recommended Listening:
Construct Contrast - Geskia!
Everything Ends Here - Blind Old Freak (Alessandro Cortini) & Don Buchla

Make: Build off of your sketch from last week to incorporate an effect, or series of effects. Explore the ones that we didn’t look at in class; Experiment with changing the order that you connect them. How does that change the resulting voice? Document your work using a blog post. Sketch out ideas for your midterm (and/or final) project. What are you hoping to achieve and how will it help to extend your musical self expression?

Week 5: Intermediate Sound design / Sampling
Sampling
Wavetable Synthesis?
Foley - Field Recording
Activity: With a partner, use a zoom recorder, or phone, to record samples around the floor. Manipulate them using Audacity and load them into a teensy synth design using either wav2sketch, or the SD Card. Play them for the class.

Homework:

Watch:
Recommended Listening:
Emergence - Shuta Hasunuma
Make: Work toward your midterm project and prepare for play testing. Document your progress in a blog post.

Week 6: Play Testing / Midterm Work Session

Homework:

Make: Prepare for your midterm presentation

Week 7: Midterm Presentations

Homework:

Think: Enjoy Spring Break! Think about the directions you can take your project in for weeks 8-14!

Week 8: MIDI / Intro to (Western) Music Theory / Intro to Eurorack
Intro to MIDI
Intro to (Western) Music Theory
Notes/Scales/Chords/Rhythms/Song Structure
Intro to Eurorack
Electrical design standards
Power Supply?
Physical design standards
External Power

Week 9: Eurorack Outputs - Control Voltage / Gates / DACs / Signal Scaling
Control Voltage Out
Gates - Triggering External Gear
Digital to Analog Converters
Signal Scaling Down to Teensy Standards
Week 10: Eurorack Inputs - Audio in / CV in / Effects pedals / Signal Scaling
Signal Scaling Up to Eurorack Standards
Audio-In
Control Voltage In
Effects Pedals

Week 11: Fabrication + Power Planning
Fabricating on Perfboard
Designing/Fabricating a Faceplate

Week 12: Analog Effects & Utilities
RC Filter
Spring Delay
Analog VCA
Vactrols

Week 13: Play testing / Work Session
Week 14: Final Presentations

ITP Code of Conduct

As with all activities at ITP and IMA, we’ll be following the ITP/IMA code of conduct. Please consider it as a guide for projects you might make or see in this class, and how we behave with respect to each other in class.

Statement of Academic Integrity

Plagiarism is presenting someone else’s work as though it were your own. More specifically, plagiarism is to present as your own: A sequence of words or programming code or images quoted without quotation marks from another writer or a paraphrased passage from another writer’s work or facts, ideas or images composed by someone else.

Statement of Principle

The core of the educational experience at the Tisch School of the Arts is the creation of original academic and artistic work by students for the critical review of faculty members. It is therefore of the utmost importance that students at all times provide their instructors with an accurate sense of their current abilities and knowledge in order to receive appropriate constructive criticism and advice. Any attempt to evade that essential, transparent transaction between instructor and student through plagiarism or cheating is educationally self-defeating and a grave violation of Tisch School of the Arts community standards. For all the details on plagiarism, please refer to page 10 of the Tisch School of the Arts, Policies and Procedures Handbook.

Statement on Accessibility

Please feel free to make suggestions to your instructor about ways in which this class could become more accessible to you. Academic accommodations are available for students with documented disabilities. Please contact the Moses Center for Students with Disabilities at 212 998-4980 for further information.

Statement on Counseling and Wellness

Your health and safety are a priority at NYU. If you experience any health or mental health issues during this course, we encourage you to utilize the support services of the 24/7 NYU Wellness Exchange 212-443-9999. Also, all students who may require an academic accommodation due to a qualified disability, physical or mental, please register with the Moses Center 212-998-4980. Please let your instructor know if you need help connecting to these resources.
