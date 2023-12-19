#include "In.h"
#include <fstream>
#include "../Error/Error.h"
#include <iostream>

namespace In {
IN getin(char infile[]) {
    char* filename = infile;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw ERROR_THROW(110);
    }
    IN in = { 0, 0, 0, nullptr, IN_USER_CODE_TABLE };

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    in.text = new unsigned char[size];

    in.size = size;

    unsigned char* pText = in.text;

    for (size_t col=0, line=0, i=0; i < size; ++col, ++i) {
        unsigned char ch = file.get();
        if (ch == '\n') {
            ++line;
            in.lines++;
            col--;
        }

       switch(in.code[(int)ch]) {
           case IN::F :
                std::cout << (int)ch << std::endl;
               setlocale(LC_ALL, "en_US.UTF-8");
               file.close();
               throw ERROR_THROW_LC(111, line, col);
            case IN::T :
               *pText = ch, pText++;
               break;
           case IN::I :
               in.ignor++, in.size--; continue;
           default:
               if (0 <= in.code[(int)ch] && 256 > in.code[(int)ch])
                   *pText = in.code[(int)ch], pText++;
       }
    }

    *pText = '\0';
    file.close();
    return in;
}
};
