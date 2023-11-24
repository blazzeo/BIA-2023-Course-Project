#pragma once
#include "../Parm/Parm.h"
#include "../WCHAR/WCHAR.h"
#include "../Error/Error.h"
#include "../Lexer/newLexer.h"
#include <fstream>

namespace Out {
struct OUT {
    wchar_t outfile[PARM_MAX_SIZE];
    std::ofstream* stream;
};

OUT getOut(wchar_t outfile[]);
void WriteError(OUT out, Error::ERROR err);
void WriteOut(OUT out, Lexer::Table);
};
