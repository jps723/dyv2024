---
title: Week 4
---

Feb 12
: Elements of a Voice: Basic Effects & Line Levels

- Delay
- Reverb
- Wavefolder
- Bitcrusher
- Line Level In/Out

### Homework:

Watch:

[Alessandro Cortini - In the Studio](https://www.youtube.com/watch?v=BUtnzGeXUaQ)

Recommended Listening:
[Everything Ends Here - Blind Old Freak (Alessandro Cortini) & Don Buchla](https://www.youtube.com/watch?v=J89IY3Ss2Mk)
[Construct Contrast - Geskia!](https://www.youtube.com/watch?v=2Dmd-Oi-UU0)

Work with your partner to: 

a) Create a synth on each of your microcontrollers incorporating the concepts we've been covering: oscillators, filters, modulation, (an effect? As mentioned, some in the library are more accessible than others - if you have questions or run into trouble, I'm available to help), etc. Work together so that your synths have complementary characteristics; I.e. one person makes a droning pad, and the other makes more percussive sounds. Or two drones with complementary tunings. Instead of a button press to trigger your notes, how else might you try to code them and add rhythm? 

b) Give your synth more musical context: add more buttons and program each one to play a specific frequency/note. Replicate your signal flow for each button/note, and mix them together using a mixer object. You can tune each note using this chart, strategically. Tune them using the techniques we've discussed in class, or explore a scale. We haven't discussed this yet in class but we will when we get back. Explore ADSR envelope shapes and make them adjustable, or evolving over time. 

c) Go modular 🤘: Deconstruct the synth voice(s) that we've been building into smaller components and 'patch' the audio from one teensy to another using the line level ins/outs. Think of each teensy as a module that serves a specific function. Right now we are only passing audio signals, but how might you be able to extend this concept to modulation signals down the road? Until then, can you code a Sine wave LFO to modulate the frequency of a teensy oscillator since we're not yet able to use external signals? 
