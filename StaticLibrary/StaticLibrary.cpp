#include "iostream"
#include <cctype>
#include <cstring>

extern "C" {
int Strlen(char* str) {
  return strlen(str);
}

int convertToNum(char* str) {
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

void printInt(int x) {
  std::cout << x << std::endl;
}

void printStr(char* str) {
  std::cout << str << std::endl;
}

void printBool(bool x) {
  std::cout << x << std::endl;
}
}
