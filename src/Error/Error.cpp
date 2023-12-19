#include "Error.h"
#include "../Lexer/newLexer.h"
#include "iostream"
#include <vector>

namespace Error {
std::vector<ERROR> errors = {
  // 0-99 Системные
    ERROR(0, "Unacceptable error code"),
    ERROR(1, "System failure"),
  //  100-199 Ошибки праметров
    ERROR(100, "-in parm missing"),
    ERROR(104, "Input parameter length exceeded"),
    ERROR(110, "Error opening source code file (-in)"),
    ERROR(111, "Invalid character in source file (-in)"),
    ERROR(112, "Error creating log file (-log)"),
  //  200-299 Ошибки лексического анализа
    ERROR(201, "Chain wasn't recognized"),
    ERROR(202, "Error creating IT file"),
    ERROR(203, "Error creating LT file"),
    ERROR(204, "Error getting Lexical table row (no element)"),
    ERROR(205, "Error getting Identifier table row (no element)"),
  //  400-499 Ошибки семантичского анализа
    ERROR(400, "Cannot apply operator to given operand type"), 
    ERROR(401, "Return type does not match function type"), 
    ERROR(402, "Undeclared variable was used"), 
    ERROR(403, "Re-announcement of name"), 
    ERROR(404, "The function must return a value"), 
    ERROR(405, "Error in conditional statement"), 
    ERROR(406, "Mismatch between actual and formal parameters of a function"), 
    ERROR(407, "Type mismatch in expression"), 
  //  600-699 Ошибки синтаксического анализа
    ERROR(600, "Incorrect program structure"),
    ERROR(601, "Error operator"),
    ERROR(602, "Error in Expression"),
    ERROR(603, "Error in Function Statements"),
    ERROR(604, "Error in the parameters of the called Function"),
    ERROR(605, "The value of this operator can only be a variable or literal"),
    ERROR(606, "Error in If-statement"),
    ERROR(607, "M Error"),
    ERROR(608, "Error in For-statement"), 
};

ERROR geterror(int id) {
  for(auto error : errors) {
    if (error.id == id)
      return error;
  }
  return errors[0];
}

ERROR geterror_lc(int id, int line = -1, int col = -1) {
  ERROR err = geterror(id);
  err.position.line = (short)line;
  err.position.col = (short)col;
  return err;
}

ERROR geterror_pos(int id, Lexer::Position pos) {
  ERROR err = geterror(id);
  err.position.line = (short)pos.line;
  err.position.col = (short)pos.col;
  return err;
}

ERROR geterror_word(int id, int line, int col, std::string error_word) {
  ERROR err = geterror_lc(id, line, col);
  err.error_line = error_word;
  std::cout << "Word : " << error_word << std::endl;
  return err;
}

ERROR geterror_word(int id, std::string error_word, Lexer::Position pos) {
  ERROR err = geterror_pos(id, pos);
  err.error_line = error_word;
  std::cout << "Word : " << error_word << std::endl;
  return err;
}

void printErorr(ERROR &e) {
  std::cout << "Error " << e.id << ": " << e.message << '\n' << std::endl;
  if(e.position.line != 0) {
    std::cout << "line " << e.position.line
      << "\tposition " << e.position.col << "\n";
    if (!e.error_line.empty()) std::cout << "Word: " << e.error_line << std::endl;
  }
}
};
