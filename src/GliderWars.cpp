
#include <Arduino.h>
#include <FastLED.h>
#include "display/display.h"  // for kss::display::Display
#include "display/h2h.h"  // for H2HDisplay
#include "games/game.h"  // for Game
#include "games/life/glider_wars.h"  // for GliderWars
#include "controls/hardware/simple.h"
#include "controls/h2h_controller.h"  // for H2HController

Game* game;
kss::display::Display* gameDisplay;
kss::controls::hardware::Simple controls;

void setup()
{
    gameDisplay = (kss::display::Display*)new kss::display::H2HDisplay();

    kss::controls::H2HController teamA;
    teamA.buttons[0] = controls.CreateButton(H2H_BUTTON_PIN_7);
    teamA.buttons[7] = controls.CreateButton(H2H_BUTTON_PIN_0);

    kss::controls::H2HController teamB;
    teamB.buttons[0] = controls.CreateButton(H2H_BUTTON_PIN_8);
    teamB.buttons[7] = controls.CreateButton(H2H_BUTTON_PIN_15);

    game = (Game*)new GliderWarsGame(gameDisplay, teamA.buttons[0], teamB.buttons[0], teamA.buttons[7], teamB.buttons[7]);
    game->setup();
    FastLED.show();
}

void loop()
{
    controls.PollAll();
    game->loop();
    FastLED.show();
}