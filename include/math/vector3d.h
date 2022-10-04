#pragma once

#include "math/random.h"  // for random::*

namespace kss {
namespace math {

template <typename T>
class Vector3D {
 public:
  union {
    T x;
    T width;
  };

  union {
    T y;
    T height;
  };

  union {
    T z;
    T depth;
  };

  Vector3D() : x{0}, y{0}, z{0} {}
  Vector3D(T x, T y, T z) : x{x}, y{y}, z{z} {}

  // Copy constructor and assignment operator
  Vector3D(const Vector3D& other) : x{other.x}, y{other.y}, z{other.z} {}
  template <typename U>
  Vector3D(const Vector3D<U>& other) : x{other.x}, y{other.y}, z{other.z} {}

  Vector3D& operator=(const Vector3D& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }
  template <typename U>
  Vector3D& operator=(const Vector3D<U>& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  // Move constructor and operator
  Vector3D(Vector3D&& other) : x{std::move(other.x)}, y{std::move(other.y)}, z{std::move(other.z)} {}
  template <typename U>
  Vector3D(Vector3D<U>&& other)
      : x{std::move(other.x)}, y{std::move(other.y)}, z{std::move(other.z)} {}

  Vector3D& operator=(Vector3D&& other) {
    x = std::move(other.x);
    y = std::move(other.y);
    z = std::move(other.z);
    return *this;
  }
  template <typename U>
  Vector3D& operator=(Vector3D<U>&& other) {
    x = std::move(other.x);
    y = std::move(other.y);
    z = std::move(other.z);
    return *this;
  }

  template <typename U>
  Vector3D<U> GetAs() const {
    return *this;
  }

  inline T GetHypotenuseSquared() const { return x * x + y * y + z * z; }
  inline T GetMagnitude() const { return sqrt(GetHypotenuseSquared()); }

  String ToString() const { return (String) "(" + x + "x" + y + "x" + z +")"; }

  // Not sure how well this would work for non-floats, meh whatever
  static Vector3D RandomVector(T max_magnitude) {
    const T neg_magnitude = max_magnitude * -1;
    const T hypotenuese_squared = max_magnitude * max_magnitude;
    Vector3D<float> float_vec;
    do {
      float_vec.x = random::Float(neg_magnitude, max_magnitude);
      float_vec.y = random::Float(neg_magnitude, max_magnitude);
      float_vec.z = random::Float(neg_magnitude, max_magnitude);
    } while (float_vec.GetHypotenuseSquared() >
             hypotenuese_squared);  // Repeat until we're within the unit circle

    return float_vec.GetAs<T>();
  }

  Vector3D& operator+=(const Vector3D& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  Vector3D& operator-=(const Vector3D& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  template <typename Scalar>
  Vector3D& operator*=(const Scalar& scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  template <typename Scalar>
  Vector3D& operator/=(const Scalar& scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }
};

// + Operators
template <typename T>
Vector3D<T> operator+(const Vector3D<T>& lhs, const Vector3D<T>& rhs) {
  return Vector3D<T>{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template <typename T, typename Scalar>
Vector3D<T> operator+(const Vector3D<T>& vect, const Scalar& scalar) {
  return Vector3D<T>{vect.x + scalar, vect.y + scalar, vect.z + scalar};
}

template <typename T, typename Scalar>
Vector3D<T> operator+(const Scalar& scalar, const Vector3D<T>& vect) {
  return vect + scalar;
}

// - Operators
template <typename T>
Vector3D<T> operator-(const Vector3D<T>& lhs, const Vector3D<T>& rhs) {
  return Vector3D<T>{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template <typename T, typename Scalar>
Vector3D<T> operator-(const Vector3D<T>& vect, const Scalar& scalar) {
  return Vector3D<T>{vect.x - scalar, vect.y - scalar, vect.z - scalar};
}

template <typename T, typename Scalar>
Vector3D<T> operator-(const Scalar& scalar, const Vector3D<T>& vect) {
  return Vector3D<T>{scalar - vect.x, scalar - vect.y, scalar - vect.z};
}

// * Operators
template <typename T>
Vector3D<T> operator*(const Vector3D<T>& lhs, const Vector3D<T>& rhs) {
  return Vector3D<T>{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

template <typename T, typename Scalar>
Vector3D<T> operator*(const Scalar& scalar, const Vector3D<T>& vect) {
  return Vector3D<T>{scalar * vect.x, scalar * vect.y, scalar * vect.z};
}

template <typename T, typename Scalar>
Vector3D<T> operator*(const Vector3D<T>& vect, const Scalar& scalar) {
  return scalar * vect;
}

// / Operators
template <typename T>
Vector3D<T> operator/(const Vector3D<T>& lhs, const Vector3D<T>& rhs) {
  return Vector3D<T>{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

template <typename T, typename Scalar>
Vector3D<T> operator/(const Vector3D<T>& vect, const Scalar& scalar) {
  return Vector3D<T>{vect.x / scalar, vect.y / scalar, vect.z / scalar};
}

template <typename T, typename Scalar>
Vector3D<T> operator/(const Scalar& scalar, const Vector3D<T>& vect) {
  return Vector3D<T>{scalar / vect.x, scalar / vect.y, scalar / vect.z};
}

}  // namespace math
}  // namespace kss
