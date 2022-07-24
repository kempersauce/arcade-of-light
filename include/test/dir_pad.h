#pragma once

#include <Constants.h>
#include "games/game.h"  // for Game

#include "animation/dot.h"                      // for Dot
#include "animation/hue_rainbow.h"              // for HueRainbow
#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/dir_pad.h"                   // for kss::controls::DirPad

// Test for Directional Pad
class DirPadTest : Game {
 public:
  kss::controls::DirPad controls;
  Dot* player;
  SingleColorBG* backgroundColor;
  HueRainbow rainbow;

  DirPadTest(Display* gameDisplay, kss::controls::DirPad controls)
      : Game(gameDisplay), controls{std::move(controls)}, rainbow(2) {
    rainbow.setWaveShift(true);
  }

  void setup() {}

  void loop() {
    if (controls.up->IsPressed()) {
      Serial.println("UP DIR BUTTON PRESSED");
      int newSpeed;
      int currentSpeed = rainbow.ShiftSpeed;
      if (currentSpeed < 20) {
        newSpeed = currentSpeed + 1;
      } else {
        newSpeed = 20;
      }

      rainbow.setSpeed(newSpeed);
    }

    if (controls.down->IsPressed()) {
      Serial.println("DOWN DIR BUTTON PRESSED");
      int newSpeed;
      int currentSpeed = rainbow.ShiftSpeed;
      if (currentSpeed > -20) {
        newSpeed = currentSpeed - 1;
      }

      rainbow.setSpeed(newSpeed);
      Serial.println("new speed:");
      // Serial.println(rainbow.ShiftSpeed);
    }

    if (controls.left->IsPressed()) {
      Serial.println("LEFT DIR BUTTON PRESSED");
    }

    if (controls.right->IsPressed()) {
      Serial.println("RIGHT DIR BUTTON PRESSED");
    }

    if (controls.a->IsPressed()) {
      rainbow.setWaveShift(true);
      Serial.println("B BUTTON PRESSED");
    }

    if (controls.b->IsPressed()) {
      rainbow.setWaveShift(false);
      Serial.println("A BUTTON PRESSED");
    }

    // if (!(//controls.a->IsPressed() &&
    // //controls.b->IsPressed() &&
    // controls.up->IsPressed() &&
    // controls.down->IsPressed() &&
    // controls.left->IsPressed() &&
    // controls.right->IsPressed()))
    // {
    //     //Serial.println("no Buttons pressed");
    // }

    rainbow.draw(display);
  }
};
