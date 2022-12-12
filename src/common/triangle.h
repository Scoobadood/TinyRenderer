//
// Created by Dave Durbin on 12/12/2022.
//

#ifndef TINYRENDERER_SRC_COMMON_TRIANGLE_H_
#define TINYRENDERER_SRC_COMMON_TRIANGLE_H_

#include "types.h"
#include "tgaimage.h"

/**
 * Fill a triangle spercified by three points using the line sweep mechanism.
 * @param t0, t1, t2 The vertices of the triangle.
 * @param image The image to which to render the triangle.
 * @param colour The colour to fill the triangle with.
 */
void fill_triangle(Vec2i t0, Vec2i t1, Vec2i t2,
                   TGAImage &image,
                   const TGAColour &colour
);

#endif //TINYRENDERER_SRC_COMMON_TRIANGLE_H_
