/**************************************************************************\
* Pinoccio Library                                                         *
* https://github.com/Pinoccio/library-pinoccio                             *
* Copyright (c) 2014, Pinoccio Inc. All rights reserved.                   *
* ------------------------------------------------------------------------ *
*  This program is free software; you can redistribute it and/or modify it *
*  under the terms of the MIT License as described in license.txt.         *
\**************************************************************************/
#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <GS.h>
#include <bitlash.h>
#include <lwm.h>
#include <js0n.h>

#include "version.h"

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int command = 0;

void setup() {
  Scout.setup(SKETCH_NAME, SKETCH_REVISION, SKETCH_BUILD);
  digitalWrite(VCC_ENABLE, HIGH);
  // Add custom setup code here
  Serial.begin(115200);
  Serial1.begin(115200);
   
  inputString.reserve(200);
}

void loop() {
  Scout.loop();
  
  while (Serial1.available()) {
    // get the new byte:
    int inChar = Serial1.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == 0) {
      stringComplete = true;
    } else {
      // add it to the inputString:
      inputString += inChar;
    }
  }
  
  if(stringComplete) {
    // print the string when a newline arrives:
    Serial.print("Command received:\t");
    //Serial.print(inputString);
    //Serial.print("\t");
    command = inputString.toInt();
    Serial.print(command);
    Serial.print("\t");
    switch(command) {
      case 1: Serial.println("on");
                Shell.eval("command.scout(2, \"neopix.on\")");
                Led.blinkWhite(1000);
              break;
      case 2: Serial.println("off");
                Shell.eval("command.scout(2, \"neopix.off\")");
                Led.turnOff();
              break;
      case 3: Serial.println("left");
                Shell.eval("command.scout(2, \"neopix.lsnake\")");
                Led.turnOff();
                Led.blinkRed(1000);
              break;
      case 4: Serial.println("right");
                Shell.eval("command.scout(2, \"neopix.rsnake\")");
                Led.turnOff();
                Led.blinkRed(1000);
              break;
      case 5: Serial.println("flash");
                Shell.eval("command.scout(2, \"neopix.flash\")");
                Led.red();
                delay(500);
                Led.turnOff();
                delay(500);
                Led.red();
                delay(500);
                Led.turnOff();
              break;
      case 6: Serial.println("red");
                Shell.eval("command.scout(2, \"neopix.red\")");
                Led.red();
              break;
      case 7: Serial.println("green");
                Shell.eval("command.scout(2, \"neopix.green\")");
                Led.green();
              break;
      case 8: Serial.println("blue");
                Shell.eval("command.scout(2, \"neopix.blue\")");
                Led.blue();
              break;
      case 9: Serial.println("white");
                Shell.eval("command.scout(2, \"neopix.white\")");
                Led.white();
              break;
      case 10: Serial.println("bonjour");
                Shell.eval("command.scout(2, \"neopix.bonjour\")");
                Led.blinkWhite(1000);
                Led.blinkBlue(1000);
                Led.blinkGreen(1000);
                Led.blinkRed(1000);
              break;
       default:
              break;
    }

    inputString = "";
    stringComplete = false;
  }
}

void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    int inChar = Serial1.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == 0) {
      stringComplete = true;
    } else {
      // add it to the inputString:
      inputString += inChar;
    }
  }
}
