#include "../Error/Error.h"
#include "../Lexer/newLexer.h"
#include "../Parm/Parm.h"
#include "../Out/Out.h"
#include "iostream"

namespace Out {
OUT getOut(char* outfile) {
  char* filename = outfile; 
  OUT out;
  strcpy(out.outfile, outfile);
  out.stream = new std::ofstream(filename);
  if (!out.stream && !out.stream->is_open()) {
    throw ERROR_THROW(112);
  }
  return out;

}
void WriteError(OUT out, Error::ERROR e) {
  const char* err_mes = e.error_line.c_str();
  if (out.stream && out.stream->is_open()) {
    *out.stream << "Error " << e.id << ": " << e.message <<
      ", line " << e.position.line <<
      ", position " << e.position.col << std::endl <<
      e.position.line << '\t' << err_mes << std::endl << std::endl;
  } else {
    std::cout << "Error " << e.id << ": " << e.message <<
      ", line " << e.position.line <<
      ", position " << e.position.col << std::endl << 
      e.position.line << '\t' << err_mes << std::endl << std::endl;
  }
}

void WriteOut(OUT out, Lexer::Table table) {
  if (out.stream && out.stream->is_open()) {
    int lineNum = -1;
    for (auto token : table.tokens) {
      if (lineNum != token.position.line)
        *out.stream << std::endl << ++lineNum << '\t';
      *out.stream << token.lexema;
    }
    *out.stream << std::endl;
  }
}
}
