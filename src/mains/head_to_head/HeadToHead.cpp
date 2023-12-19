#include <Arduino.h>
#include <FastLED.h>

#include "controls/h2h.h"                // for H2HController
#include "controls/hardware/matrix.h"    // for Matrix
#include "display/h2h.h"                 // for H2HDisplay
#include "engines/framerate.h"           // for Framerate
#include "games/head2head/game_strip.h"  // for H2HGameStrip
#include "games/head2head/head2head.h"   // for Head2Head
#include "pins/pin_setup.h"              // for pins::Init
#include "serial/debug.h"                // for Debug
#include "time/now.h"                    // for time::*

using namespace kss;

games::h2h::Head2Head* game;
display::H2HDisplay* gameDisplay;
controls::hardware::Matrix control_context;
engines::FrameRate framerate;

// Alt colors
const CRGB alt_arc_color = CRGB::Cyan;  // Cyan
const uint8_t alt_team_a_hue = 120;     // Green
const uint8_t alt_team_b_hue = 245;     // Watermelon

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  // last dip switches colors
  if (pins::ReadDip(3)) {
    games::h2h::arc_color = alt_arc_color;
    games::h2h::zoneAHue = alt_team_a_hue;
    games::h2h::zoneBHue = alt_team_b_hue;
  }

  // Boss Mode
  if (pins::ReadDip(2)) {
	games::h2h::hitVelocityMultiplierBase = 20;
	games::h2h::hitVelocityMultiplierHeinz = 20;
  }

  gameDisplay = new display::H2HDisplay();

  controls::H2HController teamA{
      controls::H2HController::TeamA(control_context)};
  controls::H2HController teamB{
      controls::H2HController::TeamB(control_context)};

  game = new games::h2h::Head2Head(&gameDisplay->main_display,
                                   &gameDisplay->instructo_a,
                                   &gameDisplay->instructo_b, teamA, teamB);
  time::SetLoopTime();
  game->setup();
  Debug("Setup Complete");
}

void loop() {
  time::SetLoopTime();
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
  framerate.PrintFrameRate();
}