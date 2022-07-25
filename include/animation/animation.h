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
  virtual void draw(Display* display);
};

}  // namespace animation
}  // namespace kss
