#include "Gen.h"
#include <memory>
#include "../Error/Error.h"
#include <ostream>
#include <stack>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace Gen {

ostream& operator<<(ostream& out, shared_ptr<Lexer::Identifier> token) {
  if (token->offset < 0)
    return out << token->offset;
  return out << '+' << token->offset;
}

shared_ptr<AsmCode> CreateAsmFile(const std::string name) {
  auto ASM = make_shared<AsmCode>(name);
  return ASM;
}

void GenerateAsm(shared_ptr<AsmCode> ASM, Sem::Scope &scope) {
  WriteLiterals(ASM, scope);
  for(auto nScope : scope.nextScopes) {         //  Generate Next Scopes
    ASM->Code << nScope->specs.name+"\tPROC\n";  //  Write Scope Name
    ASM->Code << "\tpush\tebp\n";
    ASM->Code << "\tmov\tebp, esp\n";
    ASM->Code << "\tsub\tesp, " << nScope->offset_length << endl;
    GenerateScope(ASM, *nScope);
    ASM->Code << "\tadd\tesp,\t" << nScope->offset_length << endl;
    ASM->Code << "\tpop\tebp\n";
    if(nScope->specs.name == "main") {
      ASM->Code << "\tpush\t0\n";
      ASM->Code << "\tcall\tExitProcess\n";
    } else {
      ASM->Code << "\tret ";
        if(nScope->parms.size())
          ASM->Code << nScope->parms[0]->offset - 4;
        ASM->Code << endl;
    }
    ASM->Code << nScope->specs.name+"\tENDP\n\n";  //  End of Scope
    if(nScope->specs.name == "main")
      ASM->Code << "end main";
  }
}

