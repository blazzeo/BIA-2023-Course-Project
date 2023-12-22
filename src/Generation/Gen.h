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

  ostringstream Head  {".586\n\
    .model flat, stdcall\n\
    includelib kernel32.lib\n\
    includelib libucrt.lib\n\
    includelib StaticLib.lib\n\
    convertToNum PROTO : byte\n\
    Strlen PROTO : byte\n\
    printInt PROTO : dword\n\
    printStr PROTO : byte\n\
    printBool PROTO : byte\n\
    ExitProcess PROTO : DWORD\n\n"};
  ostringstream Stack;
  ostringstream Const;
  ostringstream Data;
  ostringstream Code;

  AsmCode(string name) : fileName(name) {
    asmFile = new ofstream(name + ASM_EXT);
    Stack << "\n.STACK 4096\n";
    Data << "\n.DATA\n";
    Const << "\n.CONST\n";
    Code << "\n.CODE\n";
  } 
  ~AsmCode() {
    delete asmFile;
  }
};

  void GenerateScope(shared_ptr<AsmCode>, Sem::Scope&);
  void GenerateFile(shared_ptr<AsmCode>);
  Lexer::ValueType GenerateExpr(shared_ptr<AsmCode>, Sem::Scope&, size_t&, vector<Lexer::Token>);
  vector<vector<Lexer::Token>> parseIntoLines(Sem::Scope &);
  string LexemString(vector<Lexer::Token> &tokens);
  void WriteLiterals(shared_ptr<AsmCode>, Sem::Scope&);
  shared_ptr<AsmCode> CreateAsmFile(const std::string);
  void GenerateAsm(shared_ptr<AsmCode>, Sem::Scope&);
};
