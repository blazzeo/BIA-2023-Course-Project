#include "Error.h"
#include "../Lexer/newLexer.h"
#include "iostream"
#include <vector>

namespace Error {
std::vector<ERROR> errors = {
  // 0-99 Системные
    ERROR(0, "System: Unacceptable error code"),
    ERROR(1, "System: System failure"),
  //  100-199 Ошибки праметров
    ERROR(100, "Parm :-in parm missing"),
    ERROR(104, "Parm :Input parameter length exceeded"),
    ERROR(110, "Parm :Error opening source code file (-in)"),
    ERROR(111, "Parm :Invalid character in source file (-in)"),
    ERROR(112, "Parm :Error creating log file (-log)"),
  //  200-299 Ошибки лексического анализа
    ERROR(201, "Lexer: Chain wasn't recognized"),
    ERROR(202, "Lexer: Error creating IT file"),
    ERROR(203, "Lexer: Error creating LT file"),
    ERROR(204, "Lexer: Error getting Lexical table row (no element)"),
    ERROR(205, "Lexer: Error getting Identifier table row (no element)"),
  //  400-499 Ошибки семантичского анализа
    ERROR(401, "Semantics: Return type does not match function type"), 
    ERROR(402, "Semantics: Undeclared variable was used"), 
    ERROR(403, "Semantics: Re-announcement of name"), 
    ERROR(404, "Semantics: The function must return a value"), 
    ERROR(405, "Semantics: Mismatch between actual and formal parameters of a function"), 
    ERROR(406, "Semantics: Type mismatch in expression"), 
    ERROR(407, "Semantics: Main missing"), 
    ERROR(408, "Semantics: Error in If-statement"),
  //  600-699 Ошибки синтаксического анализа
    ERROR(600, "Parser: Incorrect program structure"),
    ERROR(601, "Parser: Error operator"),
    ERROR(602, "Parser: Error in Expression"),
    ERROR(603, "Parser: Error in Function Statements"),
    ERROR(604, "Parser: Error in the parameters of the called Function"),
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
