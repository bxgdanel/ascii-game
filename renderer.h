#pragma once
#include "Camera.h"
#include "domain.h"
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using std::string;
using std::vector;
class Renderer {
protected:
  int W_size, H_size;
  int a[320][640];

  float light_source[3];
  Camera camera;
  vector<const Surface *> shapes;

  const std::string printvals = " .,-~:;=!*#$%@";
  const int printvals_len = 14;
  char disp[205500];

  std::mutex mtx;

  void render(Camera snap);
  void task(int y, Camera snap);
  void setCursorPosition(int x, int y);
  void print_buffer();

public:
  Renderer(int width, int height, float light_source[3], Camera camera);
  Renderer() {}
  ~Renderer();

  void display(Camera s);
  void add_shape(const Surface *s);
  Camera &getCamera() { return camera; }
};
