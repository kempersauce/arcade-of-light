#pragma once

#include "display/display.h"  // for Display
#include "games/game.h"  // for Game
#include <LifeAnimation.h>

#include <memory>  // For std::shared_ptr

#include "controls/button.h"

class GliderWarsGame : public Game {
  // Buttons
  std::shared_ptr<kss::controls::Button> randomizeButton1;
  std::shared_ptr<kss::controls::Button> randomizeButton2;

  std::shared_ptr<kss::controls::Button> gliderButton1;
  std::shared_ptr<kss::controls::Button> gliderButton2;

  // Animations
  LifeAnimation* lifeGrid;

 public:
  GliderWarsGame(Display* display,
                 std::shared_ptr<kss::controls::Button> randomize_1,
                 std::shared_ptr<kss::controls::Button> randomize_2,
                 std::shared_ptr<kss::controls::Button> glider_1,
                 std::shared_ptr<kss::controls::Button> glider_2)
      : Game(display),
        randomizeButton1{randomize_1},
        randomizeButton2{randomize_2},
        gliderButton1{glider_1},
        gliderButton2{glider_2} {
    lifeGrid = new LifeAnimation(display->numStrips, display->lengthStrips);
  }

  virtual void setup() {
    // start off randomized
    lifeGrid->randomize();
  }

  virtual void loop() {
    // Calculate new game state
    if (randomizeButton1->IsPressed() || randomizeButton2->IsPressed()) {
      lifeGrid->randomize();
    } else {
      lifeGrid->GoOneRound();
    }

    if (gliderButton1->IsDepressing()) {
      lifeGrid->setCellState(2, 1, true);
      lifeGrid->setCellState(2, 2, true);
      lifeGrid->setCellState(2, 3, true);
      lifeGrid->setCellState(3, 3, true);
      lifeGrid->setCellState(4, 2, true);
    }

    if (gliderButton2->IsDepressing()) {
      lifeGrid->setCellState(2, display->lengthStrips - 2, true);
      lifeGrid->setCellState(2, display->lengthStrips - 3, true);
      lifeGrid->setCellState(2, display->lengthStrips - 4, true);
      lifeGrid->setCellState(3, display->lengthStrips - 4, true);
      lifeGrid->setCellState(4, display->lengthStrips - 3, true);
    }

    // Draw to display
    lifeGrid->draw(display);
  }
};
