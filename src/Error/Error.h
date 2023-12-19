#pragma once
#include <string>
#include "../Lexer/newLexer.h"
#define ERROR_THROW(id) Error::geterror(id);
#define ERROR_THROW_LC(id, l, c) Error::geterror_lc(id, l, c);
#define ERROR_THROW_POS(id, p) Error::geterror_pos(id, p);
#define ERROR_THROW_LEXER(id, l, c, m) Error::geterror_word(id, l, c, m);
#define ERROR_THROW_WORD(id, word, pos) Error::geterror_word(id, word, pos);
#define ERROR_ENTRY(id, m) {id, m, {-1, -1}}
#define ERROR_MAXSIZE_MESSAGE 200
#define ERROR_ENTRY_NODEF(id)   ERROR_ENTRY(-id,"Unknown Error")
#define ERROR_MAX_ENTRY 1000

namespace Error {
  struct ERROR {
    int id;
    std::string message;
    std::string error_line;
    struct IN {
      short line;
      short col;
    } position;
    ERROR(int id, std::string msg, short line=-1, short col=-1) :
      id{id}, message(msg), position({line, col}) {}
  };

ERROR geterror(int id);
ERROR geterror_lc(int id, int line, int col);
ERROR geterror_pos(int id, Lexer::Position pos);
ERROR geterror_word(int id, int line, int col, std::string word);
ERROR geterror_word(int id, std::string, Lexer::Position pos);
void printErorr(ERROR&);
};
