#pragma once
#include <string>
#include <vector>
using namespace std;

#define DOWN 25     // 下边界
#define RIGHT 60    // 右边界
#define SPEED 100   // 速度，多少毫秒刷新一次页面
int ACCELERATE = 0; // 加速

// todo:彩虹rgb字符串
vector<string> rainbow{"21;109;243", "255;107;107", "240;214;62", "204;93;232",
                       "32;201;151", "255;146;43",  "18;203;196"};

class Block {
public:
  string out;
  string color;

  Block(const string &out, const string &color) : out(out), color(color) {}
};

class Position {
public:
  Position() = default;

  Position(int x, int y) : x(x), y(y) {}

  int x;
  int y;
};

class Snake {
public:
  vector<Position> body;
  string direction;
};
