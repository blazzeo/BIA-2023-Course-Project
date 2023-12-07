#include "string"
#include "iostream"
#include <cctype>

extern "C" {
  int Strlen(std::string str) {
    return str.length();
  }

int convertToNum(const std::string& str) {
  int num = 0;
  bool isNegative = false;
  size_t i = 0;

  if (str[0] == '-') {
    isNegative = true;
    i++;
  }

  while (i < str.length()) {
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
}