void GenerateScope(shared_ptr<AsmCode> ASM, Sem::Scope &scope) {
  vector<vector<Lexer::Token>> codeLines = parseIntoLines(scope);

  static stack<string> if_marks;
  const string if_marks_template = "skip_if_";
  static stack<string> for_marks;
  const string for_marks_template = "start_for_";
  static int if_mark_count = 0;
  static int for_mark_count = 0;
  int nextScope = 0;

  for(auto line : codeLines) { //  Generate this Scope
    shared_ptr<Lexer::Identifier> tmpIdentifier = nullptr;
    string LEXSTR = LexemString(line);
    for(size_t i = 0; i < line.size(); i++) {
      auto token = line[i];
      if(token.type == Lexer::identifier) { //  Identifier
        if(token.identifier->type == Lexer::undef) {
          auto result = checkIdentifier(&scope, token.identifier);
          tmpIdentifier = result;
        } else tmpIdentifier = token.identifier;
      }
      if(token.type == Lexer::open_app_brackets) { //  { Gen Scope 
        GenerateScope(ASM, *scope.nextScopes[nextScope++]);
      }
      if(token.type == Lexer::equals) { //  Equals
        ++i;
        GenerateExpr(ASM, scope, i, line);
          // if (tmpIdentifier->type == Lexer::bol)
          //   ASM->Code << "\tmov\tbyte ptr [ebp" << tmpIdentifier << "], eax\t; " << tmpIdentifier->name << "\n";
          // else 
            ASM->Code << "\tpop\teax\n";
            ASM->Code << "\tmov\tdword ptr [ebp" << tmpIdentifier << "], eax\t; " << tmpIdentifier->name << "\n";
      }
      if(token.type == Lexer::ret) { //   Return
        ++i;
        GenerateExpr(ASM, scope, i, line);
        ASM->Code << "\tpop\teax\n";
      }
      if(token.type == Lexer::print) { //   Print
        ++i;
        switch(GenerateExpr(ASM, scope, i, line)) {
          case Lexer::i:
            ASM->Code << "\tcall\tprintInt\n";
            break;
          case Lexer::str:
            ASM->Code << "\tcall\tprintStr\n";
            break;
          case Lexer::bol:
            ASM->Code << "\tcall\tprintBool\n";
            break;
          case Lexer::undef:
            ASM->Code << "\tmov\teax, 0\t\t;EXPR ERROR\n";
            break;
        }
      }
      // if(token.type == Lexer::loop) {
      //   ASM->Code << "; FOR\n";
      //   i += 3;
      //   auto declId = line[i];
      //   i += 6;
      //   auto cmpId = line[i];
      //   i += 4;
      //   auto actId = line[i];
      //   for_marks.push(for_marks_template + to_string(for_mark_count++));
      //
      //   ASM->Code << for_marks.top() << '\n';
      //   GenerateScope(ASM, scope.nextScopes[nextScope++]);
      //   ASM->Code << ;
      // }
      if(token.type == Lexer::condition) { //   IF
        ASM->Code << "; IF\n";
        i += 2;
        auto lhs = line[i];
        if (lhs.identifier->type == Lexer::undef) {
          auto result = checkIdentifier(&scope, lhs.identifier);
          lhs.identifier = result;
        }
        i++;

        if_marks.push(if_marks_template + to_string(if_mark_count++));

        if (line[i].type == Lexer::close_parm_brackets) {
          ASM->Code << "\tmov";
          ASM->Code << "\teax, dword ptr [ebp" << lhs.identifier << "]\t; " << lhs.identifier->name << "\n";
          ASM->Code << "\ttest\teax, eax\n";
          ASM->Code << "\tjz\t" << if_marks.top() << "\n";
          GenerateScope(ASM, *scope.nextScopes[nextScope++]);
          ASM->Code << if_marks.top() << ":\n";
          if_marks.pop();
          break;
        }

        auto op = line[i];
        auto rhs = line[++i];
        i++;

        Lexer::ValueType type1;
        Lexer::ValueType type2;

        ASM->Code << "\tpush\t";
        if (lhs.type == Lexer::liter){ 
          ASM->Code << "l" << to_string(lhs.literID) << "\n";
          type1 = lhs.value.second;
        } else if (lhs.type == Lexer::identifier) {
          ASM->Code << "dword ptr [ebp" << lhs.identifier << "] ;\t" << lhs.identifier->name << lhs.identifier->type << "\n";
          type1 = lhs.identifier->type;
        }

        ASM->Code << "\tpush\t";
        if (rhs.type == Lexer::liter) {
          ASM->Code << "l" << to_string(rhs.literID) << "\n";
          type2 = rhs.value.second;
        } else if (rhs.type == Lexer::identifier) {
          if (rhs.identifier->type == Lexer::undef) {
            auto result = checkIdentifier(&scope, rhs.identifier);
            rhs.identifier = result;
          }
          ASM->Code << "dword ptr [ebp" << rhs.identifier << "] ;\t" << rhs.identifier->name << rhs.identifier->type << "\n";
          type2 = lhs.identifier->type;
        }

        if (type1 != type2)
          throw ERROR_THROW_POS(408, lhs.position);

        ASM->Code << "\tpop\tebx\n";
        ASM->Code << "\tpop\teax\n";

        switch (op.type) {
          case Lexer::less:
            ASM->Code << "\tcmp\teax, ebx\n";
            ASM->Code << "\tjge\t" << if_marks.top() << endl;
            break;
          case Lexer::greater :
            ASM->Code << "\tcmp\teax, ebx\n";
            ASM->Code << "\tjle\t" << if_marks.top() << endl;
            break;
          case Lexer::nequal :
            ASM->Code << "\tcmp\teax, ebx\n";
            ASM->Code << "\tje\t" << if_marks.top() << endl;
            break;
          case Lexer::equal :
            ASM->Code << "\tcmp\teax, ebx\n";
            ASM->Code << "\tjne\t" << if_marks.top() << endl;
            break;
        }
        GenerateScope(ASM, *scope.nextScopes[nextScope++]);
        ASM->Code << if_marks.top() << ":\n";
        if_marks.pop();
        break;
      }
    }
  }
  return;
}

vector<vector<Lexer::Token>> parseIntoLines(Sem::Scope &scope) {
  vector<vector<Lexer::Token>> Lines;
  vector<Lexer::Token> Line;
  for (auto token : scope.innerCode) {
    Line.push_back(token);
    if (token.type == Lexer::semi) {
      Lines.push_back(Line);
      Line.clear();
    }
  }
  return Lines;
}

