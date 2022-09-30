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
  virtual void Move(){};  // default empty since not all need this
  virtual void Draw(display::Display* display);
};

}  // namespace animation
}  // namespace kss
