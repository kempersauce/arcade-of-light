#pragma once

#include "math/random.h"  // for random::*

namespace kss {
namespace math {

template <typename T>
class Vector2D {
 public:
  T x;
  T y;

  Vector2D() : x{0}, y{0} {}
  Vector2D(T x, T y) : x{x}, y{y} {}

  // Copy constructor and assignment operator
  Vector2D(const Vector2D& other) : x{other.x}, y{other.y} {}
  template <typename U>
  Vector2D(const Vector2D<U>& other) : x{other.x}, y{other.y} {}

  Vector2D& operator=(const Vector2D& other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  template <typename U>
  Vector2D& operator=(const Vector2D<U>& other) {
    x = other.x;
    y = other.y;
    return *this;
  }

  // Move constructor and operator
  Vector2D(Vector2D&& other) : x{std::move(other.x)}, y{std::move(other.y)} {}
  template <typename U>
  Vector2D(Vector2D<U>&& other)
      : x{std::move(other.x)}, y{std::move(other.y)} {}

  Vector2D& operator=(Vector2D&& other) {
    x = std::move(other.x);
    y = std::move(other.y);
    return *this;
  }
  template <typename U>
  Vector2D& operator=(Vector2D<U>&& other) {
    x = std::move(other.x);
    y = std::move(other.y);
    return *this;
  }

  template <typename U>
  Vector2D<U> GetAs() {
    return *this;
  }

  T GetMagnitude() { return x * x + y * y; }

  String ToString() { return (String) "(" + x + "x" + y + ")"; }

  // Not sure how well this would work for non-floats, meh whatever
  static Vector2D RandomVector(T max_magnitude) {
    const T neg_magnitude = max_magnitude * -1;
    const T hypotenuese = max_magnitude * max_magnitude;
    Vector2D<float> float_vec;
    do {
      float_vec.x = random::Float(neg_magnitude, max_magnitude);
      float_vec.y = random::Float(neg_magnitude, max_magnitude);
    } while (float_vec.GetMagnitude() >
             hypotenuese);  // Repeat until we're within the unit circle

    return float_vec.GetAs<T>();
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

template <typename T>
Vector2D<T> operator+(const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
  return Vector2D<T>{lhs.x + rhs.x, lhs.y + rhs.y};
}

template <typename T>
Vector2D<T> operator-(const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
  return Vector2D<T>{lhs.x - rhs.x, lhs.y - rhs.y};
}

template <typename T>
Vector2D<T> operator*(const Vector2D<T>& vect_a, const Vector2D<T>& vect_b) {
  return Vector2D<T>{vect_a.x * vect_b.x, vect_a.y * vect_b.y};
}

template <typename T, typename Scalar>
Vector2D<T> operator*(const Scalar& scalar, const Vector2D<T>& vect) {
  return Vector2D<T>{scalar * vect.x, scalar * vect.y};
}

template <typename T, typename Scalar>
Vector2D<T> operator*(const Vector2D<T>& vect, const Scalar& scalar) {
  return scalar * vect;
}

template <typename T, typename Scalar>
Vector2D<T> operator/(const Vector2D<T>& vect, const Scalar& scalar) {
  return Vector2D<T>{vect.x / scalar, vect.y / scalar};
}

using Dimension = Vector2D<size_t>;

}  // namespace math
}  // namespace kss
