#ifndef TINYRENDERER_SRC_COMMON_TRIANGLE_P_H_
#define TINYRENDERER_SRC_COMMON_TRIANGLE_P_H_

#include "types.h"
#include "tgaimage.h"

/**
 * Fill a triangle using a parallel approach by determining for each point in the
 * bounding box of the triangle, whether or not it lies in the bounds of the triangle.
 * This is how a GPU based implementation may work.
 *
 * @param t0, t1, t2 Vertices of the triangle.
 * @image image The image to which to render the filled triangle
 * @param colour The colour to fill with.
 */
void fill_triangle_bb(Vec2i t0, Vec2i t1, Vec2i t2,
                      TGAImage &image,
                      const TGAColour &colour,
                      int num_threads = -1
);

void fill_triangle_bb(Vec3f t0, Vec3f t1, Vec3f t2,
                      TGAImage &image,
                      TGAImage &zbuffer,
                      const TGAColour &colour,
                      int num_threads = -1

);

/*
 * Some stats for the above code on M1 Max MBP
 * image size 800x600, 5,000 triangles
 * compiled -O3 release
 *
 * Line Sweep too 256ms
 *
 * Threads  | 1    | 2    | 3   | 4   | 5   | 6   | 7   | 8   | 9   |
 * Time     | 1800 | 1183 | 880 | 738 | 721 | 703 | 680 | 779 | 812 |
 *          | 1812 | 1109 | 870 | 731 | 717 | 683 | 678 | 746 | 761 |
 *          | 1857 | 1114 | 895 | 740 | 683 | 690 | 681 | 712 | 755 |
 *          | 1805 | 1165 | 885 | 750 | 723 | 704 | 685 | 710 | 756 |
 *          | 1860 | 1177 | 904 | 751 | 734 | 705 | 688 | 705 | 757 |
 *
 * If we up the image size to 4096x4096, the threading model gets close;
 * Line sweep : 9511 ms
 * 6 thread parallel: 11,911ms
 * 10               : 11,194
 * 16               : 9,320
 * 32               : 8,541  <-- This result actually exceeded linesweep performance but only once.
 *
 * In summary, it's a nice model that probably works well on GPUs with 1,000s of cores but it's tought to get
 * performance close to line sweep using only CPU cores.
 */
#endif //TINYRENDERER_SRC_COMMON_TRIANGLE_P_H_
