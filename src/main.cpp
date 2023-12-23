//  BIA-2023 Language
#include "Error/Error.h"
#include "Parm/Parm.h"
#include "Log/Log.h"
#include "In/In.h"
#include "Out/Out.h"
#include "Lexer/newLexer.h"
#include "Syntacsis/GRB.h"
#include "Syntacsis/MFST.h"
#include "Semantics/Sem.h"
#include "Generation/Gen.h"
#include <memory>

int main(int argc, char* argv[]) {
    Out::OUT out;
    Log::LOG log;
    try {
        Parm::PARM parms = Parm::getparm(argc, argv);
        out = Out::getOut(parms.out);
        log = Log::getlog(parms.log);
        Log::WriteLog(log);
        Log::WriteParm(log, parms);
        In::IN in = In::getin(parms.in);
    // LEXER
        Lexer::Table table = Lexer::tokenize(in);
        Lexer::generateLog(table);
    // PARSER
        MFST_TRACE_START;
        MFST::Mfst mfst(table, GRB::getGreibach());
        mfst.start();
        mfst.savededucation();
        mfst.printrules();
    // SEMANTICS
        int i = 0;
        Sem::Scope* structure = Sem::scopenize(&table, i);
        Sem::MainCheck(*structure);
        Sem::PrintTable(*structure);
    // GENERATION
        auto ASM = Gen::CreateAsmFile("BIA-2023");
        Gen::GenerateAsm(ASM, *structure);
        Gen::GenerateFile(ASM);
        Out::WriteOut(out, table);
        Log::WriteIn(log, in);
        Log::Close(log);
    }
    catch (Error::ERROR e) {
        // if (out.stream && out.stream->is_open()) {
        //     Out::WriteError(out, e);
        //     return 1;
        // } else {
            Error::printErorr(e);
            return 1;
        // }
    }
    return 0;
}
