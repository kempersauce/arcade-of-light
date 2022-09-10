#pragma once

#include "math/shape.h"    // for Shape
#include "serial/debug.h"  // for debug::*

namespace kss {
namespace math {
namespace shapes {

// // ARROW SHAPE
// //  0 1 2 3 4
// // | | |#|#|#| 4
// // | |#|#|#| | 3
// // |#|#|#| | | 2
// // | |#|#|#| | 1
// // | | |#|#|#| 0
Shape ArrowLeftFull() {
  Debug_here();
  return {{
      // clang-format off
	  {2, 4}, {3, 4}, {4, 4}, // 4
	  {1, 3}, {2, 3}, {3, 3}, // 3
	  {0, 2}, {1, 2}, {2, 2}, // 2
	  {1, 1}, {2, 1}, {3, 1}, // 1
	  {2, 0}, {3, 0}, {4, 0}  // 0
      // clang-format on
  }};
}

Shape ArrowRightFull() {
  Debug_here();
  return ArrowLeftFull().FlipX();
}
Shape ArrowUpFull() {
  Debug_here();
  return ArrowLeftFull().RotateClock();
}
Shape ArrowDownFull() {
  Debug_here();
  return ArrowLeftFull().RotateCounterClock();
}

// ARROW SHAPE
//  0 1 2 3 4
// | | |#|#|#| 4
// | |#| |#| | 3
// |#| |#| | | 2
// | |#| |#| | 1
// | | |#|#|#| 0
Shape ArrowLeftEmpty() {
  Debug_here();
  return {{
      // clang-format off
	  {2, 4}, {3, 4}, {4, 4}, // 4
	  {1, 3}, {3, 3},         // 3
	  {0, 2}, {2, 2},         // 2
	  {1, 1}, {3, 1},         // 1
	  {2, 0}, {3, 0}, {4, 0}  // 0
      // clang-format on
  }};
}

Shape ArrowRightEmpty() {
  Debug_here();
  return ArrowLeftEmpty().FlipX();
}
Shape ArrowUpEmpty() {
  Debug_here();
  return ArrowLeftEmpty().RotateClock();
}
Shape ArrowDownEmpty() {
  Debug_here();
  return ArrowLeftEmpty().RotateCounterClock();
}

}  // namespace shapes
}  // namespace math
}  // namespace kss
