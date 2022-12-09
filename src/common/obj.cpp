#include "types.h"
#include <string>
#include <vector>
#include <spdlog/spdlog-inl.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

std::pair<std::vector<Vec3f>, std::vector<std::vector<uint32_t>>>
load_obj_file(const std::string &file_name) {
  using namespace std;
  tinyobj::attrib_t attrib;
  vector<tinyobj::shape_t> shapes;
  vector<tinyobj::material_t> materials;
  string warn;
  string err;

  if (!LoadObj(&attrib, &shapes, &materials, &warn, &err, file_name.c_str())) {
    auto msg = fmt::format("Couldn't read OBJ file from {}. {} {}", file_name, warn, err);
    spdlog::error(msg);
    throw runtime_error(msg);
  }

  auto num_vertices = attrib.vertices.size() / 3;
  vector<Vec3f> vertices;
  for (auto v = 0; v < num_vertices; ++v) {
    vertices.emplace_back(attrib.vertices.at(v * 3), attrib.vertices.at(v * 3 + 1), attrib.vertices.at(v * 3 + 2));
  }

  vector<vector<uint32_t>> faces;
  for (const auto &shape: shapes) {
    auto num_faces = shape.mesh.num_face_vertices.size();
    auto next = 0;
    for (auto face_idx = 0; face_idx < num_faces; ++face_idx) {
      vector<uint32_t> face;
      for (auto i = 0; i < shape.mesh.num_face_vertices.at(face_idx); ++i) {
        auto vtx_idx = shape.mesh.indices.at(next++).vertex_index;
        face.emplace_back(vtx_idx);
      }
      faces.emplace_back(face);
    }
  }
  return {vertices, faces};
}
