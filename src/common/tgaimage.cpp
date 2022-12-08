//
// Created by Dave Durbin on 8/12/2022.
//

#include "tgaimage.h"

#include <fstream>

TGAImage::TGAImage(uint16_t width, uint16_t height, Type type) {
  assert(width != 0 && height != 0);

  width_ = width;
  height_ = height;
  switch (type) {
    case RGB:bytes_per_pixel_ = 3;
      pixel_depth_ = 24;
      has_alpha_ = false;
      data_size_ = width_ * height_ * bytes_per_pixel_;
      data_ = new uint8_t[data_size_];
      memset(data_, 0, data_size_);
      break;
    default:throw std::runtime_error("Unsupported format " + std::to_string(type));
  }
  type_ = type;
  is_flipped_ = false;
}

// RGB data is actually stored BGR
void TGAImage::set(uint16_t x, uint16_t y, const TGAColour &colour) {
  auto base_idx = (y * width_ + x) * bytes_per_pixel_;
  switch (type_) {
    case RGB:data_[base_idx] = colour.b;
      data_[base_idx + 1] = colour.g;
      data_[base_idx + 2] = colour.r;
      break;
  }
}
void TGAImage::flip_vertically() {
  is_flipped_ = !is_flipped_;
}

void TGAImage::write_tga_file(const std::string &file_name) const {
  std::ofstream f{file_name, std::ios::binary};

  // Header
  /*
   * 1 byte	ID length	Length of the image ID field
   * 1 byte	Color map type	Whether a color map is included
   * 1 byte	Image type	Compression and color types
   * 5 bytes	Color map specification	Describes the color map
   * 10 bytes	Image specification	Image dimensions and format
   */
  struct __attribute__((packed)) header {
    uint8_t len;
    uint8_t cmap_type;
    uint8_t im_type;
    uint16_t cmap_first_entry_idx;
    uint16_t cmap_len;
    uint8_t cmap_entry_sz;
    uint16_t x_orig;
    uint16_t y_orig;
    uint16_t width;
    uint16_t height;
    uint8_t bpp;
    uint8_t im_desc;
  } h{};

  auto x = sizeof(header);

  h.len = 0;
  h.cmap_type = 0;
  h.im_type = 2; // Uncompressed true colour image
  h.cmap_first_entry_idx = 0;
  h.cmap_len = 0;
  h.cmap_entry_sz = 0;
  h.x_orig = 0;
  h.y_orig = 0;
  h.width = width_;
  h.height = height_;
  h.bpp = pixel_depth_;
  h.im_desc = (has_alpha_) ? (0x00 | 0x08) : 0;

  f.write((char *) &h, 18);
  f.write((char *) data_, data_size_);

  f.close();
}
