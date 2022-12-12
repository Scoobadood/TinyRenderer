add_library(common
        tgaimage.cpp tgaimage.h
        line.cpp line.h
        obj.cpp obj.h
        tiny_obj_loader.h
        triangle.cpp triangle.h
        triangle_p.cpp triangle_p.h)

target_include_directories(common
        PUBLIC
        .)