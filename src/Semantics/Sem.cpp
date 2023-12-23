#include "../Lexer/newLexer.h"
#include "../Error/Error.h"
#include "../PolishNotation/PolishNotation.h"
#include "Sem.h"
#include <iostream>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>

namespace Sem {

std::shared_ptr<Lexer::Identifier> checkIdentifier(Scope *scope, std::shared_ptr<Lexer::Identifier> &ident) {
  std::shared_ptr<Lexer::Identifier> result = nullptr;
  for (auto inIdent : scope->Identifiers) { //  check in Identifiers
    if (inIdent->name == ident->name) {
      return inIdent;
      break;
    }
  }
  if (!result) {
    for (auto parm : scope->parms) { //   check in parms
      if (parm->name == ident->name) {
        return parm;
        break;
      }
    }
  }
  if (!result && scope->prevScope) { //   if prevScope exists and ident not found
    return checkIdentifier(scope->prevScope, ident);
  }
  return result;
}

Scope* scopenize(Lexer::Table *table, int& id, Scope *prevScope, size_t offset) {
  Scope *scope_ptr = new Scope();
  Scope &scope = *scope_ptr;
  scope.prevScope = prevScope;
  size_t stackSize = 0;
  if (!prevScope) {
    scope.specs.name = "GLOBAL";
    std::shared_ptr<Lexer::Identifier> Strlen = std::make_shared<Lexer::Identifier>("Strlen", Lexer::i, 1);
    std::shared_ptr<Lexer::Identifier> convertToNum = std::make_shared<Lexer::Identifier>("convertToNum", Lexer::i, 1);
    Strlen->size = 4;
    Strlen->parms = {std::make_shared<Lexer::Identifier>("str", Lexer::str, 0)};
    convertToNum->size = 4;
    convertToNum->parms = {std::make_shared<Lexer::Identifier>("str", Lexer::str, 0)};
    scope.Identifiers.push_back(Strlen);
    scope.Identifiers.push_back(convertToNum);
  }
  else id++;

  //  SCOPE SPECS
  if (prevScope != nullptr) {
    bool parmlist = false;
    int i = id - 2;
    Lexer::Token token = table->tokens[i];
    while(i >= 0 && (token.type != Lexer::semi || token.type != Lexer::open_app_brackets)) {
      token = table->tokens[i];
      if (token.type == Lexer::close_parm_brackets) {
        parmlist = true;  //  ParmFlag if parms available
        while(token.type != Lexer::open_parm_brackets) {
          if (token.type == Lexer::identifier) {
            scope.parms.push_back(token.identifier); //  Add Parms to Scope
          }
          token = table->tokens[--i];
        }
      }
      if (token.type == Lexer::loop) {
        scope.specs.name = "for";
        scope.specs.returnType = Lexer::undef;
        break;
      }
      if (token.type == Lexer::condition) { // IF Token
        scope.specs.name = "if";
        scope.specs.returnType = Lexer::undef;
        break;
      }
      if (token.type == Lexer::identifier) { // Identifier Token
        if (!parmlist) break;

        token.identifier->parms = scope.parms;

        scope.specs.name = token.identifier->name;
        scope.specs.returnType = token.identifier->type;
        scope.specs.isFunc = token.identifier->isFunc;
        break;
      }
      if (token.type == Lexer::main) {  //  Main Token
        scope.specs.name = token.identifier->name;
        scope.specs.returnType = token.identifier->type;
        break;
      }
      --i;
    }
  }

  for (short i = scope.parms.size()-1 , size = 8; i >= 0; i--) {
    scope.parms[i]->offset = size;
    size += scope.parms[i]->size;
  }

  if (scope.specs.isFunc || scope.specs.name == "main")
    offset = 0;

  Lexer::ValueType Expr = Lexer::undef; //  Expression Type
  Lexer::Token tmpIdent;
  bool returnFound = false;             //  returnFlag

  while (id < table->tokens.size()) {
    Lexer::Token token = table->tokens[id];
    scope.innerCode.push_back(token);
    switch (token.type) {
      case Lexer::func :
        scope.specs.isFunc = true;
        break;
      case Lexer::identifier : {
        if (token.identifier->type != Lexer::undef) {
          bool found = false;
          for (auto parm : scope.parms) { //  find identifier in scope parms
            if (parm->name == token.identifier->name) {
              found = true;
              break;
            }
          }
          for (auto ident : scope.Identifiers) { //   find identifier in scope Identifier
            if (ident->name == token.identifier->name) { 
              found = true;
              break;
            }
          }
          if (found) throw ERROR_THROW_WORD(403, token.identifier->name, table->tokens[id].position); //   if ident was declared before
          scope.offset_length += token.identifier->size;
          token.identifier->offset = -(scope.offset_length + offset);
          scope.Identifiers.push_back(token.identifier); //  if ident wasn't found before push
        } else {  //  if identifier hasn't got type -> find first declaration
          auto result = checkIdentifier(&scope, table->tokens[id].identifier);
          if (result == nullptr) { //   if idenifier's declaration wasn't found
            throw ERROR_THROW_POS(402, table->tokens[id].position);
          }
          table->tokens[id].identifier = result;
        }
        tmpIdent = table->tokens[id];
        break;
      }
      case Lexer::open_app_brackets : {
        scope.nextScopes.push_back(scopenize(table, id, scope_ptr, scope.offset_length + offset));
        scope.offset_length += scope.nextScopes.back()->offset_length;
        if (!scope.nextScopes.back()->parms.empty() && 
            (scope.nextScopes.back()->specs.name != "if" && scope.nextScopes.back()->specs.name != "for")) {
          for (size_t i=0; i<scope.nextScopes.back()->parms.size();++i)
            scope.Identifiers.erase(scope.Identifiers.end()-1);
        }
        break;
      }
      case Lexer::equals: { //  PolishNotation Check
        Expr = checkNotation(*table, id, scope);
        if (tmpIdent.identifier->type != Expr) {
          std::cout << tmpIdent.identifier->name << std::endl;
          throw ERROR_THROW_POS(406, tmpIdent.position);
        }
        break;
      }
      case Lexer::ret: { //   PolishNotation Check
        Expr = checkNotation(*table, id, scope);
        if (scope.specs.isFunc && scope.specs.returnType != Expr) {
          throw ERROR_THROW_POS(401, table->tokens[id-1].position);
        }
        returnFound = true;
        break;
      }
      case Lexer::close_app_brackets : {
        if (scope.specs.isFunc && !returnFound)
          throw ERROR_THROW_POS(404, table->tokens[id-1].position);
        return &scope;
        break;
      }
      default: {
        ++id;
        continue;
      }
    }
    ++id;
  }

  return &scope;
}

using namespace std;

bool recursiveCheck(Scope scope) {
  for (auto nScope : scope.nextScopes) {
    if (nScope->specs.name == "main")
      return true;
  }
  return false;
}

void MainCheck(Scope scope) {
  if (!recursiveCheck(scope)) {
    throw ERROR_THROW(407);
  }
}

void PrintTable(Scope scope, short level) {
  string type [4] = {
    "int",
    "char",
    "bool",
    "void"
  };
  string tabs(level, '\t');
  tabs[level-1] = '|';
  cout << endl << tabs << "==== " << scope.specs.name << " : " << type[scope.specs.returnType] << " ====" <<endl;
  cout << tabs << "Stack size: \t" << scope.offset_length << std::endl;
  cout << tabs << "Parms : \n";
  for (size_t i = 0; i < scope.parms.size(); i++) { //  Scope Parms
    cout << tabs << i << '\t' << scope.parms[i]->name << '\t' << type[scope.parms[i]->type] << endl;
  }
  cout << tabs << "Identifiers : \n";
  for (size_t i = 0; i < scope.Identifiers.size(); i++) { //  Scope Identifiers
    cout << tabs << i << '\t' << scope.Identifiers[i]->name <<
      '\t' << type[scope.Identifiers[i]->type] <<
      '\t' << scope.Identifiers[i]->offset << endl;
  }

  if (!scope.nextScopes.empty()) {
    cout << tabs << "Next scopes: \n";
    for (size_t i = 0; i < scope.nextScopes.size(); i++) {
      cout << tabs << i << '\t' << scope.nextScopes[i]->specs.name << '\t' << type[scope.nextScopes[i]->specs.returnType] << endl;
    }
    for(auto nscope : scope.nextScopes) {
      PrintTable(*nscope, level+1);
    }
  }
  return;
}
}
