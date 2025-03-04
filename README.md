# carnival-spaceship-simulator

Mini hardware project to create the electronic part belonging to a simulator (toy) of a spacecraft control panel.

## Background

My mother has always been a big fan of carnivals and costumes, and due to her current health condition, she is now confined to a wheelchair. We are trying to help her continue enjoying them by adapting the costume’s structure to the wheelchair. This year (2025), we’ve created an alien spaceship (UFO) costume.

## Requirements

### Hardware

- Raspberry PI Pico (RP2040) (or clone)

- TM1638 Model 1 (8 leds & 8 push buttons)

- PCM5102A (stereo DAC)

- Speakers

- Battery / 5 power adaptor (I am currently using a 12V battery from an UPS and a 12V to 5V adapter. The microcontroller, LEDs, and speakers are powered at 5V)

### Software dependencies

- TM1638plus by gavinlyonsrepo

- Bounce2 by thomasfredericks

- ESP8266Audio by earlephilhower
