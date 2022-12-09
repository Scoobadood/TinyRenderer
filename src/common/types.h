//
// Created by Dave Durbin on 9/12/2022.
//

#ifndef TINYRENDERER_SRC_COMMON_TYPES_H_
#define TINYRENDERER_SRC_COMMON_TYPES_H_

struct Vec3f {
  float x;
  float y;
  float z;
  Vec3f(float x, float y, float z) : x{x}, y{y}, z{z} {}
};


#endif //TINYRENDERER_SRC_COMMON_TYPES_H_
