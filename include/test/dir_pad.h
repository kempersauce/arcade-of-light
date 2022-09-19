#pragma once

#include "animation/hue_rainbow.h"              // for HueRainbow
#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/dir_pad.h"                   // for controls::DirPad
#include "display/display.h"                    // for Display
#include "games/game.h"                         // for Game
#include "serial/debug.h"                       // for Debug

namespace kss {
namespace test {

// Test for Directional Pad
class DirPadTest : public games::Game {
 public:
  controls::DirPad controls;
  animation::SingleColorBG* backgroundColor;
  animation::HueRainbow rainbow;

  DirPadTest(display::Display* gameDisplay, controls::DirPad controls)
      : Game(gameDisplay), controls{std::move(controls)}, rainbow(2) {
    rainbow.setWaveShift(true);
  }

  void setup() {}

  void loop() {
    if (controls.up->IsPressed()) {
      Debug("UP DIR BUTTON PRESSED");
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
      Debug("DOWN DIR BUTTON PRESSED");
      int newSpeed;
      int currentSpeed = rainbow.ShiftSpeed;
      if (currentSpeed > -20) {
        newSpeed = currentSpeed - 1;
      }

      rainbow.setSpeed(newSpeed);
      Debug("new speed:");
      // Debug(rainbow.ShiftSpeed);
    }

    if (controls.left->IsPressed()) {
      Debug("LEFT DIR BUTTON PRESSED");
    }

    if (controls.right->IsPressed()) {
      Debug("RIGHT DIR BUTTON PRESSED");
    }

    if (controls.a->IsPressed()) {
      rainbow.setWaveShift(true);
      Debug("B BUTTON PRESSED");
    }

    if (controls.b->IsPressed()) {
      rainbow.setWaveShift(false);
      Debug("A BUTTON PRESSED");
    }

    // if (!(//controls.a->IsPressed() &&
    // //controls.b->IsPressed() &&
    // controls.up->IsPressed() &&
    // controls.down->IsPressed() &&
    // controls.left->IsPressed() &&
    // controls.right->IsPressed()))
    // {
    //     //Debug("no Buttons pressed");
    // }

    rainbow.draw(display);
  }
};

}  // namespace test
}  // namespace kss
