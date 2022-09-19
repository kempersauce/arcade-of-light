#include <Arduino.h>
#include <FastLED.h>

#include <vector>  // for std::vector

#include "controls/button.h"           // for controls::Button
#include "controls/hardware/matrix.h"  // for controls::hardware::Matrix
#include "games/game.h"                // for Game
#include "pins/pin_setup.h"            // for pins::*

using namespace kss;

controls::hardware::Matrix control_context;

struct MatrixController {
  std::vector<controls::Button *> buttons;
};

std::vector<MatrixController> controllers;

void PrintButtonInfo(size_t controller, size_t button, const char *message) {
  Debug("T=" + millis() + " | controller[" + controller + "] (pin " +
        pins::Controllers[controller] + "), button[" + button + "] (pin " +
        pins::Buttons[button] + ") | " + message);
}

void setup() {
  Debug_init();
  pins::Init();

  // Initialize controls
  Debug("Initialize Controls");
  for (const auto cont_pin : pins::Controllers) {
    controllers.emplace_back();
    MatrixController &controller = controllers.back();
    for (const auto butt_pin : pins::Buttons) {
      controller.buttons.push_back(
          control_context.CreateButton(cont_pin, butt_pin));
    }
  }
  Debug("Initialization Successful!");

  // Poll for initial button state
  Debug("Poll for initial button state");
  control_context.PollAll();

  // Sound off initial button state
  Debug("Sound off initial button state");
  for (size_t cont = 0; cont < controllers.size(); cont++) {
    const auto &controller = controllers[cont];
    const auto &buttons = controller.buttons;
    for (size_t butt = 0; butt < buttons.size(); butt++) {
      const auto &button = buttons[butt];
      if (button->IsUp()) {
        PrintButtonInfo(cont, butt, "reporting for duty");
      }
    }
  }

  Debug("-- setup complete --");
}

void loop() {
  // Poll all the button states
  control_context.PollAll();

  // Sound off button states
  for (size_t cont = 0; cont < controllers.size(); cont++) {
    const auto &controller = controllers[cont];
    const auto &buttons = controller.buttons;
    for (size_t butt = 0; butt < buttons.size(); butt++) {
      const auto &button = buttons[butt];
      if (button->IsDepressing()) {
        PrintButtonInfo(cont, butt, "v DEPRESSED!");
      }
      if (button->IsReleasing()) {
        PrintButtonInfo(cont, butt, "^ RELEASED!");
      }
    }
  }

  // Emulate ~150 FPS
  delay(7);
}