#pragma once

#include "display/switchback_octo.h"  // for SwitchbackOctoDisplay

namespace kss {
namespace display {

namespace _instructo {

constexpr size_t kPanelRows{8};
constexpr size_t kPanelColumns{32};
constexpr size_t kTotalPixelCount{kPanelRows * kPanelColumns};

DMAMEM int kDisplayMemory[kTotalPixelCount * 3 / 4];

}  // namespace _instructo

class InstructoDisplay
    : public SwitchbackOctoDisplay<_instructo::kPanelRows,
                                   _instructo::kPanelColumns> {
 public:
  InstructoDisplay(const uint8_t pin)
      : SwitchbackOctoDisplay(pin, _instructo::kDisplayMemory) {}
};

}  // namespace display
}  // namespace kss
