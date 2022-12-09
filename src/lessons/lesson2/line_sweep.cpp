
#include "tgaimage.h"
#include "line.h"
#include "types.h"

#include <cmath>

void fill_flat_triangle(Vec2i v0, Vec2i v1, Vec2i v2,
                        TGAImage &image,
                        const TGAColour &colour) {
  assert(v0.y == v1.y || v0.y == v2.y || v1.y == v2.y);

  int16_t from_x, from_y, to_y, to_left_x, to_right_x;
  if (v0.y == v1.y) {
    from_x = v2.x;
    from_y = v2.y;
    to_y = v0.y;
    to_left_x = (v0.x < v1.x) ? v0.x : v1.x;
    to_right_x = (v0.x < v1.x) ? v1.x : v0.x;
  } else if (v0.y == v2.y) {
    from_x = v1.x;
    from_y = v1.y;
    to_y = v0.y;
    to_left_x = (v0.x < v2.x) ? v0.x : v2.x;
    to_right_x = (v0.x < v2.x) ? v2.x : v0.x;
  } else {
    from_x = v0.x;
    from_y = v0.y;
    to_y = v1.y;
    to_left_x = (v1.x < v2.x) ? v1.x : v2.x;
    to_right_x = (v1.x < v2.x) ? v2.x : v1.x;
  }
  auto step_y = to_y > from_y ? 1 : -1;
  auto delta_y = abs(to_y - from_y) + 1;
  float left_delta = (to_left_x-from_x) / (float) (delta_y);
  float right_delta = (to_right_x-from_x) / (float) (delta_y);
  for (auto i = 0; i < delta_y; ++i) {
    auto left_x = from_x + (left_delta * i);
    auto right_x = from_x + (right_delta * i);
    auto y = from_y + (step_y * i);
    line(left_x, y, right_x, y, image, colour);
  }
}

void fill_triangle(Vec2i v0, Vec2i v1, Vec2i v2,
                   TGAImage &image,
                   const TGAColour &colour
) {
  using namespace std;

  if (v0.y == v1.y || v0.y == v2.y || v1.y == v2.y) {
    fill_flat_triangle(v0, v1, v2, image, colour);
    return;
  }

  // Split into two flat triangles and render separately
  if (v0.y > v1.y) { swap(v0, v1); }
  if (v0.y > v2.y) { swap(v0, v2); }
  if (v1.y > v2.y) { swap(v1, v2); }
  auto tempx = v0.x + round(((v1.y - v0.y) / (float) (v2.y - v0.y)) * (v2.x - v0.x));
  Vec2i temp = {(int16_t) tempx, v1.y};
  fill_flat_triangle(v0, v1, temp, image, colour);
  fill_flat_triangle(v2, v1, temp, image, colour);
}

int main(int argc, char **argv) {
  auto width = 400;
  auto height = 400;
  TGAImage image(width, height, TGAImage::RGB);

  for( int i=0; i<50; i++ ) {
    TGAColour green(rand()%255, rand()%255, rand()%255, 255);
    Vec2i v0 = {(int16_t)(rand()%width), (int16_t)(rand()%height)};
    Vec2i v1 = {(int16_t)(rand()%width), (int16_t)(rand()%height)};
    Vec2i v2 = {(int16_t)(rand()%width), (int16_t)(rand()%height)};
    fill_triangle(v0, v1, v2, image, green);
  }

  image.write_tga_file("triangle.tga");
  return 0;
}