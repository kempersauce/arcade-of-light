#pragma once

#include "controls/button.h"       // for Button
#include "display/display.h"       // for Display
#include "games/game.h"            // for Game
#include "games/life/animation.h"  // for LifeAnimation

namespace kss {
namespace games {
namespace life {

class GliderWarsGame : public Game {
  // Buttons
  controls::Button* randomizeButton1;
  controls::Button* randomizeButton2;

  controls::Button* gliderButton1;
  controls::Button* gliderButton2;

  // Animations
  LifeAnimation lifeGrid;

 public:
  GliderWarsGame(display::Display* display, controls::Button* randomize_1,
                 controls::Button* randomize_2, controls::Button* glider_1,
                 controls::Button* glider_2)
      : Game(display),
        randomizeButton1{randomize_1},
        randomizeButton2{randomize_2},
        gliderButton1{glider_1},
        gliderButton2{glider_2},
        lifeGrid{display->size.x, display->size.y} {}

  void setup() override {
    // start off randomized
    lifeGrid.randomize();
  }

  void loop() override {
    // Calculate new game state
    if (randomizeButton1->IsPressed() || randomizeButton2->IsPressed()) {
      lifeGrid.randomize();
    } else {
      lifeGrid.GoOneRound();
    }

    if (gliderButton1->IsDepressing()) {
      lifeGrid.setCellState(2, 1, true);
      lifeGrid.setCellState(2, 2, true);
      lifeGrid.setCellState(2, 3, true);
      lifeGrid.setCellState(3, 3, true);
      lifeGrid.setCellState(4, 2, true);
    }

    if (gliderButton2->IsDepressing()) {
      lifeGrid.setCellState(2, display->size.y - 2, true);
      lifeGrid.setCellState(2, display->size.y - 3, true);
      lifeGrid.setCellState(2, display->size.y - 4, true);
      lifeGrid.setCellState(3, display->size.y - 4, true);
      lifeGrid.setCellState(4, display->size.y - 3, true);
    }

    // Draw to display
    lifeGrid.draw(display);
  }
};

}  // namespace life
}  // namespace games
}  // namespace kss
