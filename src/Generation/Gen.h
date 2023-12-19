#pragma once
#include "../Lexer/newLexer.h"
#include "../Semantics/Sem.h"
#include <fstream>
#include <vector>

#define ASM_EXT ".asm"

using namespace std;

namespace Gen {
struct AsmCode {
  string fileName;
  ofstream* asmFile = nullptr;

  string Head = ".586P\n\
    .MODEL FLAT, STDCALL\n\
    includelib kernel32.lib\n\
    includelib libucrt.lib\n\
    includelib ..\\Debug\
    StaticLibrary.lib\n\
    EXTRN convertToNum: PROC\n\
    EXTRN Strlen: PROC\n\
    ExitProcess PROTO : DWORD\n\n";
  string Stack = ".STACK 4096\n";
  string Const = ".CONST\n\n";
  string Data = ".DATA\n";
  string Code = ".CODE\n\n";

  AsmCode(string name) : fileName(name) {
    asmFile = new ofstream(name + ASM_EXT);
  } 
  ~AsmCode() {
    delete asmFile;
  }
};

  
  // void GetHead(Sem::Scope&, Lexer::Table&, AsmCode&);
  // void GetData(Sem::Scope&, Lexer::Table&, AsmCode&);
  // void GetCode(Sem::Scope&, Lexer::Table&, AsmCode&);
  void GenerateAsm(Sem::Scope &, Lexer::Table&);
  void GenerateExpr(AsmCode&, Sem::Scope&, size_t);
  vector<vector<Lexer::Token>> parseIntoLines(Sem::Scope &);
  string LexemString(vector<Lexer::Token> &tokens);
};
