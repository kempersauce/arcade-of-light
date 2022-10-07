#pragma once

#include "display/constants.h"          // for k*
#include "display/octo/octo_display.h"  // for OctoDisplay
#include "display/sub_display.h"        // for SubDisplay
#include "pins/pin_setup.h"             // for pins::*

namespace kss {
namespace display {

namespace _instructo_standalone {

constexpr size_t kNumStrips = 1;  // 1 instructo
constexpr size_t kLengthStrips = kInstructoStripLength;

constexpr uint8_t kPinList[kNumStrips]{
    // clang-format off

    // Cable 1
    pins::LedInstructo[0]

    // clang-format on
};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];

}  // namespace _instructo_standalone

class InstructoStandaloneDisplay
    : public octo::OctoDisplay<_instructo_standalone::kNumStrips,
                               _instructo_standalone::kLengthStrips> {
 public:
  InstructoStandaloneDisplay()
      : OctoDisplay(_instructo_standalone::kPinList,
                    _instructo_standalone::kDisplayMemory,
                    _instructo_standalone::kLengthStrips) {}
};

}  // namespace display
}  // namespace kss
