#pragma once
#include <cmath>
#include <vector>
using std::vector;
struct Ray {
  float origin[3];
  float direction[3];
};
class Camera {
private:
  float sin_x, cos_x, sin_z, cos_z;
  void rotate_y_by_angle(float p[3], float angle) {
    float angleRadians = angle * static_cast<float>(M_PI) / 180.0f;

    float cosTheta = std::cos(angleRadians);
    float sinTheta = std::sin(angleRadians);

    float oldX = p[0];
    float oldz = p[2];

    p[0] = oldX * cosTheta + oldz * sinTheta;
    p[2] = -oldX * sinTheta + oldz * cosTheta;
  }
  void rotate_z_by_angle(float p[3], float angle) {
    float angleRadians = angle * static_cast<float>(M_PI) / 180.0f;

    float cosTheta = std::cos(angleRadians);
    float sinTheta = std::sin(angleRadians);

    float oldX = p[0];
    float oldY = p[1];

    p[0] = oldX * cosTheta - oldY * sinTheta;
    p[1] = oldX * sinTheta + oldY * cosTheta;
  }
  void rotate_x_by_angle(float p[3], float angle) {
    float angleRadians = angle * static_cast<float>(M_PI) / 180.0f;

    float cosTheta = std::cos(angleRadians);
    float sinTheta = std::sin(angleRadians);

    float oldZ = p[2];
    float oldY = p[1];

    p[1] = oldY * cosTheta + oldZ * sinTheta;
    p[2] = -oldY * sinTheta + oldZ * cosTheta;
  }

public:
  float Coords[3] = {0, 0, 0};
  float rotation_angle = 0.0f, down_angle = 0.0f;
  Ray get_ray(int x, int y, int W_size, int H_size);
  Camera(float c[3]) {
    Coords[0] = c[0];
    Coords[1] = c[1];
    Coords[2] = c[2];
    rotation_angle = 0.0f;
    down_angle = 0.0f;
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
  void move(float c[3]) {
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
};
