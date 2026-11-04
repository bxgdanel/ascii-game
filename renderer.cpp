#include "renderer.h"
#include "Camera.h"
#include "domain.h"
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <unistd.h>
using namespace std;
Renderer::Renderer(int w, int h, float ls[3], Camera camera) {
  W_size = w;
  H_size = h;
  light_source[0] = ls[0];
  light_source[1] = ls[1];
  light_source[2] = ls[2];

  a.resize(W_size, vector<int>(H_size, 0));
  zbuf.resize(W_size, vector<float>(H_size, 0.0f));

  float we = sqrt(pow(light_source[0], 2) + pow(light_source[1], 2) +
                  pow(light_source[2], 2));
  light_source[0] = light_source[0] / we;
  light_source[1] = light_source[1] / we;
  light_source[2] = light_source[2] / we;
  this->camera = camera;
}
void Renderer::print_buffer() {
  string disp = "";
  for (int y = H_size - 1; y >= 0; y--) {
    for (int x = 0; x < W_size - 1; x++) {
      // printf("%c", printvals[a[x][y]]);
      disp += printvals[a[x][y]];
      disp += " ";
    }
    disp += '\n';
  }
  std::cout << disp;
}
void Renderer::ResetDepthBuffer() {
  for (int x = 0; x < W_size; x++)
    for (int y = 0; y < H_size; y++)
      zbuf[x][y] = -1e19;
}
void Renderer::setCursorPosition(int x, int y) {
  printf("\033[%d;%dH", y + 1, x + 1);
  fflush(stdout);
}
void Renderer::render() {
  for (int y = 0; y < H_size; y++)
    for (int x = 0; x < W_size; x++) {
      Ray ray = camera.get_ray(x, y, W_size, H_size);

      float t_min = 1e9;
      const Surface *closest_surf = nullptr;
      float intersection_norm[3];

      for (auto s : shapes) {
        float t = 1e9f;
        float normal[3];
        if (s->intersect(ray, t, normal))
          if (t < t_min && t > 0) {
            t_min = t;
            closest_surf = s;
            copy(begin(normal), end(normal), begin(intersection_norm));
          }
      }
      if (closest_surf != nullptr) {
        float n_len = sqrt(intersection_norm[0] * intersection_norm[0] +
                           intersection_norm[1] * intersection_norm[1] +
                           intersection_norm[2] * intersection_norm[2]);
        if (n_len > 0) {
          intersection_norm[0] /= n_len;
          intersection_norm[1] /= n_len;
          intersection_norm[2] /= n_len;
        }
        float brightness = intersection_norm[0] * light_source[0] +
                           intersection_norm[1] * light_source[1] +
                           intersection_norm[2] * light_source[2];
        float ambient = 0.15f;
        if (brightness < 0.0f)
          brightness = 0.0f;
        brightness += ambient;
        if (brightness > 1.0f)
          brightness = 1.0f;
        a[x][y] = brightness * (printvals_len - 1);
      } else {
        a[x][y] = 0;
      }
    }
}

void Renderer::display() {
  setCursorPosition(0, 0);
  ResetDepthBuffer();
  render();
  print_buffer();
}
void Renderer::add_shape(const Surface *s) { shapes.push_back(s); }
