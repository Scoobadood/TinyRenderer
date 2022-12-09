//
// Created by Dave Durbin on 9/12/2022.
//

#ifndef TINYRENDERER_SRC_COMMON_OBJ_H_
#define TINYRENDERER_SRC_COMMON_OBJ_H_

#include "types.h"
#include <vector>

std::pair<std::vector<Vec3f>, std::vector<std::vector<uint32_t>>>
load_obj_file(const std::string &file_name);

#endif //TINYRENDERER_SRC_COMMON_OBJ_H_
