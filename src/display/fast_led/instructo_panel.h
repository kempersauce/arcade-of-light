#pragma once

#include "display/fast_led/switchback.h"  // for SwitchbackDisplay
#include "pins/pin_setup.h"               // for Leds

namespace kss {
namespace display {
namespace fast_led {

namespace _instructo {

constexpr size_t kPanelRows{8};
constexpr size_t kPanelColumns{32};

}  // namespace _instructo

class InstructoDisplay : public SwitchbackDisplay<_instructo::kPanelRows,
                                                  _instructo::kPanelColumns> {
 public:
  InstructoDisplay() : SwitchbackDisplay() {
    RegisterStrip<pins::LedInstructo[0]>();
  }
};

}  // namespace fast_led
}  // namespace display
}  // namespace kss
