#include "Error.h"
#include "iostream"

namespace Error {
  ERROR errors[ERROR_MAX_ENTRY] = {
  // 0-99 Системные
    ERROR_ENTRY(0, "Unacceptable error code"),
    ERROR_ENTRY(1, "System failure"),
  //  100-199 Ошибки праметров
    ERROR_ENTRY(100, "-in parm missing"),
    ERROR_ENTRY(104, "Input parameter length exceeded"),
    ERROR_ENTRY(110, "Error opening source code file (-in)"),
    ERROR_ENTRY(111, "Invalid character in source file (-in)"),
    ERROR_ENTRY(112, "Error creating log file (-log)"),
  //  200-299 Ошибки лексического анализа
    ERROR_ENTRY(201, "Chain wasn't recognized"),
    ERROR_ENTRY(202, "Error creating IT file"),
    ERROR_ENTRY(203, "Error creating LT file"),
    ERROR_ENTRY(204, "Error getting Lexical table row (no element)"),
    ERROR_ENTRY(205, "Error getting Identifier table row (no element)"),
  //  400-499 Ошибки семантичского анализа
    ERROR_ENTRY(400, "Cannot apply operator to given operand type"), 
    ERROR_ENTRY(401, "Return type does not match function type"), 
    ERROR_ENTRY(402, "Undeclared variable was used"), 
    ERROR_ENTRY(403, "Re-announcement of name"), 
    ERROR_ENTRY(404, "The function must return a value"), 
    ERROR_ENTRY(405, "Error in conditional statement"), 
    ERROR_ENTRY(406, "Mismatch between actual and formal parameters of a function"), 
    ERROR_ENTRY(407, "Type mismatch in expression"), 
  //  600-699 Ошибки синтаксического анализа
    ERROR_ENTRY(600, "Incorrect program structure"),
    ERROR_ENTRY(601, "Error operator"),
    ERROR_ENTRY(602, "Error in Expression"),
    ERROR_ENTRY(603, "Error in Function Statements"),
    ERROR_ENTRY(604, "Error in the parameters of the called Function"),
    ERROR_ENTRY(605, "The value of this operator can only be a variable or literal"),
    ERROR_ENTRY(606, "Error in If-statement"),
    ERROR_ENTRY(607, "M Error"),
    ERROR_ENTRY(608, "Error in For-statement"), 
};

ERROR geterror(int id) {
  return id > 0 && id < ERROR_MAX_ENTRY ? errors[id] : errors[0];
}

ERROR geterrorin(int id, int line = -1, int col = -1) {
  ERROR err = geterror(id);
  err.inext.line = (short)line;
  err.inext.col = (short)col;
  return err;
}

ERROR geterrorlexer(int id, int line, std::string error_word) {
    ERROR err = geterrorin(id, line);
    std::cout << "Word : " << error_word << std::endl;
    err.error_line = error_word;
    return err;
}

};
