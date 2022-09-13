#pragma once

#include <vector>  // for vector

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "engines/noise.h"        // for NoiseGenerator
#include "math/random.h"          // for random*
#include "math/vector2d.h"        // for Dimension
#include "serial/debug.h"         // for Debug

namespace kss {
namespace animation {

namespace _splotch {

const math::Dimension kSplotchPartMaxSize{4, 7};
constexpr uint8_t kSplotchMaxHueDrift{15};
constexpr uint8_t kSplotchPartMinCount{10};
constexpr uint8_t kSplotchPartMaxCount{15};

}  // namespace _splotch
using namespace _splotch;

class Splotch : public Animation {
  engines::NoiseGenerator noise_generator;
  math::Dimension location;

  struct SplotchPart {
    math::Dimension offset;
    math::Dimension size;
    uint8_t hue;

    SplotchPart(math::Dimension offset, math::Dimension size, uint8_t hue)
        : offset{offset}, size{size}, hue{hue} {}
  };

  std::vector<SplotchPart> parts;

 public:
  Splotch(math::Dimension size, math::Dimension location, const uint8_t hue)
      : Animation(), noise_generator{size, 5}, location{location} {
    const uint8_t splotch_count{
        math::random::Int8_incl(kSplotchPartMinCount, kSplotchPartMaxCount)};
    while (parts.size() < splotch_count) {
      math::Dimension part_offset = math::Dimension{
          math::random::Int8_incl(size.x), math::random::Int8_incl(size.y)};
      math::Dimension part_size{
          math::random::Int8_incl(1, kSplotchPartMaxSize.x),
          math::random::Int8_incl(1, kSplotchPartMaxSize.y)};
      uint8_t part_hue =
          256 + hue +
          math::random::Int8_incl(-kSplotchMaxHueDrift, kSplotchMaxHueDrift) %
              256;
      parts.emplace_back(part_offset, part_size, part_hue);
    }
  }

  void Move() override { noise_generator.fillnoise8(); }

  void draw(display::Display* display) {
    for (const auto& part : parts) {
      for (size_t x = 0; x < part.size.x; ++x) {
        for (size_t y = 0; y < part.size.y; y++) {
          const auto value = noise_generator.data[part.offset.x][part.offset.y];
          const int pix_x = location.x + part.offset.x + x;
          const int pix_y = location.y + part.offset.y + y;
          if (display->IsInBounds(pix_x, pix_y)) {
            display->Pixel(pix_x, pix_y) = CHSV(part.hue, 200, value);
          }
        }
      }
    }
  }
};

}  // namespace animation
}  // namespace kss