#pragma once

#include <vector>

#include "math/random.h"    // for random::*
#include "math/vector2d.h"  // for Dimension
#include "serial/debug.h"   // for Debug

/**
 * @brief BE CAREFUL USING THIS IT DOESNT WORT QUITE RIGHT YET & LIKES TO CRASH
 *
 */

namespace kss {
namespace math {

Dimension GetShapeSize(const std::vector<Dimension>& points) {
  Dimension max;
  for (const auto& point : points) {
    if (max.x > point.x) {
      max.x = point.x;
    }
    if (max.y > point.y) {
      max.y = point.y;
    }
  }
  return max;
}

class Shape {
 public:
  Dimension bounds;
  std::vector<Dimension> points;

  Shape(std::vector<Dimension> points)
      : bounds{GetShapeSize(points)}, points{points} {}

  Shape(std::vector<Dimension> points, Dimension bounds)
      : bounds{bounds}, points{points} {}

  Shape FlipX() const {
    Debug_here();
    std::vector<Dimension> flipped{points.size()};
    for (const auto& point : points) {
      flipped.emplace_back(bounds.x - point.x, point.y);
    }
    return {flipped, bounds};
  }

  Shape FlipY() const {
    Debug_here();
    std::vector<Dimension> flipped{points.size()};
    for (const auto& point : points) {
      flipped.emplace_back(point.x, bounds.y - point.y);
    }
    return {flipped, bounds};
  }

  Shape FlipXY() const {
    Debug_here();
    std::vector<Dimension> flipped{points.size()};
    for (const auto& point : points) {
      flipped.emplace_back(bounds.x - point.x, bounds.y - point.y);
    }
    return {flipped, bounds};
  }

  Shape RotateClock() const {
    Debug_here();
    std::vector<Dimension> flipped{points.size()};
    for (const auto& point : points) {
      flipped.emplace_back(point.y, bounds.x - point.x);
    }
    return {flipped, {bounds.y, bounds.x}};
  }

  Shape RotateCounterClock() const {
    Debug_here();
    std::vector<Dimension> flipped{points.size()};
    for (const auto& point : points) {
      flipped.emplace_back(point.y - bounds.y, point.x);
    }
    return {flipped, {bounds.y, bounds.x}};
  }

  Shape Rotate180() const {
    Debug_here();
    std::vector<Dimension> flipped{points.size()};
    for (const auto& point : points) {
      flipped.emplace_back(point.y, point.x);
    }
    return {flipped, bounds};
  }
};

}  // namespace math
}  // namespace kss
