#pragma once

#include "animation/animation.h"  // for Animation
#include "animation/arrow.h"      // for Arrow
#include "animation/exploder.h"   // for Exploder
#include "animation/explosion.h"  // for Explosion
#include "animation/starscape.h"  // for Starscape
#include "controls/dir_pad.h"     // for DirPad
#include "games/game.h"           // for Game
#include "serial/debug.h"         // for Debug

namespace kss {
namespace games {
namespace rhythm {

namespace _rhythm_single {

const animation::Explosion kExploderPrototype{2, 350, 150,  25,  0,
                                              0,  0,   128, 160};

}  // namespace _rhythm_single
using namespace _rhythm_single;

class RhythmGameSingle : public Game {
  // Sticks
  // controls::DirPad controller;

  // Sounds

  // Animations
  animation::Starscape background;
  animation::Arrow arrow;
  animation::Exploder exploder;

 public:
  RhythmGameSingle(display::Display* display)
      : Game(display),
        background{display->size},
        exploder{kExploderPrototype, {display->size.x / 2, 35}, 50} {
    arrow.location.y = display->size.y + 5;
  }

  virtual void setup() override {}

  virtual void loop() override {
    arrow.location.y--;
    if (arrow.location.y == 0) {
      arrow.location.y = display->size.y + 5;
    }

    if (arrow.location.y <= 35) {
      exploder.Move();
    }

    background.draw(display);

    // Draw hit-line
    for (size_t x = 0; x < display->size.x; ++x) {
      display->Pixel(x, 35) = CRGB::White;
    }

    exploder.draw(display);
    arrow.draw(display);
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
