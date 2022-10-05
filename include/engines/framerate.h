#pragma once

#include "serial/debug.h"  // for Debug
#include "time/now.h"      // for Now

namespace kss {
namespace engines {

class FrameRate {
  uint32_t last_frame_millis_{time::Now()};

 public:
  void PrintFrameRate() {
    const uint32_t now = time::Now();
    const uint32_t timeDiff = time::LoopElapsedMillis();
    const uint32_t fps = 1000 / timeDiff;
    Debug("T=" + now + ", " + fps + "fps (" + timeDiff + "ms/frame)");
  }
};

}  // namespace engines
}  // namespace kss
