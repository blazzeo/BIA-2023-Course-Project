#include "Gen.h"
#include <memory>
#include <stack>
#include <vector>

using namespace std;

#define asm *ASM->asmFile

namespace Gen {
shared_ptr<AsmCode> CreateAsmFile(const std::string name) {
  auto ASM = make_shared<AsmCode>(name);
  return ASM;
}

void GenerateAsm(shared_ptr<AsmCode> ASM, Sem::Scope &scope, Lexer::Table &table) {
  vector<vector<Lexer::Token>> codeLines = parseIntoLines(scope);
  if(scope.specs.name == "GLOBAL") { //   Generate GLOBAL Identifiers
    // for(auto ident : scope.Identifiers) {
    //   if (!ident->isFunc) {
    //     *ASM.asmFile << ident->name+":\n\t\t.";
    //     switch (ident->type) {
    //       case Lexer::i :
    //         *ASM.asmFile << "int\t" << get<int>(ident->value);
    //         break;
    //       case Lexer::str :
    //         *ASM.asmFile << "str\t" << get<string>(ident->value);
    //         break;
    //       case Lexer::bol :
    //         *ASM.asmFile << "bool\t" << get<bool>(ident->value);
    //         break;
    //       default:
    //         break;
    //     }
    //   }
    // }
  } else {
    WriteLiterals(ASM, scope);
    ASM->Code << scope.specs.name+"\tPROC\n";  //  Write Scope Name
    ASM->Code << "push\tEBP\n\
                  mov\tEBP, ESP\n\
                  sub\tESP, " << scope.offset_length << endl;
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
        ASM->Code << "mov\tdword ptr [EBP+" << tmpIdentifier->offset << "]\tEAX\n";
      }
      if(token.type == Lexer::ret) {
        GenerateExpr(ASM, scope, i+1);
      }
      if(token.type == Lexer::print) {
        switch(GenerateExpr(ASM, scope, i+1)) {
          case Lexer::i:
            ASM->Code << "call\tprintInt\n";
            break;
          case Lexer::str:
            ASM->Code << "call\tprintStr\n";
            break;
          case Lexer::bol:
            ASM->Code << "call\tprintBool\n";
            break;
          case Lexer::undef:
            ASM->Code << "mov\tEAX, 0\t\t;EXPR ERROR\n";
            break;
        }
        
        ASM->Code << "mov\tEAX, -11\n\
                      call GetStdHandle\n\n";
        ASM->Code << "push\t0\n";
        ASM->Code << "lea\tEDX, ";
      }
    }
  }

  if(scope.specs.name != "GLOBAL") {
    ASM->Code << "add\tESP,\t" << scope.offset_length << endl;
    ASM->Code << "pop\tEBP\n";
    ASM->Code << "ret\n";
    ASM->Code << scope.specs.name+"\tENDP\n";  //  End of Scope
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

Lexer::ValueType GenerateExpr(shared_ptr<AsmCode> ASM, Sem::Scope &scope, size_t id) {
  stack<Lexer::Token> stack;
  Lexer::ValueType valType = Lexer::undef;
  while(scope.innerCode[id].type != Lexer::semi) {
    switch (scope.innerCode[id].type) {
      case Lexer::liter : {
        ASM->Code << "push\t" << scope.specs.name << scope.innerCode[id].literID << endl;
        break;
      }
      case Lexer::identifier : {
        if (scope.innerCode[id].identifier->isFunc) {
          ASM->Code << "call\t" << scope.innerCode[id].identifier->name << endl;
        } else {
          ASM->Code << "push\t" << "dword ptr[EBP+" << scope.innerCode[id].identifier->offset << "]\n";
        }
        break;
      }
    }
  }
  return valType;
}

string LexemString(vector<Lexer::Token> &tokens) {
  string result{};
  for (auto token : tokens) {
    result += token.lexema;
  }
  return result;
}

void WriteLiterals(shared_ptr<AsmCode> ASM, Sem::Scope &scope) {
  short literID = 0;
  for(auto token : scope.innerCode) {
    if (token.type == Lexer::liter) {
      token.literID = literID;
      ASM->Const << scope.specs.name << literID++;
      switch (token.value.second) {
        case Lexer::i : {
          ASM->Const << "\tDWORD\t" << token.value.first << endl;
          break;
        }
        case Lexer::bol : {
          ASM->Const << "\tBYTE\t" << token.value.first << endl;
          break;
        }
        case Lexer::str : {
          ASM->Const << "\tBYTE\t\"" << token.value.first << "\"" << endl;
          break;
        }
        case Lexer::undef :
          break;
      }
    }
  }
}

}
