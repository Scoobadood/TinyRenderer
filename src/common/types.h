//
// Created by Dave Durbin on 9/12/2022.
//

#ifndef TINYRENDERER_SRC_COMMON_TYPES_H_
#define TINYRENDERER_SRC_COMMON_TYPES_H_

#include <vector>
#include <cmath>

template<typename T>
struct Vec3 {
  T x;
  T y;
  T z;
  Vec3(T x, T y, T z) : x{x}, y{y}, z{z} {}
  inline Vec3<T> cross(const Vec3<T> &other) const {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
  }
  inline Vec3<T> operator-(const Vec3<T> &other) const {
    return Vec3<T>{x - other.x, y - other.y, z - other.z};
  }
  inline Vec3<T> operator+(const Vec3<T> &other) const {
    return Vec3<T>{x + other.x, y + other.y, z + other.z};
  }
  inline Vec3<T> operator/(T f) const {
    return Vec3<T>{x / f, y / f, z / f};
  }
  inline T dot(const Vec3<T> &other) const {
    return x * other.x + y * other.y + z * other.z;
  }
  inline Vec3<T> normalized() const {
    auto l = sqrt(x * x + y * y + z * z);
    return {x / l, y / l, z / l};
  }
};

using Vec3f = Vec3<float>;
using Vec3i = Vec3<int32_t>;

template<typename T>
struct Vec2 {
  T x;
  T y;
  Vec2<T>(T x, T y) : x{x}, y{y} {}
  Vec2<T> operator-(
      const Vec2<T> &other
  ) const {
    return Vec2<T>{x - other.x, y - other.y};
  }
  Vec2<T> operator+(const Vec2<T> &other) const {
    return Vec2<T>{x + other.x, y + other.y};
  }
  Vec2<T> operator*(float f) const {
    return Vec2<T>{(T) roundf(x * f), (T) roundf(y * f)};
  }
  Vec2<T> operator/(float f) const {
    return Vec2<T>{(T) roundf(x / f), (T) roundf(y / f)};
  }
};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int32_t>;

#endif //TINYRENDERER_SRC_COMMON_TYPES_H_
