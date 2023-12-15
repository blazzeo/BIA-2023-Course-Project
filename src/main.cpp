#include "Syntacsis/GRB.h"
#include "Error/Error.h"
#include "Log/Log.h"
#include "Out/Out.h"
#include "Lexer/newLexer.h"
#include "Parm/Parm.h"
#include "In/In.h"
#include "Generation/Gen.h"
#include "Semantics/Sem.h"
#include "Syntacsis/MFST.h"

#include <iostream>

int main(int argc, char* argv[]) {
    Out::OUT out;
    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        out = Out::getOut(parm.out);
        Log::LOG log = Log::getlog(parm.log);
        Log::WriteLog(log);
        Log::WriteParm(log, parm);
        In::IN in = In::getin(parm.in);
    // LEXER
        Lexer::Table table = Lexer::tokenize(in);
        Lexer::generateLog(table);
    // SYNTACSIS
        MFST_TRACE_START;
        MFST::Mfst mfst(table, GRB::getGreibach());
        mfst.start();
        mfst.savededucation();
        std::cout << std::endl << "\t\tRules\n";
        mfst.printrules();
    // // SEMANTICS
        int i = 0;
        Sem::Scope structure = Sem::scopenize(&table, i);
        Sem::PrintTable(structure);
    // // GENERATION
        Gen::GenerateAsm(structure, table);
        Out::WriteOut(out, table);
        Log::WriteIn(log, in);
        Log::Close(log);
    }
    catch (Error::ERROR e) {
        // if (out.stream && out.stream->is_open()) {
        //     Out::WriteError(out, e);
        //     return 1;
        // } else {
            std::cout << "Error " << e.id << ": " << e.message << '\n' << std::endl;
            std::cout << "line " << e.inext.line+1
                << "\tposition " << e.inext.col << "\n\n";
            return 1;
        // }
    }
    return 0;
}
