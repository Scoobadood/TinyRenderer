#include "tgaimage.h"
#include "obj.h"
#include "triangle.h"

int main(int argc, char **argv) {
  using namespace std;

  auto width = 1024;
  auto height = 1024;
  auto scale_x = width / 2.0f;
  auto scale_y = height / 2.0f;
  TGAImage image(width, height, TGAImage::RGB);
  TGAColour white(255, 255, 255, 255);

  auto vf = load_obj_file(argv[1]);
  const auto &vertices = vf.first;
  const auto &faces = vf.second;
  for (const auto &face: faces) {
    auto v0 = vertices.at(face[0]);
    auto v1 = vertices.at(face[1]);
    auto v2 = vertices.at(face[2]);

    Vec2i sc0 = Vec2i((v0.x + 1.0f) * scale_x, (v0.y + 1.0f) * scale_y);
    Vec2i sc1 = Vec2i((v1.x + 1.0f) * scale_x, (v1.y + 1.0f) * scale_y);
    Vec2i sc2 = Vec2i((v2.x + 1.0f) * scale_x, (v2.y + 1.0f) * scale_y);
    TGAColour
        colour{(uint8_t) (arc4random() % 0xff),
               (uint8_t) (arc4random() % 0xff),
               (uint8_t) (arc4random() % 0xff), (uint8_t) 0xff};
        fill_triangle(sc0, sc1, sc2, image, colour);
    }
    image.write_tga_file("head_tf.tga");
    return EXIT_SUCCESS;
  }
