#pragma once
#include "../Lexer/newLexer.h"
#include "../Semantics/Sem.h"
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>

#define ASM_EXT ".asm"

using namespace std;

namespace Gen {
struct AsmCode {
  string fileName;
  ofstream* asmFile = nullptr;

  stringstream Head  {".586P\n\
    .MODEL FLAT, STDCALL\n\
    includelib kernel32.lib\n\
    includelib libucrt.lib\n\
    StaticLibrary.lib\n\
    EXTRN convertToNum: PROC\n\
    EXTRN Strlen: PROC\n\
    EXTRN printInt: PROC\n\
    EXTRN printStr: PROC\n\
    EXTRN printBool: PROC\n\
    ExitProcess PROTO : DWORD\n\n"};
  stringstream Stack  {".STACK 4096\n"};
  stringstream Const  {".CONST\n\n"};
  stringstream Data  {".DATA\n"};
  stringstream Code  {".CODE\n\n"};

  AsmCode(string name) : fileName(name) {
    asmFile = new ofstream(name + ASM_EXT);
  } 
  ~AsmCode() {
    delete asmFile;
  }
};

  void GenerateAsm(shared_ptr<AsmCode>, Sem::Scope&);
  Lexer::ValueType GenerateExpr(shared_ptr<AsmCode>, Sem::Scope&, size_t);
  vector<vector<Lexer::Token>> parseIntoLines(Sem::Scope &);
  string LexemString(vector<Lexer::Token> &tokens);
  void WriteLiterals(shared_ptr<AsmCode>, Sem::Scope&);
  shared_ptr<AsmCode> CreateAsmFile(const std::string);
};
