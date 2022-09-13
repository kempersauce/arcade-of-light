#pragma once

#include "animation/animation.h"  // for Animation
#include "animation/arrow.h"      // for Arrow
#include "animation/exploder.h"   // for Exploder
#include "animation/explosion.h"  // for Explosion
#include "animation/splotch.h"    // for Splotch
#include "animation/starscape.h"  // for Starscape
#include "controls/dir_pad.h"     // for DirPad
#include "games/game.h"           // for Game
#include "serial/debug.h"         // for Debug

namespace kss {
namespace games {
namespace rhythm {

namespace _rhythm_single {

const animation::Explosion kExploderPrototype{2, 350, 150, 25, 0,
                                              0, 0,   128, 160};

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

  animation::Splotch splotch_red;
  animation::Splotch splotch_blue;
  animation::Splotch splotch_green;
  animation::Splotch splotch_yellow;

 public:
  RhythmGameSingle(display::Display* display)
      : Game(display),
        background{display->size},
        exploder{kExploderPrototype, {display->size.x / 2, 35}, 50},
        splotch_red{{display->size.x, 20}, {0, 2 * display->size.y / 6}, 0},
        splotch_blue{{display->size.x, 20}, {0, 3 * display->size.y / 6}, 171},
        splotch_green{{display->size.x, 20}, {0, 4 * display->size.y / 6}, 78},
        splotch_yellow{
            {display->size.x, 20}, {0, 5 * display->size.y / 6}, 43} {
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

    splotch_red.Move();
    splotch_blue.Move();
    splotch_green.Move();
    splotch_yellow.Move();

    splotch_red.draw(display);
    splotch_blue.draw(display);
    splotch_green.draw(display);
    splotch_yellow.draw(display);

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
