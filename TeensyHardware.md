---
layout: page
title: 4. Teensy Hardware & Setup
description: Recommended Hardware for this Course
---

# Hardware & Setup

The first half of this class is taught using the [Teensy 4.1](https://www.pjrc.com/store/teensy41.html) and [Teensy 4.x Audio Shield](https://www.pjrc.com/store/teensy3_audio.html). I recommend purchasing these boards without pre-soldered pins so that you have more flexibility in how you will use them. Here is my example configuration that is flexible and compact.

# **Teensy 4.1 with 'Extra Long' Stacking Female Headers**

Solder [extra long stacking header pins](https://www.adafruit.com/product/5582) to your Teensy 4.x board. The solder should be on the bottom side of the board. You may need to sand down the adjacent edges of the headers to get them to seat properly next to each other. For the Teensy 4.0 you will need 2 sets of 14x1 headers, and for the Teensy 4.1, you will need 2 sets of 24x1 headers.

**Do not snip off the excess pin length!!**

We are using these extra long pins so that it will be possible to insert the pins into a breadboard, and also stack the audio board on top of the teensy itself.

![The Teensy 4.1 board with unsoldered stacking female header pins lying next to it on a table showing that the pins are longer than standard hearders](assets/images/teensy4_1withPins.JPG)

![The Teensy 4.1 board with soldered stacking female header pins](assets/images/teensy4_1_withHeaders.jpg)

# **Teensy 4.x Audio Shield with Standard Male Headers**

Solder standard [2.54mm male headers](https://www.amazon.com/Jabinco-Breakable-Header-Connector-Arduino/dp/B0817JG3XN/) to your Teensy 4.x Audio Shield. The short part of the pin should be on the top of the board, with the longer part below. The solder joint goes on top of the board.

![The Teensy 4.x audio shield with unsoldered header pins lying next to it on a table showing that the pins are longer than standard headers](assets/images/teensy4_x_audioBoardWithPins.JPG)

![The Teensy 4.x audio shield with soldered header pins](assets/images/teensyAudioShieldWithHeaders.jpg)

# **Assembly for Prototyping**

Insert the Teensy 4.x into a breadboard.

![The Teensy 4.1 inserted into a breadboard](assets/images/teensy4_1_breadBoard.JPG)

Stack the Audio Shield on top of it. This configuration allows for prototyping on a breadboard while remaining compact, and also leaves the possibility of using the boards in different contexts down the road.

![The Teensy 4.x audio shield stacked on top of a Teensy 4.1 which is inserted into a breadboard](assets/images/teensy4_1_withAudioBoardStacked.JPG)

![The Teensy 4.x audio shield stacked on top of a Teensy 4.1](assets/images/teensy4_1_andAudioshield.JPG)

![A closeup image of the teensy 4.x audio shield stacked on top of a Teensy 4.1, which is then inserted into a breadboard](assets/images/teensy4_1_audioBoardInBreadboard.jpeg)
