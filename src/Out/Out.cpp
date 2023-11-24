#include "../Error/Error.h"
#include "../Lexer/newLexer.h"
#include "../Parm/Parm.h"
#include "../Out/Out.h"
#include "iostream"
#include <vector>

namespace Out {
OUT getOut(wchar_t* w_outfile) {
    char* filename = getCH(w_outfile); 
    OUT out;
    wcscpy(out.outfile, w_outfile);
    out.stream = new std::ofstream(filename);
    if (!out.stream && !out.stream->is_open()) {
        throw ERROR_THROW(112);
    }
    return out;

}
void WriteError(OUT out, Error::ERROR e) {
    const char* err_mes = e.error_line.c_str();
    if (out.stream && out.stream->is_open()) {
        *out.stream << "Ошибка " << e.id << ": " << e.message <<
            ", строка " << e.inext.line <<
            ", позиция " << e.inext.col << std::endl <<
            e.inext.line << '\t' << err_mes << std::endl << std::endl;
    } else {
        std::cout << "Ошибка " << e.id << ": " << e.message <<
            ", строка " << e.inext.line <<
            ", позиция " << e.inext.col << std::endl << 
            e.inext.line << '\t' << err_mes << std::endl << std::endl;
    }
}

void WriteOut(OUT out, Lexer::Table table) {
    const std::string tokenTypes = " ;{}()[]+*/-,=ittmlrfdpu";
    if (out.stream && out.stream->is_open()) {
        int lineNum = -1;
        for (auto token : table.tokens) {
            if (lineNum != token.lineNum)
                *out.stream << std::endl << ++lineNum << '\t';
            *out.stream << token.lexema;
        }
        *out.stream << std::endl;
    }
}

}

