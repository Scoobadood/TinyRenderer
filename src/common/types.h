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
  inline T dot(const Vec3<T> &other) const {
    return x * other.x + y * other.y + z * other.z;
  }
  inline Vec3<T> normalized() const {
    auto l = sqrt(x * x + y * y + z * z);
    return {x / l, y / l, z/l};
  }
};

using Vec3f = Vec3<float>;
using Vec3i = Vec3<int32_t>;

struct Vec2i {
  int32_t x;
  int32_t y;
  Vec2i(int32_t x, int32_t y) : x{x}, y{y} {}
  Vec2i operator-(const Vec2i &other) const {
    return Vec2i{x - other.x, y - other.y};
  }
  Vec2i operator+(const Vec2i &other) const {
    return Vec2i{x + other.x, y + other.y};
  }
  Vec2i operator*(float f) const {
    return Vec2i{(int32_t) roundf(x * f), (int32_t) roundf(y * f)};
  }
};

#endif //TINYRENDERER_SRC_COMMON_TYPES_H_
