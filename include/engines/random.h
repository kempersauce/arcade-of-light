#pragma once

#include <FastLED.h>  // for random*

// Anonymous namespace - these are only accessible in this file
namespace {
constexpr uint8_t BIT_MASK = 0x1;
constexpr uint16_t UINT8_MAX_INCL = (uint16_t)UINT8_MAX + 1;
constexpr uint32_t UINT16_MAX_INCL = (uint32_t)UINT16_MAX + 1;
constexpr uint64_t UINT32_MAX_INCL = (uint64_t)UINT32_MAX + 1;

// Include this outside the random namespace so we can reference it later
inline int32_t random32() { return random(); }

}  // namespace

namespace kss {
namespace engines {
namespace random {

//////// 8-bit ints

// 0 to UINT8_MAX
inline uint8_t Int8() { return random8(); }

// 0 to max (exclusive)
inline uint8_t Int8(uint8_t max) { return Int8() * max / UINT8_MAX; }

// min to max (exclusive)
inline int8_t Int8(int8_t min, int8_t max) { return Int8(max - min) + min; }

// 0 to max (inclusive)
inline uint8_t Int8_incl(uint8_t max) {
  return Int8() * (max + 1) / UINT8_MAX_INCL;
}

// min to max (inclusive)
inline int8_t Int8_incl(int8_t min, int8_t max) {
  return Int8_incl(max - min) + min;
}

//////// 16-bit ints

// 0 to UINT16_MAX
inline uint16_t Int16() { return random16(); }

// 0 to max (exclusive)
inline uint16_t Int16(uint16_t max) { return Int16() * max / UINT16_MAX; }

// min to max (exclusive)
inline int16_t Int16(int16_t min, int16_t max) {
  return Int16(max - min) + min;
}

// 0 to max (inclusive)
inline uint16_t Int16_incl(uint16_t max) {
  return Int16() * (max + 1) / UINT16_MAX_INCL;
}

// min to max (inclusive)
inline int16_t Int16_incl(int16_t min, int16_t max) {
  return Int16_incl(max - min) + min;
}

//////// 32-bit ints

// 0 to UINT32_MAX (inclusive)
inline uint32_t Int32() { return random32(); }

/****
 * DANGER: These don't work, we hit overflow and always end up with the lower bound
 ****/

// // 0 to max (exclusive)
// inline uint32_t Int32(uint32_t max) {
//   return Int32() * (max + 1) / UINT32_MAX_INCL;
// }

// // min to max (exclusive)
// inline int32_t Int32(int32_t min, int32_t max) {
//   return Int32(max - min) + min;
// }

// // 0 to max (inclusive)
// inline uint32_t Int32_incl(uint32_t max) {
//   return Int32() * (max + 1) / UINT32_MAX_INCL;
// }

// // min to max (inclusive)
// inline int32_t Int32_incl(int32_t min, int32_t max) {
//   return Int32_incl(max - min) + min;
// }

//////// Floating point types

// 0.0 to 1.0 (exclusive)
inline float Float() { return (float)random16() / UINT16_MAX; }

// 0.0 to max (exclusive)
inline float Float(float max) { return (float)random16() * max / UINT16_MAX; }

// min to max (exclusive)
inline float Float(float min, float max) { return Float(max - min) + min; }

//////// Booleans

// true to false
inline bool Bool() { return random16() & BIT_MASK == 0; }

// true to false (chance% of being true)
inline bool Bool(float chance) { return Float() < chance; }

}  // namespace random
}  // namespace engines
}  // namespace kss
