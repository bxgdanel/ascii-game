#include "domain.h"
using namespace std;
void Surface::get_normal(float p[3], float n[3]) const {
  float eps = 0.001f;
  n[0] = get_distance(p[0] + eps, p[1], p[2]) -
         get_distance(p[0] - eps, p[1], p[2]);

  n[1] = get_distance(p[0], p[1] + eps, p[2]) -
         get_distance(p[0], p[1] - eps, p[2]);

  n[2] = get_distance(p[0], p[1], p[2] + eps) -
         get_distance(p[0], p[1], p[2] - eps);

  float len = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
  if (len > 0) {
    n[0] /= len;
    n[1] /= len;
    n[2] /= len;
  }
}

bool Surface::intersect(Ray &ray, float &t, float norm[]) const {
  float t_curent = 0.0f;
  const int MAX_STEPS = 80;
  const float MAX_DIST = 100.0f;
  const float SURFACE_DIST = 0.01f;

  for (int i = 0; i < MAX_STEPS; i++) {
    float p[3] = {ray.origin[0] + ray.direction[0] * t_curent,
                  ray.origin[1] + ray.direction[1] * t_curent,
                  ray.origin[2] + ray.direction[2] * t_curent};
    float d = get_distance(p[0], p[1], p[2]);
    if (d < SURFACE_DIST) {
      t = t_curent;
      get_normal(p, norm);
      return true;
    }
    if (t_curent > MAX_DIST)
      break;
    t_curent += d;
  }
  return false;
}

float Terrain::get_distance(float x, float y, float z) const {
  return (y - center[1] - sin(x - center[0]) - cos(z - center[2])) / 1.7321f;
}
