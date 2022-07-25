#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h" // for Display

class FinishLine : public kss::animation::Animation {
 public:
  int Loc;
  int Stripes[5][4] = {0, 1, 0, 1, 0 1, 0, 1, 0, 1 0, 1, 0, 1, 0 1, 0, 1, 0, 1};

  // Constructor
  Target(int loc) : Animation() { Loc = loc; }

  void draw(Display* display) {}
};
