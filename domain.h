#pragma once
#include "Camera.h"
#include <cmath>
#include <vector>
using std::vector;
class Surface {
public:
  float sin_x, cos_x, sin_z, cos_z;
  vector<float> center = {0, 0, 0};
  float angle_x = 0, angle_z = 0;

  virtual ~Surface() = default;

  void rotate_x(float unghi) { angle_x += unghi; }
  void rotate_z(float unghi) { angle_z += unghi; }
  void translate(float x, float y, float z) {
    center[0] += x, center[1] += y, center[2] += z;
  }

  virtual float get_distance(float x, float y, float z) const = 0;
  void get_normal(float p[3], float n[3]) const;
  bool intersect(Ray &ray, float &t, float normals[]) const;
};

class Terrain : public Surface {
  float dim[3];

public:
  void generate(float x, float y, float z) {
    dim[0] = x, dim[1] = y, dim[2] = z;
  }
  float get_distance(float x, float y, float z) const override;
};
