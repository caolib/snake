#pragma once
#include "struct.h"
#include <ostream>
#include <string>
#include <vector> // 确保包含 <vector> 头文件
using namespace std;

// 带有属性的格式化输出
inline string getFormatStr(string output, string format) {
  return "\033[" + format + "m" + output + "\033[0m";
}

inline string getFormatStr(int output, string format) {
  return "\033[" + format + "m" + to_string(output) + "\033[0m";
}

// 定义 operator<<
inline std::ostream &operator<<(std::ostream &out, std::vector<int> arr) {
  for (const auto &elem : arr) {
    out << elem << " ";
  }
  return out;
}

// true->前景 false->背景
inline string getColor(int i, bool flag) {
  string color = "";
  i %= 7;
  return flag ? "38;2;" + rainbow.at(i) : "48;2;" + rainbow.at(i);
}

// 根据rgb字符串获取颜色
inline string getColor(string rgb, bool flag) {
  return flag ? "38;2;" + rgb : "48;2;" + rgb;
}
