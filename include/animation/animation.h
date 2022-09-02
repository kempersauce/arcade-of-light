#pragma once

/*
Animation class
Make the pretty lights
Make the lights pretty
*/

#include "display/display.h"  // for Display

namespace kss {
namespace animation {

class Animation {
 public:
  virtual void draw(display::Display* display);
  virtual void Move(){};  // default empty since not all need this
};

}  // namespace animation
}  // namespace kss
