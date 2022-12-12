# Render a variable number of triangles in two different
# Ways and time how long it takes.
add_executable(triangles_timing
        triangles_timing.cpp)

target_link_libraries(triangles_timing
        common)

# Render the african head OBJ file with randomly coloured triangles
add_executable(triangle_render
        triangle_render.cpp)

target_link_libraries(triangle_render
        common)


# Render the african head OBJ file with flat shaded triangles
# Use face normals to determine colour mapping XYZ -> RGB
# Or using a cmdline spec'd base colour.
add_executable(flat_shade
        flat_shade.cpp)

target_link_libraries(flat_shade
        common)

