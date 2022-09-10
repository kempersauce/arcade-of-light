#pragma once

#include "animation/noise.h"                    // for NoiseAnimation
#include "animation/single_color_background.h"  // for SingleColorBG
#include "animation/starscape.h"                // for Starscape
#include "display/display.h"                    // for Display
#include "display/four_panel.h"                 // for FourPanelDisplay
#include "games/game.h"                         // for Game
#include "games/life/life.h"                    // for LifeGame
#include "games/rainbow/rainbow.h"              // for RainbowGame
#include "test/animation.h"                     // for AnimationTest

namespace kss {
namespace test {

class MultiGameTest : public games::Game {
  games::Game* games[4];

 public:
  MultiGameTest(display::FourPanelDisplay* gameDisplay)
      : Game{gameDisplay},
        games{(games::Game*)new test::AnimationTest{
                  gameDisplay->panels[0],
                  (animation::Animation*)new animation::NoiseAnimation{
                      gameDisplay->panels[0].size}},
              (games::Game*)new games::rainbow::RainbowGame{
                  gameDisplay->panels[1]},
              (games::Game*)new games::life::LifeGame{gameDisplay->panels[2]},
              (games::Game*)new test::AnimationTest{
                  gameDisplay->panels[3],
                  (animation::Animation*)new animation::Starscape{
                      gameDisplay->panels[3].size, 140}}} {}

  void setup() {
    for (auto game : games) {
      game->setup();
    }
  }

  void loop() {
    for (auto game : games) {
      game->loop();
    }
  }
};

}  // namespace test
}  // namespace kss
