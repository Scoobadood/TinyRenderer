#include "tgaimage.h"
#include "obj.h"
#include "triangle_p.h"

int main(int argc, char **argv) {
  using namespace std;

  bool colour_normals = argc > 2 && argv[2][0] == 'n';

  auto width = 1024;
  auto height = 1024;
  auto scale_x = width / 2.0f;
  auto scale_y = height / 2.0f;
  TGAImage image(width, height, TGAImage::RGB);
  TGAImage zbuffer(width, height, TGAImage::RGB);

  auto vf = load_obj_file(argv[1]);
  const auto &vertices = vf.first;
  const auto &faces = vf.second;
  for (const auto &face: faces) {
    auto v0 = vertices.at(face[0]);
    auto v1 = vertices.at(face[1]);
    auto v2 = vertices.at(face[2]);

    auto e1 = v1 - v0;
    auto e2 = v2 - v0;
    auto n = e1.cross(e2).normalized();
    auto dp = n.dot(Vec3f{0, 0, 1});

    // Cull backfaces
    if (dp < 0) continue;

    TGAColour colour{0, 0, 0, 0};
    if (colour_normals)
      colour = {(uint8_t) ((n.x / 2.0f + 0.5f) * 255.0f),
                (uint8_t) ((n.y / 2.0f + 0.5f) * 255.0f),
                (uint8_t) ((n.z / 2.0f + 0.5f) * 255.0f),
                (uint8_t) 0xff};
    else
      colour = {(uint8_t) (dp * 255.0f),
                (uint8_t) (dp * 255.0f),
                (uint8_t) (dp * 255.0f),
                (uint8_t) 255};

    Vec3f sc0 = Vec3f((v0.x + 1.0f) * scale_x, (v0.y + 1.0f) * scale_y, v0.z);
    Vec3f sc1 = Vec3f((v1.x + 1.0f) * scale_x, (v1.y + 1.0f) * scale_y, v1.z);
    Vec3f sc2 = Vec3f((v2.x + 1.0f) * scale_x, (v2.y + 1.0f) * scale_y, v2.z);
    fill_triangle_bb(sc0, sc1, sc2, image, zbuffer, colour);
  }
  image.write_tga_file("head_fs.tga");
  zbuffer.write_tga_file("head_depth.tga");
  return EXIT_SUCCESS;
}
