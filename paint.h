#pragma once
#include "function.h"
#include <iostream>
#include <windows.h>

// 隐藏控制台光标
inline void hideCursor() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

inline bool isSnake(int x, int y, const Snake &s) {
  for (auto i : s.body) {
    if (i.x == x && i.y == y)
      return true;
  }
  return false;
}

inline void paint(const Snake &snake, const Position &food, const int speed) {
  hideCursor(); // 隐藏光标
  vector<Position> b = snake.body;
  const string format = getColor(3, true);
  const string format_back = "48;2;46;204;113";
  // 状态栏
  cout << "退出 " << getFormatStr("Esc", getColor("255;107;107", true)) << " ";
  cout << " 方向:" << getFormatStr(snake.direction, format);
  cout << " 长度:" << getFormatStr(static_cast<int>(b.size()), format);
  cout << " 间隔:" << getFormatStr(speed, format) << " ms";
  cout << " 加速:" << getFormatStr("j", format);
  cout << " 减速:" << getFormatStr("k", format);
  cout << " 位置:" << "(" << getFormatStr(b.front().x, format) << ","
       << getFormatStr(b.front().y, format) << ")";
  cout << endl;
  const string out = "  ";
  // 上边界
  for (int i = 0; i < RIGHT + 2; i++)
    std::cout << getFormatStr("  ", format_back);
  cout << endl;
  for (int i = 1; i <= DOWN; i++) {
    // 左边界
    cout << getFormatStr("  ", format_back);
    for (int j = 1; j <= RIGHT; ++j) {
      if (isSnake(i, j, snake) || (food.x == i && food.y == j))
        cout << getFormatStr(out, getColor(i + j, false));
      else
        cout << out;
    }
    // 右边界
    cout << getFormatStr("  ", format_back) << endl;
  }
  // 下边界
  for (int i = 0; i < RIGHT + 2; i++)
    std::cout << getFormatStr("  ", format_back);
  cout << endl;
}
