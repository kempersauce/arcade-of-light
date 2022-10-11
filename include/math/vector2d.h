#pragma once

#include "math/random.h"  // for random::*

namespace kss {
namespace math {

template <typename T>
class Vector2D {
 public:
  union {
    T x;
    T width;
  };

  union {
    T y;
    T height;
  };

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
  Vector2D<U> GetAs() const {
    return *this;
  }

  inline T GetHypotenuseSquared() const { return x * x + y * y; }
  inline T GetMagnitude() const { return sqrt(GetHypotenuseSquared()); }

  String ToString() const { return (String) "(" + x + "x" + y + ")"; }

  Vector2D GetAbs() const { return {abs(x), abs(y)}; }

  // Not sure how well this would work for non-floats, meh whatever
  static Vector2D RandomVector(const T max_magnitude) {
    const T neg_magnitude = max_magnitude * -1;
    const T hypotenuese_squared = max_magnitude * max_magnitude;
    Vector2D<float> float_vec;
    do {
      float_vec.x = random::Float(neg_magnitude, max_magnitude);
      float_vec.y = random::Float(neg_magnitude, max_magnitude);
    } while (float_vec.GetHypotenuseSquared() >
             hypotenuese_squared);  // Repeat until we're within the unit circle

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

// + Operators
template <typename T>
Vector2D<T> operator+(const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
  return Vector2D<T>{lhs.x + rhs.x, lhs.y + rhs.y};
}

template <typename T, typename Scalar>
Vector2D<T> operator+(const Vector2D<T>& vect, const Scalar& scalar) {
  return Vector2D<T>{vect.x + scalar, vect.y + scalar};
}

template <typename T, typename Scalar>
Vector2D<T> operator+(const Scalar& scalar, const Vector2D<T>& vect) {
  return vect + scalar;
}

// - Operators
template <typename T>
Vector2D<T> operator-(const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
  return Vector2D<T>{lhs.x - rhs.x, lhs.y - rhs.y};
}

template <typename T, typename Scalar>
Vector2D<T> operator-(const Vector2D<T>& vect, const Scalar& scalar) {
  return Vector2D<T>{vect.x - scalar, vect.y - scalar};
}

template <typename T, typename Scalar>
Vector2D<T> operator-(const Scalar& scalar, const Vector2D<T>& vect) {
  return Vector2D<T>{scalar - vect.x, scalar - vect.y};
}

// * Operators
template <typename T>
Vector2D<T> operator*(const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
  return Vector2D<T>{lhs.x * rhs.x, lhs.y * rhs.y};
}

template <typename T, typename Scalar>
Vector2D<T> operator*(const Scalar& scalar, const Vector2D<T>& vect) {
  return Vector2D<T>{scalar * vect.x, scalar * vect.y};
}

template <typename T, typename Scalar>
Vector2D<T> operator*(const Vector2D<T>& vect, const Scalar& scalar) {
  return scalar * vect;
}

// / Operators
template <typename T>
Vector2D<T> operator/(const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
  return Vector2D<T>{lhs.x / rhs.x, lhs.y / rhs.y};
}

template <typename T, typename Scalar>
Vector2D<T> operator/(const Vector2D<T>& vect, const Scalar& scalar) {
  return Vector2D<T>{vect.x / scalar, vect.y / scalar};
}

template <typename T, typename Scalar>
Vector2D<T> operator/(const Scalar& scalar, const Vector2D<T>& vect) {
  return Vector2D<T>{scalar / vect.x, scalar / vect.y};
}

using Dimension = Vector2D<size_t>;

}  // namespace math
}  // namespace kss
