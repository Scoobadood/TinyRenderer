#include "triangle.h"
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
) {
  using namespace std;

  // Handle degenerate triangles
  if (t0.y == t1.y && t0.y == t2.y) return;

  // Sort the vertices, t0, t1, t2 lower−to−upper
  if (t0.y > t1.y) swap(t0, t1);
  if (t0.y > t2.y) swap(t0, t2);
  if (t1.y > t2.y) swap(t1, t2);

  int total_height = t2.y - t0.y;
  for (int i = 0; i < total_height; i++) {
    auto pixel_y = t0.y + i;

    // An arbitrary triangle can be split into two other triangles joined along a horizontal line
    // If the original triangle has two vertices with the same Y, the second triangle is effectively
    // zero height.
    // We are into the second triangle iff we pass the t1 vertex or if t1 and t0 are on the same row
    bool second_half = i > t1.y - t0.y || t1.y == t0.y;
    int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
    // Compute ratio of t0-t2 edge
    float long_slope = (float) i / total_height;

    // and similarly for the other edge which may be t0-t1 or t1-t2
    float short_slope = (float) (i - (second_half ? t1.y - t0.y : 0)) / segment_height;
    Vec2i bound1 = t0 + (t2 - t0) * long_slope;
    Vec2i bound2 = second_half ? t1 + (t2 - t1) * short_slope : t0 + (t1 - t0) * short_slope;

    // Fill the row left to right
    if (bound1.x > bound2.x) swap(bound1, bound2);
    for (auto pixel_x = bound1.x; pixel_x <= bound2.x; ++pixel_x) {
      image.set(pixel_x, pixel_y, colour); // attention, due to int casts t0.y+i != A.y
    }
  }
}
