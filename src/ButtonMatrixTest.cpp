
#include <Arduino.h>
#include <FastLED.h>
#include "games/game.h"  // for Game
#include "controls/button.h"           // for controls::Button
#include "controls/hardware/matrix.h"  // for controls::hardware::Matrix

#include <memory>  // for std::shared_ptr
#include <vector>  // for std::vector

using namespace kss;

// These are the pins we're using for each controller/button
const int cont_pins[4] = {2, 3, 4, 7};
const int butt_pins[6] = {0, 1, 2, 3, 4, 5};

controls::hardware::Matrix control_context;

struct MatrixController {
  std::vector<std::shared_ptr<controls::Button>> buttons;
};

std::vector<MatrixController> controllers;

void setup() {
  Serial.begin(115200);

  // Initialize controls
  Serial.println("Initialize Controls");
  for (const int cont_pin : cont_pins) {
    MatrixController controller;
    for (const int butt_pin : butt_pins) {
      controller.buttons.emplace_back(
          control_context.CreateButton(cont_pin, butt_pin));
    }
    controllers.emplace_back(controller);
  }

  // Poll for initial button state
  Serial.println("Poll for initial button state");
  control_context.PollAll();

  // Sound off initial button state
  Serial.println("Sound off initial button state");
  for (size_t cont = 0; cont < controllers.size(); cont++) {
    const auto &controller = controllers[cont];
    const auto &buttons = controller.buttons;
    for (size_t butt = 0; butt < buttons.size(); butt++) {
      const auto &button = buttons[butt];
      if (button->IsUp()) {
        Serial.println((String) "controller: " + cont + ", button: " + butt +
                       " | reporting for duty");
      }
    }
  }

  Serial.println("-- setup complete --");
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
        Serial.println((String) "controller: " + cont + ", button: " + butt +
                       " | DEPRESSED!");
      }
      if (button->IsReleasing()) {
        Serial.println((String) "controller: " + cont + ", button: " + butt +
                       " | RELEASED!");
      }
    }
  }
}