// hopefully this makes sound work
// #define FASTLED_ALLOW_INTERRUPTS 0

#include "display/display.h"               // for Display
#include "display/octo_display.h"          // for OctoDisplay
#include "display/standard_display.h"      // for StandardDisplay
#include "display/five.h"               // for FiveDisplay
#include "display/h2h.h"                // for H2HDisplay
#include "display/rocket.h"             // for RocketDisplay
#include "display/twenty.h"             // for TwentyDisplay
#include "engines/framerate.h"  // for FrameRate
// #include "games/head2head/head2head.h"  // for Head2Head
// #include "games/rocket/rocket_game.h"   // for RocketGame
// #include "games/wav_player/wav_player.h"  // for WavPlayer
// #include "games/life/life.h"    // for LifeGame
// #include "test/single_color.h"  // for SingleColorTest
// #include "audio/sounds.h"  // for Sounds
// #include "test/firework.h"  // for FireworkTest
// #include "games/life/glider_wars.h"  // for GliderWars
// #include "games/marquee/marquee.h"           // for MarqueeGame
// #include "games/noise/noise.h"  // for NoiseGame
#include "games/rainbow/rainbow.h"           // for RainbowGame
// #include "games/snake/snake_game.h"  // for SnakeGame
// #include "test/animation.h"            // for AnimationTest
// #include "test/dir_pad.h"            // for DirPadTest
// #include "test/five_strip.h"         // for FiveStripTest
// #include "test/serial.h"             // for SerialTest
// #include "test/single_color.h"             // for SingleColorTest
// #include "games/shooter/shooter_game.h"  // for ShooterGame
// #include "games/falling/falling.h"                  // for FallingGame
// #include "games/lane_runner/lane_runner.h"  // for LaneRunner
// #include "games/life/single_player.h"  // for LifeGameSinglePlayer
// #include "test/animation.h"                 // for AnimationTest

using namespace kss;

engines::FrameRate frameRate;

games::Game* game;
display::Display* gameDisplay;

void setup() {
  // FastLED.setBrightness(100);

  // init audio stuff
  // audio::initAudio();

  Serial.begin(9600);
  Serial.println("Begin setup()");

  // Choose your Display type
  // gameDisplay = (display::Display*)new display::FiveDisplay();
  // gameDisplay = (display::Display*)new display::H2HDisplay();
  // gameDisplay = (display::Display*)new display::RocketDisplay();
    gameDisplay = (display::Display*)new display::TwentyDisplay();

  Serial.println("gameDisplay created");

  // Choose your Game type
  // game = (games::Game*)new games::h2h::Head2Head(gameDisplay);
  // game = (games::Game*)new games::life::LifeGame(gameDisplay);
  // game = (games::Game*)new games::rocket::RocketGame(gameDisplay);
  game = (games::Game*)new games::rainbow::RainbowGame(gameDisplay);
  // game = (games::Game*)new games::marquee::MarqueeGame(gameDisplay);
  // game = (games::Game*)new games::snake::SnakeGame(gameDisplay);
  // game = (games::Game*)new games::shooter::ShooterGame(gameDisplay);
  // game = (games::Game*)new games::falling::FallingGame(gameDisplay);
  // game = (games::Game*)new games::lane_runner::LaneRunnerGame(gameDisplay);
  // game = (games::Game*)new games::life::LifeGameSinglePlayer(gameDisplay);

  // Test Games
  // game = (games::Game*)new test::DirPadTest(gameDisplay);
  // game = (games::Game*)new test::FiveStripTest(gameDisplay);
  // game = (games::Game*)new games::life::GliderWarsGame(gameDisplay);
  // game = (games::Game*)new test::AnimationTest(gameDisplay);

  Serial.println("game created");

  game->setup();
  Serial.println("game setup complete");

  Serial.println("End setup()");

  // TODO what is this? can we remove it?
  // pinMode(9, OUTPUT);

  // TODO should we show LEDs on setup?
  FastLED.show();
}

void loop() {
  // Serial.println("loop() entered");

  game->loop();
  FastLED.show();

  // Serial.println("loops brother");
  frameRate.PrintFrameRate();
}
