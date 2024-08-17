#pragma once
#include "run.h"
#include "struct.h"
#include <conio.h>
#include <future>

inline void init() {

  // 初始化一条蛇
  Snake snake;
  vector<Position> body = {
      Position(1, 1), Position(1, 2), Position(2, 2), Position(2, 3),
      Position(2, 4), Position(2, 5), Position(2, 6),
  };
  snake.body = body;
  snake.direction = "左";

  auto task = async(launch::async, run_snake, ref(snake));

  char op;
  while (true) {
    op = _getch();
    string *dire = &snake.direction;
    switch (op) {
    case 'w':
      if (*dire == "左" || *dire == "右")
        *dire = "上";
      break;
    case 's':
      if (*dire == "左" || *dire == "右")
        *dire = "下";
      break;
    case 'a':
      if (*dire == "上" || *dire == "下")
        *dire = "左";
      break;
    case 'd':
      if (*dire == "上" || *dire == "下")
        *dire = "右";
      break;
    case 'j':
      ACCELERATE += 10; // 使用变量 accelerate
      break;
    case 'k':
      ACCELERATE -= 10; // 使用变量 accelerate
      break;
    case 27: // ESC 键
      cout << "\n游戏结束..." << endl;
      exit(0);
    default:
      break;
    }
  }
}
