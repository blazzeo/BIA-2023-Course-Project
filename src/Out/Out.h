#pragma once
#include "../Parm/Parm.h"
#include "../WCHAR/WCHAR.h"
#include "../Error/Error.h"
#include "../Lexer/newLexer.h"
#include <fstream>

namespace Out {
struct OUT {
    char outfile[PARM_MAX_SIZE];
    std::ofstream* stream;
};

OUT getOut(char outfile[]);
void WriteError(OUT out, Error::ERROR err);
void WriteOut(OUT out, Lexer::Table);
};
