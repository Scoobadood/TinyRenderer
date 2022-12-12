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
  TGAColour operator()(uint16_t x, uint16_t y) const;

  void flip_vertically();
  void write_tga_file(const std::string &file_name) const;
  inline uint16_t width() const {
    return width_;
  }
  inline uint16_t height() const {
    return height_;
  }

 private:
  bool is_flipped_;
  bool has_alpha_;
  uint16_t width_;
  uint16_t height_;
  uint8_t bytes_per_pixel_;
  Type type_;
  uint8_t pixel_depth_;
  uint8_t *data_;
  uint32_t data_size_;
};

#endif //TINYRENDERER_SRC_TGAIMAGE_H_
