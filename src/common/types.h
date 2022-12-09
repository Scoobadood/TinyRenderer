//
// Created by Dave Durbin on 9/12/2022.
//

#ifndef TINYRENDERER_SRC_COMMON_TYPES_H_
#define TINYRENDERER_SRC_COMMON_TYPES_H_

#include <vector>

struct Vec3f {
  float x;
  float y;
  float z;
  Vec3f(float x, float y, float z) : x{x}, y{y}, z{z} {}
};


struct Vec2i {
  int16_t x{};
  int16_t y{};
  Vec2i(int16_t x, int16_t y) : x{x}, y{y} {}
};

#endif //TINYRENDERER_SRC_COMMON_TYPES_H_
