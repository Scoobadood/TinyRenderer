/*
 * Learning to line. A series of line drawing exercises.
 */

#include <cmath>
#include "tgaimage.h"

/**
 * Naive line drawer using a parametric approach.
 * Note that the step size will cause this to be a problem for lines loinger than 100 pixels.
 *
 * @param from_x
 * @param from_y
 * @param to_x
 * @param to_y
 * @param colour
 */
void line(uint16_t from_x, uint16_t from_y,
          uint16_t to_x, uint16_t to_y,
          TGAImage &image,
          const TGAColour &colour) {
  using namespace std;

  bool steep = (abs(to_x - from_x) < abs(to_y - from_y));
  if (steep) {
    swap(to_x, to_y);
    swap(from_x, from_y);
  }
  if (from_x > to_x) {
    swap(from_x, to_x);
    swap(from_y, to_y);
  }
  int dx = to_x - from_x;
  int dy = to_y - from_y;
  int derror2 = std::abs(dy) * 2;
  int error2 = 0;
  int y = from_y;
  for (int x = from_x; x <= to_x; x++) {
    if (steep) {
      image.set(y, x, colour);
    } else {
      image.set(x, y, colour);
    }
    error2 += derror2;
    if (error2 > dx) {
      y += (to_y > from_y ? 1 : -1);
      error2 -= dx * 2;
    }
  }
}

int main(int argc, char **argv) {
  TGAImage image(150, 150, TGAImage::RGB);

  TGAColour green(0, 255, 0, 0);
  TGAColour red(255, 0, 0, 0);

  for (auto i = 0; i < 1000000; ++i) {
    line(10, 20, 20, 140, image, green);
    line(22, 140, 12, 20, image, red);

    line(20, 10, 140, 20, image, green);
    line(140, 22, 20, 12, image, red);
  }

  image.write_tga_file("output.tga");
  return 0;
}
