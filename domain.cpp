#include "domain.h"
using namespace std;
vector<float> Surface::get_normal(vector<float> p) const {
  float eps = 0.001f;
  vector<float> n = {get_distance({p[0] + eps, p[1], p[2]}) -
                         get_distance({p[0] - eps, p[1], p[2]}),
                     get_distance({p[0], p[1] + eps, p[2]}) -
                         get_distance({p[0], p[1] - eps, p[2]}),
                     get_distance({p[0], p[1], p[2] + eps}) -
                         get_distance({p[0], p[1], p[2] - eps})};
  float len = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
  if (len > 0) {
    n[0] /= len;
    n[1] /= len;
    n[2] /= len;
  }
  return n;
}
bool Surface::intersect(Ray &ray, float &t, float norm[]) const {
  float t_curent = 0.0f;
  const int MAX_STEPS = 80;
  const float MAX_DIST = 100.0f;
  const float SURFACE_DIST = 0.01f;

  for (int i = 0; i < MAX_STEPS; i++) {
    vector<float> p = {ray.origin[0] + ray.direction[0] * t_curent,
                       ray.origin[1] + ray.direction[1] * t_curent,
                       ray.origin[2] + ray.direction[2] * t_curent};
    float d = get_distance(p);
    if (d < SURFACE_DIST) {
      t = t_curent;
      vector<float> normal_tmp = get_normal(p);
      copy(normal_tmp.begin(), normal_tmp.end(), norm);
      return true;
    }
    if (t_curent > MAX_DIST)
      break;
    t_curent += d;
  }
  return false;
}
float Torus::get_distance(vector<float> p) const {
  float px = p[0] - center[0];
  float py = p[1] - center[1];
  float pz = p[2] - center[2];

  float py_rot = py * cos(angle_x) + pz * sin(angle_x);
  float pz_rot = -py * sin(angle_x) + pz * cos(angle_x);
  py = py_rot;
  pz = pz_rot;

  float px_rot = px * cos(angle_z) + py * sin(angle_z);
  float py_rot2 = -px * sin(angle_z) + py * cos(angle_z);
  px = px_rot;
  py = py_rot2;

  float qx = sqrt(px * px + py * py) - R;
  float qy = pz;
  return sqrt(qx * qx + qy * qy) - r;
}
float Cube::get_distance(vector<float> p) const {
  float px = p[0] - center[0];
  float py = p[1] - center[1];
  float pz = p[2] - center[2];

  float py_rot = py * cos(angle_x) + pz * sin(angle_x);
  float pz_rot = -py * sin(angle_x) + pz * cos(angle_x);
  py = py_rot, pz = pz_rot;
  float px_rot = px * cos(angle_z) + py * sin(angle_z);
  float py_rot2 = -px * sin(angle_z) + py * cos(angle_z);
  px = px_rot, py = py_rot2;

  float qx = std::abs(px) - dim[0];
  float qy = std::abs(py) - dim[1];
  float qz = std::abs(pz) - dim[2];

  float max_qx = std::max(qx, 0.0f);
  float max_qy = std::max(qy, 0.0f);
  float max_qz = std::max(qz, 0.0f);

  float out_dist = sqrt(max_qx * max_qx + max_qy * max_qy + max_qz * max_qz);
  float in_dist = min(max(qx, max(qy, qz)), 0.0f);

  return out_dist + in_dist;
}
float Terrain::get_distance(vector<float> p) const {
  return p[1] - center[1] - sin(p[0] - center[0]) - cos(p[2] - center[2]);
}
