#pragma once
#include <cmath>
#include <vector>
struct Ray {
  float origin[3];
  float direction[3];
};
class Camera {
private:
  float sin_x, cos_x, sin_z, cos_z;
  float aspect_ratio, W_size, H_size;

  void rotate_y_by_angle(float p[3], float angle);
  void rotate_z_by_angle(float p[3], float angle);
  void rotate_x_by_angle(float p[3], float angle);

public:
  float Coords[3] = {0, 0, 0};
  float rotation_angle = 0.0f, down_angle = 0.0f;

  Camera(float c[3], float _W_size, float _H_size) {
    Coords[0] = c[0];
    Coords[1] = c[1];
    Coords[2] = c[2];
    rotation_angle = 0.0f;
    down_angle = 0.0f;
    W_size = _W_size, H_size = _H_size;
    aspect_ratio = ((float)_W_size / (float)_H_size) * 0.5;
  }
  Camera() {
    Coords[0] = 0;
    Coords[1] = 0;
    Coords[2] = 0;
    rotation_angle = 0.0f;
    down_angle = 0.0f;
  }

  void setPosition(float c[3]) {
    Coords[0] = c[0], Coords[1] = c[1], Coords[2] = c[2];
  }
  void move(float c[3]);

  Ray get_ray(int x, int y);

  void update_cache() {
    float rad_rot = rotation_angle * M_PI / 180.0f;
    float rad_down = down_angle * M_PI / 180.0f;
    cos_x = std::cos(rad_down);
    sin_x = std::sin(rad_down);
    cos_z = std::cos(rad_rot);
    sin_z = std::sin(rad_rot);
  }
};
