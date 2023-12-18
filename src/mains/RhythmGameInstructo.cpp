#include <vector>  // for std::vector

#include "animation/wave_out.h"                // for WaveOut
#include "display/fast_led/instructo_panel.h"  // for InstructoStandaloneDisplay
#include "engines/framerate.h"                 // for FrameRate
#include "games/rhythm/constants.h"            // for kPlayerHues
#include "pins/pin_setup.h"                    // for pins::Init
#include "serial/debug.h"                      // for serial debugging
#include "test/animation.h"                    // for AnimationTest
#include "time/now.h"                          // for time::*

using namespace kss;

constexpr bool USE_OFF_HUES{false};
constexpr uint8_t PLAYER_NO{0};

engines::FrameRate frameRate;

display::fast_led::InstructoDisplay* gameDisplay;
test::AnimationTest* game;
std::vector<animation::Animation*> animes;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  Debug("Begin setup()");

  // Choose your Display type
  gameDisplay = new display::fast_led::InstructoDisplay();

  Debug("gameDisplay created");

  const uint8_t hue = USE_OFF_HUES ? games::rhythm::kPlayerOffhues[PLAYER_NO]
                             : games::rhythm::kPlayerHues[PLAYER_NO];

  animes.push_back(new animation::WaveOut1(hue, 255, gameDisplay->size));

  Debug("Animations created");

  game = new test::AnimationTest(gameDisplay, animes);

  Debug("game created");

  time::SetLoopTime();
  game->setup();

  Debug("End setup()");
}

void loop() {
  time::SetLoopTime();
  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
}
