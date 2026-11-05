#include "Camera.h"
#include "domain.h"
#include "renderer.h"
#include <termios.h>
#include <thread>
#include <unistd.h>
float ls[3] = {0, 2, -10};
float cam_position[3] = {0, 0, 0};
Camera camera = Camera(cam_position);
Renderer r = Renderer(640, 320, ls, camera);
Terrain test;

char readKey() {
  struct termios oldt, newt;
  char ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}
float input_buf[3];
int input_rot = 0, input_d = 0;
void thread_input() {
  while (true) {
    input_buf[0] = 0;
    input_buf[1] = 0;
    input_buf[2] = 0;
    char c = readKey();
    if (c == 'w')
      input_buf[2] = 1;
    else if (c == 's')
      input_buf[2] = -1;
    else if (c == 'a')
      input_buf[0] = -1;
    else if (c == 'd')
      input_buf[0] = 1;
    else if (c == ' ')
      input_buf[1] = 1;
    else if (c == 'm')
      input_buf[1] = -1;
    else if (c == '[')
      input_rot -= 15;
    else if (c == ']')
      input_rot += 15;
    else if (c == 'h') {
      input_d -= 15;
      if (input_d < -85)
        input_d = -85;
    } else if (c == 'y') {
      input_d += 15;
      if (input_d > 85)
        input_d = 85;
    }
    r.getCamera().move(input_buf);
    r.getCamera().rotation_angle = input_rot;
    r.getCamera().down_angle = input_d;
  }
}
void thread_output() {
  while (true) {
    r.display();
  }
}
int main() {
  test.generate(2, 2, 2);
  r.add_shape(&test);
  test.translate(-10, -30, -10);
  std::thread t_in(thread_input);
  std::thread t_out(thread_output);

  t_in.join();
  t_out.join();
}
