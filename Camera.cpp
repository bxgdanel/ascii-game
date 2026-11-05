#include "Camera.h"
#include <cmath>
Ray Camera::get_ray(int x, int y) {
  Ray ray;
  ray.origin[0] = this->Coords[0];
  ray.origin[1] = this->Coords[1];
  ray.origin[2] = this->Coords[2];

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

  float oldY = pos[1], oldZ = pos[2];
  pos[1] = oldY * cos_x + oldZ * sin_x;
  pos[2] = -oldY * sin_x + oldZ * cos_x;

  float oldX = pos[0];
  oldZ = pos[2];
  pos[0] = oldX * cos_z + oldZ * sin_z;
  pos[2] = -oldX * sin_z + oldZ * cos_z;

  ray.direction[0] = pos[0];
  ray.direction[1] = pos[1];
  ray.direction[2] = pos[2];
  return ray;
}
void Camera::rotate_y_by_angle(float p[3], float angle) {
  float angleRadians = angle * static_cast<float>(M_PI) / 180.0f;

  float cosTheta = std::cos(angleRadians);
  float sinTheta = std::sin(angleRadians);

  float oldX = p[0];
  float oldz = p[2];

  p[0] = oldX * cosTheta + oldz * sinTheta;
  p[2] = -oldX * sinTheta + oldz * cosTheta;
}
void Camera::rotate_z_by_angle(float p[3], float angle) {
  float angleRadians = angle * static_cast<float>(M_PI) / 180.0f;

  float cosTheta = std::cos(angleRadians);
  float sinTheta = std::sin(angleRadians);

  float oldX = p[0];
  float oldY = p[1];

  p[0] = oldX * cosTheta - oldY * sinTheta;
  p[1] = oldX * sinTheta + oldY * cosTheta;
}
void Camera::rotate_x_by_angle(float p[3], float angle) {
  float angleRadians = angle * static_cast<float>(M_PI) / 180.0f;

  float cosTheta = std::cos(angleRadians);
  float sinTheta = std::sin(angleRadians);

  float oldZ = p[2];
  float oldY = p[1];

  p[1] = oldY * cosTheta + oldZ * sinTheta;
  p[2] = -oldY * sinTheta + oldZ * cosTheta;
}
void Camera::move(float c[3]) {
  float angleRadians = rotation_angle * static_cast<float>(M_PI) / 180.0f;

  float cosTheta = std::cos(angleRadians);
  float sinTheta = std::sin(angleRadians);

  float oldx = c[0];
  float oldz = c[2];

  c[0] = oldx * cosTheta + oldz * sinTheta;
  c[2] = -oldx * sinTheta + oldz * cosTheta;
  Coords[0] += c[0];
  Coords[1] += c[1];
  Coords[2] += c[2];
}
