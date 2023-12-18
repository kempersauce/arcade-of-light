#pragma once

#include "display/octo/switchback.h"  // for SwitchbackDisplay

namespace kss {
namespace display {
namespace octo {

namespace _instructo {

constexpr size_t kPanelRows{8};
constexpr size_t kPanelColumns{32};
constexpr size_t kTotalPixelCount{kPanelRows * kPanelColumns};

DMAMEM int kDisplayMemory[kTotalPixelCount * 3 / 4];

}  // namespace _instructo

class InstructoDisplay : public SwitchbackDisplay<_instructo::kPanelRows,
                                                  _instructo::kPanelColumns> {
 public:
  InstructoDisplay(const uint8_t pin)
      : SwitchbackDisplay(pin, _instructo::kDisplayMemory) {}
};

}  // namespace octo
}  // namespace display
}  // namespace kss
