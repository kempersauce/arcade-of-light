
#include <Arduino.h>
#include <FastLED.h>

#include "controls/dir_pad.h"          // for DirPad
#include "controls/hardware/simple.h"  // for controls::hardware::Simple
#include "display/fast_led/five.h"     // for FiveDisplay
#include "games/game.h"                // for Game
#include "games/life/single_player.h"  // for LifeGameSinglePlayer
#include "pins/pin_setup.h"            // for pins::*
#include "serial/debug.h"              // for Debug
#include "time/now.h"                  // for time::*

using namespace kss;

games::Game* game;
display::Display* gameDisplay;
controls::hardware::Simple control_context;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = (display::Display*)new display::fast_led::FiveDisplay();

  controls::DirPad dirPad{control_context.CreateButton(pins::Buttons[4]),
                          control_context.CreateButton(pins::Buttons[3]),
                          control_context.CreateButton(pins::Buttons[5]),
                          control_context.CreateButton(pins::Buttons[2]),
                          control_context.CreateButton(pins::Buttons[1]),
                          control_context.CreateButton(pins::Buttons[0])};

  game =
      (games::Game*)new games::life::LifeGameSinglePlayer(gameDisplay, dirPad);
  time::SetLoopTime();
  game->setup();
  gameDisplay->Show();
}

void loop() {
  time::SetLoopTime();
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
}