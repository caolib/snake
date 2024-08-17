#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "function.h"
#include "init.h"
#include "struct.h"
#include <conio.h>
#include <future>
#include <iostream>
#include <windows.h>
using namespace std;

void print_color() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
  COORD pos = {0, 0}; // 设置光标位置为左上角

  string out = "  ";

  vector<Block> arr;
  // 插入颜色块
  for (int i = 0; i < 7; i++) {
    // arr.push_back(Block(out, getColor(i, false)));
    arr.emplace_back(out, getColor(i, false));
  }
  // 插入空白块
  for (int i = 0; i < 3; i++) {
    arr.emplace_back(out, "");
  }

  while (true) {
    SetConsoleCursorPosition(hConsole, pos); // 设置光标位置
    //------------------------------------------------------

    for (auto i : arr) {
      cout << getFormatStr(i.out, i.color);
    }
    Block b = arr.back();
    arr.pop_back();
    arr.insert(arr.begin(), b);

    //------------------------------------------------------
    cout << endl;
    Sleep(1000); // 暂停
  }
}

int main() {

  init();

  return 0;
}