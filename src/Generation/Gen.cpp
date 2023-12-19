#include "Gen.h"
#include <memory>
#include <stack>
#include <vector>

using namespace std;

namespace Gen {
AsmCode CreateAsmFile(std::string name) {
  AsmCode ASM(name);
  *ASM.asmFile << ASM.Head << ASM.Stack << ASM.Const << ASM.Code;
  return ASM;
}

void GenerateAsm(AsmCode& ASM, Sem::Scope &scope, Lexer::Table &table) {
  *ASM.asmFile << scope.specs.name+":" << endl;  //  Write Scope Name
  vector<vector<Lexer::Token>> codeLines = parseIntoLines(scope);
  if(scope.specs.name == "GLOBAL") {
    for(auto ident : scope.Identifiers) {
      *ASM.asmFile << ident->name+":" << endl << "\t\t.";
      switch (ident->type) {
        case Lexer::i :
        *ASM.asmFile << "int\t" << ;
        
      }
    }
  }

  for(auto line : codeLines) { //  Generate this Scope
    shared_ptr<Lexer::Identifier> tmpIdentifier = nullptr;
    string LEXSTR = LexemString(line);
    for(size_t i = 0; i < line.size(); i++) {
      auto token = line[i];
      if(token.type == Lexer::identifier) {
        tmpIdentifier = token.identifier;
      }
      if(token.type == Lexer::equals) {
        GenerateExpr(ASM, scope, i+1);
        *ASM.asmFile << "mov\t" << "dword ptr [EBP+" << tmpIdentifier->offset << "]\tEAX" << endl;
      }
      if(token.type == Lexer::ret) {
        GenerateExpr(ASM, scope, i+1);
        *ASM.asmFile << "add\tESP,\t" << scope.offset_length << endl;
        *ASM.asmFile << "pop\tEBP" << endl;
        *ASM.asmFile << "ret" << endl;
      }
    }
  }

  for(auto nScope : scope.nextScopes) { //  Generate Next Scopes
    GenerateAsm(ASM, nScope, table);
  }
}

vector<vector<Lexer::Token>> parseIntoLines(Sem::Scope &scope) {
  vector<vector<Lexer::Token>> Lines;
  vector<Lexer::Token> Line;
  for (auto token : scope.innerCode) {
    if (token.type == Lexer::semi) {
      Lines.push_back(Line);
      Line.clear();
    }
    Line.push_back(token);
  }
  return Lines;
}

void GenerateExpr(AsmCode &ASM, Sem::Scope &scope, size_t id) {
  stack<Lexer::Token> stack;
  while(scope.innerCode[id].type != Lexer::semi) {
    switch (scope.innerCode[id].type) {
      case Lexer::liter : {
      }
      case Lexer::identifier : {
        if (scope.innerCode[id].identifier->isFunc) {
          *ASM.asmFile << "call\t" << scope.innerCode[id].identifier->name << endl;
        }
      }
    }
  }
}

string LexemString(vector<Lexer::Token> &tokens) {
  string result{};
  for (auto token : tokens) {
    result += token.lexema;
  }
  return result;
}
}
