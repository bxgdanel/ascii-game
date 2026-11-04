#pragma once
#include "Camera.h"
#include <cmath>
#include <vector>
using std::vector;
class Surface {
public:
  vector<float> center = {0, 0, 0};
  float angle_x = 0, angle_z = 0;

  virtual ~Surface() = default;

  void rotate_x(float unghi) { angle_x += unghi; }
  void rotate_z(float unghi) { angle_z += unghi; }
  void translate(float x, float y, float z) {
    center[0] += x, center[1] += y, center[2] += z;
  }

  virtual float get_distance(vector<float> p) const = 0;
  vector<float> get_normal(vector<float> p) const;
  bool intersect(Ray &ray, float &t, float normals[]) const;
};
class Torus : public Surface {
  float R = 0, r = 0;

public:
  void generate(float big_r, float small_r) { R = big_r, r = small_r; }
  float get_distance(vector<float> p) const override;
};
class Cube : public Surface {
  float dim[3];

public:
  void generate(float dimx, float dimy, float dimz) {
    dim[0] = dimx, dim[1] = dimy, dim[2] = dimz;
  }
  float get_distance(vector<float> p) const override;
};

class Terrain : public Surface {
  float dim[3];

public:
  void generate(float x, float y, float z) {
    dim[0] = x, dim[1] = y, dim[2] = z;
  }
  float get_distance(vector<float> p) const override;
};
