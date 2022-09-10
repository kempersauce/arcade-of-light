// hopefully this makes sound work
// #define FASTLED_ALLOW_INTERRUPTS 0

#include <vector>  // for vector

#include "animation/fireworks_show.h"       // for FireworksShow
#include "animation/noise.h"                // for NoiseAnimation
#include "display/display.h"                // for Display
#include "display/five.h"                   // for FiveDisplay
#include "display/four_panel.h"             // for FourPanelDisplay
#include "display/h2h.h"                    // for H2HDisplay
#include "display/octo_display.h"           // for OctoDisplay
#include "display/rocket.h"                 // for RocketDisplay
#include "display/standard_display.h"       // for StandardDisplay
#include "display/twenty.h"                 // for TwentyDisplay
#include "display/twenty_standard.h"        // for TwentyDisplayStandard
#include "engines/framerate.h"              // for FrameRate
#include "games/falling/falling.h"          // for FallingGame
#include "games/head2head/head2head.h"      // for Head2Head
#include "games/lane_runner/lane_runner.h"  // for LaneRunner
#include "games/life/glider_wars.h"         // for GliderWars
#include "games/life/life.h"                // for LifeGame
#include "games/life/single_player.h"       // for LifeGameSinglePlayer
#include "games/marquee/marquee.h"          // for MarqueeGame
#include "games/noise/noise.h"              // for NoiseGame
#include "games/rainbow/rainbow.h"          // for RainbowGame
#include "games/rainbow/rainbow_static.h"   // for RainbowStatic
#include "games/rhythm/rhythm_game.h"       // for RhythmGame
#include "games/rhythm/rhythm_single.h"     // for RhythmGameSingle
#include "games/rocket/rocket_game.h"       // for RocketGame
#include "games/shooter/shooter_game.h"     // for ShooterGame
#include "games/snake/snake_game.h"         // for SnakeGame
#include "serial/debug.h"                   // for serial debugging
#include "test/animation.h"                 // for AnimationTest
#include "test/dir_pad.h"                   // for DirPadTest
#include "test/five_strip.h"                // for FiveStripTest
#include "test/multi_game.h"                // for MultiGameTest
#include "test/serial.h"                    // for SerialTest
#include "test/single_color.h"              // for SingleColorTest

using namespace kss;

engines::FrameRate frameRate;

games::Game* game;
display::FourPanelDisplay* gameDisplay;

void setup() {
  // This only works if we're not using octo
  // FastLED.setBrightness(100);

  debug::Init();
  Debug("Begin setup()");

  // Choose your Display type
  //   gameDisplay = (display::Display*)new display::FiveDisplay();
    gameDisplay = new display::FourPanelDisplay();
  //   gameDisplay = (display::Display*)new display::H2HDisplay();
  //   gameDisplay = (display::Display*)new display::RocketDisplay();
//   gameDisplay = (display::Display*)new display::TwentyDisplay();
  //   gameDisplay = (display::Display*)new display::TwentyDisplayStandard();

  Debug("gameDisplay created");

  // Choose your Game type
  //   game = (games::Game*)new games::h2h::Head2Head(*gameDisplay);
  //   game = (games::Game*)new games::life::LifeGame(*gameDisplay);
  //   game = (games::Game*)new games::rainbow::RainbowGame(*gameDisplay);
  //   game = (games::Game*)new games::rainbow::RainbowStatic(*gameDisplay);
  //   game = (games::Game*)new games::rocket::RocketGame(*gameDisplay);
  //   game = (games::Game*)new games::marquee::MarqueeGame(*gameDisplay);
  //   game = (games::Game*)new games::snake::SnakeGame(*gameDisplay);
  //   game = (games::Game*)new games::shooter::ShooterGame(*gameDisplay);
  //   game = (games::Game*)new games::falling::FallingGame(*gameDisplay);
  //   game = (games::Game*)new games::lane_runner::LaneRunnerGame(*gameDisplay);
  //   game = (games::Game*)new games::life::LifeGameSinglePlayer(*gameDisplay);

  // Rhythm Games
  //   game = (games::Game*)new games::rhythm::RhythmGameSingle(((display::FourPanelDisplay*)gameDisplay)->panels[0]);

  Debug("Creating game...");
  game = (games::Game*)new games::rhythm::RhythmGameSingle(&gameDisplay->panels[0]);

  // Test Games
  //   game = (games::Game*)new test::DirPadTest(*gameDisplay);
  //   game = (games::Game*)new test::FiveStripTest(*gameDisplay);
  //   game = (games::Game*)new games::life::GliderWarsGame(*gameDisplay);
  //   game = (games::Game*)new test::MultiGameTest{
  //       *(display::FourPanelDisplay*)gameDisplay};

  // Animation Test game
//   std::vector<animation::Animation*> test_animations{
//       (animation::Animation*)new animation::Starscape{gameDisplay->size, 140},
//       (animation::Animation*)new animation::FireworksShow{gameDisplay->size,
//                                                           15}};

//   game = (games::Game*)new test::AnimationTest(*gameDisplay, test_animations);

  Debug("game created");

  game->setup();
  Debug("game setup complete");

  Debug("End setup()");

  // TODO should we show LEDs on setup?
  gameDisplay->Show();
}

void loop() {
  //   Debug_here();

  game->loop();

  //   Debug("Show Display");
  gameDisplay->Show();

  //   Debug("loops brother");
  // frameRate.PrintFrameRate();

  delay(20);
}
