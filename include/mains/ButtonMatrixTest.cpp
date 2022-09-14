
#include <Arduino.h>
#include <FastLED.h>

#include <vector>  // for std::vector

#include "controls/button.h"           // for controls::Button
#include "controls/hardware/matrix.h"  // for controls::hardware::Matrix
#include "games/game.h"                // for Game

using namespace kss;

// These are the pins we're using for each controller/button
constexpr size_t cont_pins[]{2, 3, 4, 7};
constexpr size_t butt_pins[]{8, 9, 10, 11, 12, 13};

controls::hardware::Matrix control_context;

struct MatrixController {
  std::vector<controls::Button *> buttons;
};

std::vector<MatrixController> controllers;

void PrintButtonInfo(size_t controller, size_t button, const char *message) {
  Debug("T=" + millis() + " | controller: " + controller +
                 ", button: " + button + " | " + message);
}

void setup() {
  Debug_init();

  // Initialize controls
  Debug("Initialize Controls");
  for (const size_t cont_pin : cont_pins) {
    controllers.emplace_back();
    MatrixController& controller = controllers.back();
    for (const size_t butt_pin : butt_pins) {
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