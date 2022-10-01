#pragma once

#include "display/switchback_standard.h"  // for SwitchbackStandardDisplay
#include "pins/pin_setup.h"               // for Leds

namespace kss {
namespace display {

namespace _instructo_standard {

constexpr size_t kPanelRows{8};
constexpr size_t kPanelColumns{32};

}  // namespace _instructo_standard

class InstructoDisplay
    : public SwitchbackStandardDisplay<_instructo_standard::kPanelRows,
                                       _instructo_standard::kPanelColumns> {
 public:
  InstructoDisplay(const uint8_t pin) : SwitchbackStandardDisplay() {
    RegisterStrip<pins::Leds[12]>();
  }
};

}  // namespace display
}  // namespace kss
