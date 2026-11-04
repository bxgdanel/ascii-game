#pragma once
#include "Camera.h"
#include "domain.h"
#include <string>
#include <tuple>
#include <vector>
using std::vector;
class Renderer {
protected:
  int W_size, H_size;
  vector<vector<int>> a;
  vector<vector<int>> b;
  vector<vector<float>> zbuf;
  vector<const Surface *> shapes;
  float light_source[3];
  Camera camera;
  const std::string printvals = " .,-~:;=!*#$%@";
  const int printvals_len = 14;
  void print_buffer();
  virtual void ResetDepthBuffer();
  void setCursorPosition(int x, int y);
  virtual void render();
  void task(int y);

public:
  Renderer(int width, int height, float light_source[3], Camera camera);
  Renderer() {}
  void display();
  void add_shape(const Surface *s);
  Camera &getCamera() { return camera; }
};
