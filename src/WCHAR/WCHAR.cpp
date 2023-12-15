#include "../Error/Error.h"

wchar_t* getWC(const char* src) {
  const size_t length = strlen(src) + 1;
  wchar_t* wc = new wchar_t[length];
  if (mbstowcs(wc, src, length) == (size_t)-1) {
    delete[] wc;
    throw ERROR_THROW(0);
  }
  return wc;
}

char* getCH(const wchar_t* src) {
  const size_t length = wcslen(src) + 1;
  char* ch = new char[length*2];
  if (wcstombs(ch, src, length*2) == (size_t)-1) {
    delete[] ch;
    throw ERROR_THROW(0);
  }
  return ch;
}