Lexer::ValueType GenerateExpr(shared_ptr<AsmCode> ASM, Sem::Scope &scope, size_t &id, vector<Lexer::Token> line) {
  ASM->Code << ";\tEXPRESSION\t" << line[0].position.line << endl;

  bool operationFound = false;
  Lexer::ValueType valType = Lexer::undef; // return type for print

  while(line[id].type != Lexer::semi) {
    switch (line[id].type) {
      case Lexer::liter : {
        ASM->Code << "\tpush\t";
        if (line[id].value.second == Lexer::str) {
          ASM->Code << "offset ";
        }
        ASM->Code << "l" << line[id].literID << endl;
        valType = line[id].value.second;
        break;
      }
      case Lexer::faalse : {
        ASM->Code << "\tpush\t0\n";
        valType = line[id].value.second;
        break;
      }
      case Lexer::truue : {
        ASM->Code << "\tpush\t1\n";
        valType = line[id].value.second;
        break;
      }
      case Lexer::identifier : {
        // if (line[id].identifier->);
        if (line[id].identifier->isFunc) {
          ASM->Code << "\tcall\t" << line[id].identifier->name << endl;
          ASM->Code << "\tpush\teax" << endl;
          if (valType == Lexer::undef)
            valType = line[id].identifier->type;
        } else {
          if(line[id].identifier->type == Lexer::undef) {
            auto result = checkIdentifier(&scope, line[id].identifier);
            line[id].identifier = result;
          }
          // if (line[id].identifier->type == Lexer::bol)
          //   ASM->Code << "\tpush\tbyte ptr[ebp" << line[id].identifier << "]\t; " << line[id].identifier->name << "\n";
          // else
            ASM->Code << "\tpush\tdword ptr[ebp" << line[id].identifier << "]\t; " << line[id].identifier->name << "\n";
          valType = line[id].identifier->type;
        }
        break;
      }
      case Lexer::sub : {
        operationFound = true;
        ASM->Code << ";\tminus" << endl;
        ASM->Code << "\tpop\teax" << endl;
        ASM->Code << "\tpop\tebx" << endl;
        ASM->Code << "\tsub\teax, ebx" << endl;
        ASM->Code << "\tpush\teax" << endl;
        ASM->Code << ";\tminus" << endl;
        break;
      }
      case Lexer::sum : {
        operationFound = true;
        ASM->Code << ";\tplus" << endl;
        ASM->Code << "\tpop\teax" << endl;
        ASM->Code << "\tpop\tebx" << endl;
        ASM->Code << "\tadd\teax, ebx" << endl;
        ASM->Code << "\tpush\teax" << endl;
        ASM->Code << ";\tplus" << endl;
        break;
      }
      case Lexer::multiply : {
        operationFound = true;
        ASM->Code << ";\tmultiply" << endl;
        ASM->Code << "\tpop\teax" << endl;
        ASM->Code << "\tpop\tebx" << endl;
        ASM->Code << "\tmul\tebx" << endl;
        ASM->Code << "\tpush\teax" << endl;
        ASM->Code << ";\tmultiply" << endl;
        break;
      }
      case Lexer::div : {
        operationFound = true;
        ASM->Code << ";\tdiv" << endl;
        ASM->Code << "\tpop\tebx" << endl;
        ASM->Code << "\tpop\teax" << endl;
        ASM->Code << "\txor\tedx, edx" << endl; // Registor of
        ASM->Code << "\tdiv\tebx" << endl;
        ASM->Code << "\tpush\teax" << endl;
        ASM->Code << ";\tdiv" << endl;
        break;
      }
      case Lexer::mod : {
        operationFound = true;
        ASM->Code << ";\tmodule" << endl;
        ASM->Code << "\tpop\tebx" << endl;
        ASM->Code << "\tpop\teax" << endl;
        ASM->Code << "\txor\tedx, edx" << endl; // Registor of
        ASM->Code << "\tdiv\tebx" << endl;
        ASM->Code << "\tpush\tedx" << endl;
        ASM->Code << ";\tmodule" << endl;
        break;
      }
    }
    ++id;
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
  static size_t literID = 0;
  for(auto &token : scope.innerCode) {
    if (token.type == Lexer::liter) {
      token.literID = literID;
      ASM->Const << "\tl" << literID++;
      switch (token.value.second) {
        case Lexer::i : {
          ASM->Const << "\tDWORD\t" << token.value.first << endl;
          break;
        }
        case Lexer::bol : {
          ASM->Const << "\tDB\t" << token.value.first << endl;
          break;
        }
        case Lexer::str : {
          ASM->Const << "\tDB\t'" << token.value.first << "', 0" << endl;
          break;
        }
        case Lexer::undef :
          break;
      }
    }
  }
  for (auto &nScope : scope.nextScopes) {
    WriteLiterals(ASM, *nScope);
  }
}

void GenerateFile(shared_ptr<AsmCode> ASM) {
  if (ASM->asmFile != nullptr && ASM->asmFile->is_open()) {
    *ASM->asmFile << ASM->Head.str() << ASM->Stack.str() << ASM->Const.str() << ASM->Data.str() << ASM->Code.str() << endl;
  } else throw ERROR_THROW(0);
}

}
