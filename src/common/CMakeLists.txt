add_library(common
        tgaimage.cpp tgaimage.h
        line.cpp line.h
        obj.cpp obj.h
        tiny_obj_loader.h)

target_include_directories(common
        PUBLIC
        .)