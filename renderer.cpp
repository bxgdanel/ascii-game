#include "renderer.h"
#include "Camera.h"
#include "domain.h"
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

  float we = sqrt(pow(light_source[0], 2) + pow(light_source[1], 2) +
                  pow(light_source[2], 2));
  light_source[0] = light_source[0] / we;
  light_source[1] = light_source[1] / we;
  light_source[2] = light_source[2] / we;

  char hidec[] = "\033[?25l";
  write(STDOUT_FILENO, hidec, sizeof(hidec));

  this->camera = camera;
}
void Renderer::print_buffer() {
  int index = 0;
  for (int y = H_size - 1; y >= 0; y--) {
    for (int x = 0; x < W_size - 1; x++) {
      disp[index++] = printvals[a[y][x]];
    }
    disp[index++] = '\n';
  }
  write(STDOUT_FILENO, disp, index * sizeof(char));
}

void Renderer::setCursorPosition(int x, int y) {
  char buf[32];
  int len = snprintf(buf, sizeof(buf), "\033[%d;%dH", y + 1, x + 1);
  if (len > 0) {
    write(STDOUT_FILENO, buf, len);
  }
}
void Renderer::task(int y, Camera snap) {
  for (int x = 0; x < W_size; x++) {
    Ray ray = snap.get_ray(x, y);

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
      float brightness = intersection_norm[0] * light_source[0] +
                         intersection_norm[1] * light_source[1] +
                         intersection_norm[2] * light_source[2];

      float ambient = 0.15f;
      brightness = brightness < 0 ? 0 : brightness;
      brightness += ambient;
      brightness = brightness > 1.0f ? 1.0f : brightness;

      a[y][x] = brightness * (printvals_len - 1);

    } else {
      a[y][x] = 0;
    }
  }
}
void Renderer::render(Camera snap) {
  snap.update_cache();
  for (int y = 0; y < H_size; y++)
    task(y, snap);
}

void Renderer::display(Camera snap) {
  setCursorPosition(0, 0);
  render(snap);
  print_buffer();
}
void Renderer::add_shape(const Surface *s) { shapes.push_back(s); }

Renderer::~Renderer() {
  char showc[] = "\033[?25h";
  write(STDOUT_FILENO, showc, sizeof(showc));
}
