#pragma once

#include "math/vector2d.h"  // for Vector2D

namespace kss {
namespace display {

const math::Vector2D<float> GRID_SCALE_1_1{1, 1};
const math::Vector2D<float> GRID_SCALE_WIDE{2.125, 0.65};

constexpr size_t kTableStripLength{215};
constexpr size_t kTableStripCount{8};

constexpr size_t kTowerStripLength{294};
constexpr size_t kTowerStripCount{5};

constexpr size_t kInstructoRowCount{8};
constexpr size_t kInstructoColumnCount{32};
constexpr size_t kInstructoStripLength{kInstructoRowCount *
                                       kInstructoColumnCount};

}  // namespace display
}  // namespace kss
