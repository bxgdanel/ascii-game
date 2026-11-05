#include "Camera.h"
#include "domain.h"
#include "renderer.h"
#include <mutex>
#include <termios.h>
#include <thread>
#include <unistd.h>
#define width 320
#define height 160
float ls[3] = {0, 2, -10};
float cam_position[3] = {0, 0, 0};
Camera camera = Camera(cam_position, width, height);
Renderer r = Renderer(width, height, ls, camera);
std::mutex mtx;

char readKey() {
  struct termios oldt, newt;

  tcgetattr(STDIN_FILENO, &oldt);

  newt = oldt;
  newt.c_lflag &=
      ~(ICANON | ECHO); // dezactiveaza ICANON => nu mai foloseste buffer,
                        // ECHO => nu se mai afiseaza in terminal

  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  char ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return ch;
}
void thread_input() {
  float input_buf[3];
  int input_rot = 0, input_d = 0;
  while (true) {
    input_buf[0] = 0;
    input_buf[1] = 0;
    input_buf[2] = 0;
    char c = readKey();
    switch (c) {
    case 'w':
      input_buf[2] = 1;
      break;
    case 's':
      input_buf[2] = -1;
      break;
    case 'a':
      input_buf[0] = -1;
      break;
    case 'd':
      input_buf[0] = 1;
      break;
    case ' ':
      input_buf[1] = 1;
      break;
    case 'm':
      input_buf[1] = -1;
      break;
    case '[':
      input_rot -= 15;
      break;
    case ']':
      input_rot += 15;
      break;
    case 'h':
      input_d -= 15;
      if (input_d < -85)
        input_d = -85;
      break;
    case 'y':
      input_d += 15;
      if (input_d > 85)
        input_d = 85;
      break;
    }
    mtx.lock();
    r.getCamera().move(input_buf);
    r.getCamera().rotation_angle = input_rot;
    r.getCamera().down_angle = input_d;
    mtx.unlock();
  }
}
void thread_output() {
  while (true) {
    mtx.lock();
    Camera snap = r.getCamera();
    mtx.unlock();

    r.display(snap);
  }
}

int main() {
  Terrain test;
  test.generate(2, 2, 2);
  r.add_shape(&test);
  test.translate(-10, -30, -10);
  std::thread t_in(thread_input);
  std::thread t_out(thread_output);

  t_in.join();
  t_out.join();
}
