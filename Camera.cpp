#include "Camera.h"
#include <cmath>
using std::vector;
Ray Camera::get_ray(int x, int y, int W_size, int H_size) {
  Ray ray;
  ray.origin[0] = this->Coords[0];
  ray.origin[1] = this->Coords[1];
  ray.origin[2] = this->Coords[2];

  float aspect_ratio = ((float)W_size / (float)H_size) * 0.5;
  float normalized_x = (2.0f * (x + 0.5f) / W_size - 1.0f) * aspect_ratio;
  float normalized_y = (2.0f * (y + 0.5f) / H_size - 1.0f);

  float pos[3] = {normalized_x, normalized_y, 1.0f};
  float len =
      sqrt(normalized_x * normalized_x + normalized_y * normalized_y + 1.0f);
  if (len != 0) {
    pos[0] /= len;
    pos[1] /= len;
    pos[2] /= len;
  }
  rotate_x_by_angle(pos, down_angle);
  rotate_y_by_angle(pos, rotation_angle);
  ray.direction[0] = pos[0];
  ray.direction[1] = pos[1];
  ray.direction[2] = pos[2];
  return ray;
}
