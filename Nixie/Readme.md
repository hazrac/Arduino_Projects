# Nixie Tube Display
## Intro
I have 6 Nixie Tubes and I'm looking to make a universal display that I can feed any 6 digit number to and have it be displayed on the tubes.

I've considered putting a wifi board in the project as well as a real time clock, but haven't come to a decision yet.

## ToDate
I have one SN74HC595N connected to two Russian 74141s and driving two of the six nixie tubes.  This is all done on a breadboard.

## Theory / Notes
You'll notice in the [Nixie Countdown](https://github.com/hazrac/Arduino_Projects/blob/master/Nixie/Nixie_coutdown/Nixie_coutdown.ino) testing code that there is an array defined:
 
```int charTable[] = {0,128,64,192,32,160,96,224,16,...```

The author made a refrence table allowing them to call ```charTable[number]``` and get the 8-bit byte back that would represent that ```number```. In this code example they are using LSBFIRST with the shiftOut() function.  This means that 2^7 (or 128) represents the 8th place of the binary number. Hence "128" represents 00000001.  This translates into activating the correct pin(s) on the 74141 to ground the correct digit.

## ToDo
* Create three seperate "master" functions to control the three shift registeres (which will, in turn, be connected to 6 Nixie Tubes). These will take a two digit number and display those on the set of two Nixie Tubes that shift register controls.
* Define an overall function where you can pass a 6 digit number and it calls the master functions to display the number.
* Look at adding a wifi board and a function to call an API that provides a given number.
* Add a rotating knob and piezo buzzer to select between APIs and/or RTC to display info.

## Refrences
* [SN74HC595N datasheet](http://www.ti.com/lit/ds/symlink/sn74hc595.pdf)
* [Shift registers, how they work, and binary](http://www.cs.uregina.ca/Links/class-info/207/Lab8/)
* The [shiftOut()](https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/) function in Arduino
* [SN74141 datasheet](https://neon1.net/nixieclock/sn74141.pdf)
* [Truth Table](http://g3ynh.info/digrdout/74141.html) for the 74141
* [Arduino shift register walkthrough](https://www.arduino.cc/en/tutorial/ShiftOut)

### Other Nixie Projects for Refrence
* [Shift Registers and Nixie Tubes - good visuals](http://jafrog.com/2014/08/30/testing-a-shift-register.html)
* [Testing Two Nixie Tubes](http://www.instructables.com/id/Driving-two-Nixie-tubes-with-an-Arduino-via-a-shif/)
* [Instructable with a RTC](http://www.instructables.com/id/Arduino-Nixie-Clock-for-Absolute-Beginners/)
* [Lightweight overview, but good tables](https://idyl.io/arduino/how-to/control-a-nixie-tube-with-arduino/)
* [Full PCB Design](http://www.instructables.com/id/simple-user-adjustable-DIY-Nixie-Clock/)

## Contact
David Mitchell / dmitchell at hazrac.org / [hazrac.org](http://www.hazrac.org) / @hazrac
