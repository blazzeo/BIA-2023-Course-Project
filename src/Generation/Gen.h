#pragma once
#include "../Lexer/newLexer.h"
#include "../Semantics/Sem.h"
#include <fstream>
#include <vector>

using namespace std;

namespace Gen {
  struct AsmCode {
		string Head = ".586P\n.MODEL FLAT, STDCALL\nincludelib kernel32.lib\nincludelib libucrt.lib\nincludelib ..\\Debug\\StaticLibrary.lib\nEXTRN convertToNum: PROC\nEXTRN Strlen: PROC\nExitProcess PROTO : DWORD\n\n";
		string Stack = ".STACK 4096\n";
    string Const = ".CONST\n\n";
		string Data = ".DATA\n";
		string Code = ".CODE\n\n";

    vector<AsmCode> nextASMs;
    string fileName;
};

  void GetHead(Sem::Scope&, Lexer::Table&, AsmCode&);
  void GetData(Sem::Scope&, Lexer::Table&, AsmCode&);
  void GetCode(Sem::Scope&, Lexer::Table&, AsmCode&);
  AsmCode GenerateAsm(Sem::Scope &, Lexer::Table&);
};
