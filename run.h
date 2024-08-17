#pragma once
#include "paint.h"
#include "struct.h"
#include <algorithm>
#include <unordered_set>
#include <windows.h>
using namespace std;

inline bool operator<(const Position &p1, const Position &p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

inline Position get_position(Position p, string d) {
  int x, y;
  if (d == "上") {
    x = p.x - 1;
    y = p.y;
  } else if (d == "下") {
    x = p.x + 1;
    y = p.y;
  } else if (d == "左") {
    x = p.x;
    y = p.y - 1;
  } else {
    x = p.x;
    y = p.y + 1;
  }

  return Position(x, y);
}

inline void run_snake(Snake &snake) {

  srand(time(nullptr));

  // 界面
  vector<Position> board;
  for (int i = 1; i < DOWN; i++) {
    for (int j = 1; j < RIGHT; j++) {
      board.emplace_back(i, j);
    }
  }

  cout << "请把窗口最大化" << endl;
  // 暂停3秒
  Sleep(3000);
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
  COORD pos = {0, 0};                                // 光标位置

  bool flag = true; // 判断是否生成食物

  Position food;
  while (true) {
    SetConsoleCursorPosition(hConsole, pos); // 光标位置设置为左上角
    //------------------------------------------------------------------------
    // 蛇头
    Position head = snake.body.front();
    // 时间间隔
    int t = (SPEED - snake.body.size() / 5 * 10) - ACCELERATE;

    int time;
    if (t >= 0)
      time = t;
    else
      time = 0;

    // 打印当前状态
    paint(snake, food, time);

    // 根据移动方向改变蛇的状态
    head = get_position(head, snake.direction);
    // 到达边界
    if (head.x == 0)
      head.x = DOWN;
    if (head.y == 0)
      head.y = RIGHT;
    if (head.x == DOWN + 1)
      head.x = 1;
    if (head.y == RIGHT + 1)
      head.y = 1;
    snake.body.insert(snake.body.begin(), head);
    snake.body.pop_back();

    // 随机生成食物
    if (flag) {
      vector<Position> b = snake.body;
      sort(board.begin(), board.end());
      sort(b.begin(), b.end());
      vector<Position> diff;
      set_symmetric_difference(board.begin(), board.end(), b.begin(), b.end(),
                               back_inserter(diff));
      food = diff.at(rand() % diff.size());
      flag = false;
    }

    // 判断是否撞上自己
    if (snake.body.size() >= 4) {
      vector<Position> b2 = snake.body;
      head = snake.body.front();
      b2.erase(b2.begin(), b2.begin() + 3);
      for (auto i : b2) {
        if (i.x == head.x && i.y == head.y) {
          cout << getFormatStr("真的太逊了", getColor(3, true));
          Sleep(3000);
          exit(0);
        }
      }
    }

    // 如果吃到食物
    if (head.x == food.x && head.y == food.y) {
      string dire;
      Position t1 = snake.body.at(snake.body.size() - 2);
      Position t2 = snake.body.back();
      if (t1.x > t2.x)
        dire = "上";
      else if (t1.x < t2.x)
        dire = "下";
      else if (t1.y < t2.y)
        dire = "右";
      else
        dire = "左";
      snake.body.push_back(get_position(t2, dire));
      flag = true;
    }

    //------------------------------------------------------------------------
    Sleep(time);
  }
}
