#include "triangle_p.h"

#include "types.h"
#include "tgaimage.h"
#include <thread>
#include <vector>

/**
 * Fill a triangle using a parallel approach by determining for each point in the
 * bounding box of the triangle, whether or not it lies in the bounds of the triangle.
 * This is how a GPU based implementation may work. Testing on M1 MBP shows that
 * even with threading enabled, it is 5 times slower than the CPU based approach.
 * GPU would no doubt be faster as greater parallelisation could be achieved.
 *
 * @param t0, t1, t2 Vertices of the triangle.
 * @image image The image to which to render the filled triangle
 * @param colour The colour to fill with.
 */
void fill_triangle_bb(Vec2i t0, Vec2i t1, Vec2i t2,
                      TGAImage &image,
                      const TGAColour &colour,
                      int num_threads

) {
  using namespace std;

  // Compute bounding box
  Vec2i bottom_left = {max(0, min(t0.x, min(t1.x, t2.x))),
                       max(0, min(t0.y, min(t1.y, t2.y)))};
  Vec2i top_right = {min(image.width() - 1, max(t0.x, max(t1.x, t2.x))),
                     min(image.height() - 1, max(t0.y, max(t1.y, t2.y)))};
  auto AB = t1 - t0;
  auto AC = t2 - t0;

  if (num_threads == -1) {
    const static unsigned nb_threads_hint = thread::hardware_concurrency();
    num_threads = (nb_threads_hint == 0u ? 8 : nb_threads_hint);
  }

  // Function to do actual triangle fill.
  uint32_t bb_width = top_right.x - bottom_left.x + 1;
  auto fill_function = [&](uint32_t idx) {
    int32_t yi = (int32_t) bottom_left.y + (idx / bb_width);
    int32_t xi = (int32_t) bottom_left.x + (idx % bb_width);

    // Compute barycentric coords wrt triangle
    Vec2i PA{t0.x - xi, t0.y - yi};
    auto v0 = Vec3i(AB.x, AC.x, PA.x);
    auto v1 = Vec3i(AB.y, AC.y, PA.y);
    auto cp = v0.cross(v1);
    if (cp.z == 0) return;
    if (((float) cp.y / (float) cp.z) < 0) return;
    if (((float) cp.x / (float) cp.z) < 0) return;
    if ((1.0f - ((cp.x + cp.y) / (float) cp.z)) < 0) return;
    image.set(xi, yi, colour);
  };

  // [Helper] Inner loop
  auto launch_range = [&fill_function](uint32_t k1, uint32_t k2) {
    for (auto k = k1; k < k2; k++) {
      fill_function(k);
    }
  };

  auto start = 0u;
  uint32_t data_size = (top_right.y - bottom_left.y + 1) * bb_width;
  auto end = data_size - 1;
  auto slice_size = max(1u, (uint32_t) round(data_size / static_cast<double> (num_threads)));

  // Create pool and launch jobs
  vector<thread> pool;
  pool.reserve(num_threads);

  auto i1 = start;
  auto i2 = min(start + slice_size, end);
  for (unsigned i = 0; i + 1 < num_threads && i1 < end; ++i) {
    pool.emplace_back(launch_range, i1, i2);
    i1 = i2;
    i2 = std::min(i2 + slice_size, end);
  }
  if (i1 < end) {
    pool.emplace_back(launch_range, i1, end);
  }

  // Wait for jobs to finish
  for (thread &t: pool) {
    if (t.joinable()) {
      t.join();
    }
  }
}