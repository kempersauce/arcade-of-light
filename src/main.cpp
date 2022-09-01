// // hopefully this makes sound work
// // #define FASTLED_ALLOW_INTERRUPTS 0

// #include "animation/noise.h"                // for NoiseAnimation
// // #include "audio/sounds.h"                   // for Sounds
// #include "display/display.h"                // for Display
// #include "display/five.h"                   // for FiveDisplay
// #include "display/four_panel.h"             // for FourPanelDisplay
// #include "display/h2h.h"                    // for H2HDisplay
// #include "display/octo_display.h"           // for OctoDisplay
// #include "display/rocket.h"                 // for RocketDisplay
// #include "display/standard_display.h"       // for StandardDisplay
// #include "display/twenty.h"                 // for TwentyDisplay
// #include "display/twenty_standard.h"        // for TwentyDisplayStandard
// #include "engines/framerate.h"              // for FrameRate
// #include "games/falling/falling.h"          // for FallingGame
// #include "games/head2head/head2head.h"      // for Head2Head
// #include "games/lane_runner/lane_runner.h"  // for LaneRunner
// #include "games/life/glider_wars.h"         // for GliderWars
// #include "games/life/life.h"                // for LifeGame
// #include "games/life/single_player.h"       // for LifeGameSinglePlayer
// #include "games/marquee/marquee.h"          // for MarqueeGame
// #include "games/noise/noise.h"              // for NoiseGame
// #include "games/rainbow/rainbow.h"          // for RainbowGame
// #include "games/rainbow/rainbow_static.h"   // for RainbowStatic
// #include "games/rocket/rocket_game.h"       // for RocketGame
// #include "games/shooter/shooter_game.h"     // for ShooterGame
// #include "games/snake/snake_game.h"         // for SnakeGame
// // #include "games/wav_player/wav_player.h"    // for WavPlayer
// #include "serial/debug.h"           // for serial debugging
// #include "test/animation.h"         // for AnimationTest
// #include "test/dir_pad.h"           // for DirPadTest
// #include "test/five_strip.h"        // for FiveStripTest
// #include "test/multi_game.h"        // for MultiGameTest
// #include "test/serial.h"            // for SerialTest
// #include "test/single_animation.h"  // for SingleAnimation
// #include "test/single_color.h"      // for SingleColorTest

// using namespace kss;

// engines::FrameRate frameRate;

// games::Game* game;
// display::Display* gameDisplay;

// void setup() {
//   // This only works if we're not using octo
//   // FastLED.setBrightness(100);

//   Serial.begin(115200);
//   debug::println("Begin setup()");

//   // Choose your Display type
// //   gameDisplay = (display::Display*)new display::FiveDisplay();
//   gameDisplay = (display::Display*)new display::FourPanelDisplay();
// //   gameDisplay = (display::Display*)new display::H2HDisplay();
// //   gameDisplay = (display::Display*)new display::RocketDisplay();
// //   gameDisplay = (display::Display*)new display::TwentyDisplay();
// //   gameDisplay = (display::Display*)new display::TwentyDisplayStandard();

//   debug::println("gameDisplay created");

//   // Choose your Game type
// //   game = (games::Game*)new games::h2h::Head2Head(gameDisplay);
// //   game = (games::Game*)new games::life::LifeGame(gameDisplay);
// //   game = (games::Game*)new games::rocket::RocketGame(gameDisplay);
// //   game = (games::Game*)new games::rainbow::RainbowStatic(gameDisplay);
// //   game = (games::Game*)new games::marquee::MarqueeGame(gameDisplay);
// //   game = (games::Game*)new games::snake::SnakeGame(gameDisplay);
// //   game = (games::Game*)new games::shooter::ShooterGame(gameDisplay);
// //   game = (games::Game*)new games::falling::FallingGame(gameDisplay);
// //   game = (games::Game*)new games::lane_runner::LaneRunnerGame(gameDisplay);
// //   game = (games::Game*)new games::life::LifeGameSinglePlayer(gameDisplay);

//   // Test Games
// //   game = (games::Game*)new test::DirPadTest(gameDisplay);
// //   game = (games::Game*)new test::FiveStripTest(gameDisplay);
// //   game = (games::Game*)new games::life::GliderWarsGame(gameDisplay);
// //   game = (games::Game*)new test::AnimationTest(gameDisplay);
//   game = (games::Game*)new test::MultiGameTest{
//       (display::FourPanelDisplay*)gameDisplay};

//   // Animation Test game
// //   animation::Animation* test_animation =
// //       (animation::Animation*)new animation::NoiseAnimation{
// //           gameDisplay->strip_count, gameDisplay->strip_length};
// //   game = (games::Game*)new test::SingleAnimation(gameDisplay, test_animation);

//   debug::println("game created");

//   game->setup();
//   debug::println("game setup complete");

//   debug::println("End setup()");

//   // TODO should we show LEDs on setup?
//   gameDisplay->Show();
// }

// void loop() {
//   //   debug::println("loop() entered");

//   game->loop();

//   //   debug::println("loop() Show Display");
//   gameDisplay->Show();

//   //   debug::println("loops brother");
//   frameRate.PrintFrameRate();
// }
