
#include "tgaimage.h"
#include "types.h"
#include "triangle.h"
#include "triangle_p.h"
#include <cmath>
#include <iostream>
#include <spdlog/spdlog-inl.h>
/**
 * Args:
 *  num_threads num_triangles width height
 * @return
 */
int main(int argc, char **argv) {
  using namespace std;

  auto num_threads = (argc > 1) ? atoi(argv[1]) : -1;
  auto num_triangles = (argc > 2) ? atoi(argv[2]) : 5000;
  auto width = (argc > 3) ? atoi(argv[3]) : 800;
  auto height = (argc > 4) ? atoi(argv[4]) : 600;

  if( num_threads == 0 || num_triangles == 0 || width <=10 || height <= 10) {
    cout << "Usage: " << argv[0] << "[num_threads > 0] [num_triangles > 0] [width > 10] [height > 10]" << endl;
    return EXIT_FAILURE;
  }

  vector<vector<Vec2i>> triangles;
  vector<TGAColour> colours;
  for (int i = 0; i < num_triangles; i++) {

    triangles.push_back({{(int16_t)(arc4random() % width), (int16_t)(arc4random() % height)},
                         {(int16_t)(arc4random() % width), (int16_t)(arc4random() % height)},
                         {(int16_t)(arc4random() % width), (int16_t)(arc4random() % height)}});
    colours.emplace_back((uint8_t)(arc4random() % 0xff),
                         (uint8_t)(arc4random() % 0xff),
                         (uint8_t)(arc4random() % 0xff),
                         255);
  }

  TGAImage image(width, height, TGAImage::RGB);
  auto start = std::chrono::steady_clock::now();
  for (int i = 0; i < triangles.size(); i++) {
    fill_triangle(triangles.at(i)[0], triangles.at(i)[1], triangles.at(i)[2], image, colours[i]);
  }
  auto basic_end = std::chrono::steady_clock::now();
  image.write_tga_file("triangle_basic.tga");

  TGAImage image2(width, height, TGAImage::RGB);
  auto bb_start = std::chrono::steady_clock::now();
  for (int i = 0; i < triangles.size(); i++) {
    fill_triangle_bb(triangles.at(i)[0], triangles.at(i)[1], triangles.at(i)[2], image2, colours[i], num_threads);
  }
  auto bb_end = std::chrono::steady_clock::now();
  image2.write_tga_file("triangle_bb.tga");

  spdlog::info("Elapsed time for basic triangles {} ms",
               std::chrono::duration_cast<std::chrono::milliseconds>(basic_end - start).count());
  spdlog::info("Elapsed time for BB triangles {} ms",
               std::chrono::duration_cast<std::chrono::milliseconds>(bb_end - bb_start).count());
  return EXIT_SUCCESS;
}