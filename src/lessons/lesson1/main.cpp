/*
 * Learning to line. A series of line drawing exercises.
 */

#include "tgaimage.h"
#include "line.h"
#include "obj.h"

#include <spdlog/spdlog.h>
#include <vector>
#include <string>

int main(int argc, char **argv) {
  using namespace std;

  auto width = 400;
  auto height = 400;
  auto scale_x = width / 2.0f;
  auto scale_y = height / 2.0f;
  TGAImage image(width, height, TGAImage::RGB);
  TGAColour white(255, 255, 255, 255);

  auto vf = load_obj_file(argv[1]);
  for (const auto &face: vf.second) {
    for (auto v = 0; v < 3; ++v) {
      auto v0 = vf.first.at(face.at(v));
      auto v1 = vf.first.at(face.at((v + 1) % 3));

      auto x0 = (v0.x + 1.0f) * scale_x;
      auto y0 = (v0.y + 1.0f) * scale_y;
      auto x1 = (v1.x + 1.0f) * scale_x;
      auto y1 = (v1.y + 1.0f) * scale_y;
      line(x0, y0, x1, y1, image, white);
    }
  }
  image.write_tga_file("head_wf.tga");
  return EXIT_SUCCESS;
}
