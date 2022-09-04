#pragma once

#include "math/random.h"  // for random::*

namespace kss {
namespace math {

class Vector2D {
 public:
  float x;
  float y;

  Vector2D() : x{0}, y{0} {}
  Vector2D(float x, float y) : x{x}, y{y} {}

  static Vector2D RandomVector(float max_magnitude) {
    const float neg_magnitude = max_magnitude * -1;
    const float hypotenuese = max_magnitude * max_magnitude;
    float x, y;
    do {
      x = random::Float(neg_magnitude, max_magnitude);
      y = random::Float(neg_magnitude, max_magnitude);
    } while (x * x + y * y >
             hypotenuese);  // Repeat until we're within the unit circle

    return Vector2D{x, y};
  }

  Vector2D& operator+=(const Vector2D& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  Vector2D& operator-=(const Vector2D& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  template <typename Scalar>
  Vector2D& operator*=(const Scalar& scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  template <typename Scalar>
  Vector2D& operator/=(const Scalar& scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }
};

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs) {
  return Vector2D{lhs.x + rhs.x, lhs.y + rhs.y};
}

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) {
  return Vector2D{lhs.x - rhs.x, lhs.y - rhs.y};
}

Vector2D operator*(const Vector2D& vect_a, const Vector2D& vect_b) {
  return Vector2D{vect_a.x * vect_b.x, vect_a.y * vect_b.y};
}

template <typename Scalar>
Vector2D operator*(const Scalar& scalar, const Vector2D& vect) {
  return Vector2D{scalar * vect.x, scalar * vect.y};
}

template <typename Scalar>
Vector2D operator*(const Vector2D& vect, const Scalar& scalar) {
  return scalar * vect;
}

template <typename Scalar>
Vector2D operator/(const Vector2D& vect, const Scalar& scalar) {
  return Vector2D{vect.x / scalar, vect.y / scalar};
}

}  // namespace math
}  // namespace kss
