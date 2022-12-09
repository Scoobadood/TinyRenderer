//
// Created by Dave Durbin on 9/12/2022.
//

#ifndef TINYRENDERER_SRC_COMMON_LINE_H_
#define TINYRENDERER_SRC_COMMON_LINE_H_

void line(uint16_t from_x, uint16_t from_y,
          uint16_t to_x, uint16_t to_y,
          TGAImage &image,
          const TGAColour &colour);
#endif //TINYRENDERER_SRC_COMMON_LINE_H_
