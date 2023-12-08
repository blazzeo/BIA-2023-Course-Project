#include "Gen.h"
#include <fstream>
#include <string>

namespace Gen {
void GetHead(Sem::Scope &structure, Lexer::Table &table, AsmCode &ASM) {
  for(auto nextASM : ASM.nextASMs) {
    ASM.Head += "\ninclude ";
    ASM.Head += nextASM.fileName;
  }
}

void GetData(Sem::Scope &structure, Lexer::Table &table, AsmCode &ASM) {
  ASM.Data += "\n\tbuffer BYTE 256 dup(0)";

  for (auto ident : structure.Identifiers)
  {
    ASM.Data += "\n\t";
    ASM.Data += ident.name;
    if (ident.type == Lexer::bol)
      ASM.Data += " DD 0";
    else if (ident.type == Lexer::i)
      ASM.Data += " DD 0";
    else if (ident.type == Lexer::str)
      ASM.Data += " DD ?";
  }
  for (auto parm : structure.parms)
  {
    ASM.Data += "\n\t";
    ASM.Data += parm.name;
    if (parm.type == Lexer::bol)
      ASM.Data += " DD 0";
    else if (parm.type == Lexer::i)
      ASM.Data += " DD 0";
    else if (parm.type == Lexer::str)
      ASM.Data += " DD ?";
  }
  ASM.Data += "\n\n";
}

void GetCode(Sem::Scope &structure, Lexer::Table &table, AsmCode &ASM) {
  ASM.Code += "mov [RSP + 8], RCX\
push R15\
push R14\
push R13\
sub RSP, fixed-allocation-size\
lea R13, 128[RSP]";



  ASM.Code += "add RSP, fixed-allocation-size\
pop R13\
pop R14\
pop R15\
ret";
}

AsmCode GenerateAsm(Sem::Scope &scope, Lexer::Table &table) {
  static short undefNum = 0;
  AsmCode ASM;
  for(auto nextScope : scope.nextScopes) {
    ASM.nextASMs.push_back(GenerateAsm(nextScope, table));
  }
  GetHead(scope, table, ASM);
  GetData(scope, table, ASM);
  GetCode(scope, table, ASM);
  ASM.fileName = scope.specs.name;
  if(scope.specs.returnType == Lexer::undef)
    ASM.fileName += to_string(undefNum++);
  ASM.fileName += ".asm";
  ofstream file(ASM.fileName);
  if (file.is_open()) {
    file << ASM.Head;
    file << ASM.Stack;
    file << ASM.Const;
    file << ASM.Data;
    file << ASM.Code;
  }
  return ASM;
}
}
