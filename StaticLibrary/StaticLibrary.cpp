#include "iostream"
#include <cctype>
#include <cstring>

extern "C" {
int __stdcall Strlen(const char* str) {
  return strlen(str);
}

int __stdcall convertToNum(const char* str) {
  int num = 0;
  bool isNegative = false;
  size_t i = 0;

  if (str[0] == '-') {
    isNegative = true;
    i++;
  }

  while (i < strlen(str)) {
    if (isdigit(str[i])) {
      num = num * 10 + (str[i] - '0');
      i++;
    } else {
      std::cout << "Ошибка преобразования строки в число!" << std::endl;
      return 0;
    }
  }
  return isNegative? -num : num;
}

void __stdcall printInt(int x) {
  std::cout << x << std::endl;
}

void __stdcall printStr(const char* str) {
  if (str == nullptr) {
    std::cout << "NULL" << std::endl;
    return;
  }
  std::cout << str << std::endl;
  return;
}

void __stdcall printBool(bool x) {
  std::cout << x << std::endl;
  return;
}
}
