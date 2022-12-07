/*
 * TGA Image file handler.
 * Derived from https://en.wikipedia.org/wiki/Truevision_TGA
 *
 */

#ifndef TINYRENDERER_SRC_TGAIMAGE_H_
#define TINYRENDERER_SRC_TGAIMAGE_H_

#include <string>
#include <vector>

struct TGAColour {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
  TGAColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) //
      : r{red} //
      , g{green} //
      , b{blue} //
      , a{alpha} //
  {}
};

class TGAImage {
 public:
  enum Type {
    RGB = 2,
  };

  TGAImage(uint16_t width, uint16_t height, Type type);
  void set(uint16_t x, uint16_t y, const TGAColour &colour);
  void flip_vertically();
  void write_tga_file(const std::string &file_name) const;

 private:
  bool is_flipped_;
  bool has_alpha_;
  uint16_t width_;
  uint16_t height_;
  uint8_t bytes_per_pixel;
  Type type_;
  uint8_t pixel_depth_;
  std::vector<uint8_t> data_;

};

#endif //TINYRENDERER_SRC_TGAIMAGE_H_
