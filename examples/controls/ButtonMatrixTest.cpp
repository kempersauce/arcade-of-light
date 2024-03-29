#include <Arduino.h>
#include <FastLED.h>

#include <vector>  // for std::vector

#include "controls/button.h"           // for controls::Button
#include "controls/hardware/matrix.h"  // for controls::hardware::Matrix
#include "pins/pin_setup.h"            // for pins::*
#include "time/now.h"                  // for Now

using namespace kss;

controls::hardware::Matrix control_context;

struct MatrixController {
  std::vector<controls::Button *> buttons;
};

std::vector<MatrixController> controllers;

void PrintButtonInfo(size_t controller, size_t button, const char *message) {
  Debug("T=%d | controller[%d] (pin %d), button[%d] (pin %d) | %s", time::Now(),
        controller, pins::Controllers[controller], button,
        pins::Buttons[button], message);
}

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  // Initialize controls
  Debug("Initialize Controls");
  for (const auto cont_pin : pins::Controllers) {
    controllers.emplace_back();
    MatrixController &controller = controllers.back();
    for (const auto butt_pin : pins::Buttons) {
      controller.buttons.push_back(
          control_context.CreateButton(cont_pin, butt_pin));
    }
    // break;// test single controller[0]
  }
  Debug("Initialization Successful!");

  // Poll for initial button state
  Debug("Poll for initial button state");
  time::SetLoopTime();
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
  time::SetLoopTime();
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