#pragma once

#include "display/switchback_octo.h"  // for SwitchbackOctoDisplay

namespace kss {
namespace display {

namespace _instructo_panel {

constexpr size_t kPanelRows{8};
constexpr size_t kPanelColumns{32};
constexpr size_t kTotalPixelCount{kPanelRows * kPanelColumns};

DMAMEM int displayMemory[kTotalPixelCount * 3 / 4];

}  // namespace _instructo_panel
using namespace _instructo_panel;

class InstructoDisplay
    : public SwitchbackOctoDisplay<kPanelRows, kPanelColumns> {
 public:
  InstructoDisplay(const uint8_t pin)
      : SwitchbackOctoDisplay(pin, displayMemory) {}
};

}  // namespace display
}  // namespace kss
