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
    std::cout << inIdent->name << std::endl;
    if (inIdent->name == ident->name) {
      return inIdent;
      break;
    }
  }
  if (!result) {
    for (auto parm : scope->parms) { //   check in parms
      if (parm->name == ident->name) {
        result = parm;
        break;
      }
    }
  }
  if (!result && scope->prevScope) { //   if prevScope exists and ident not found
    return checkIdentifier(scope->prevScope, ident);
  }
  return result;
}

Scope scopenize(Lexer::Table *table, int& id, Scope *prevScope) {
  Scope scope;
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
  scope.prevScope = prevScope;

  //  SCOPE SPECS
  if (prevScope != nullptr) {
    bool parmlist = false;
    int i = id;
    while(i > 0) {
      Lexer::Token token = table->tokens[i];
      if (token.type == Lexer::close_parm_brackets) {
        parmlist = true;  //  ParmFlag if parms available
        while(token.type != Lexer::open_parm_brackets) {
          if (token.type == Lexer::identifier) {
            // token.identifier->offset = stackSize;
            scope.parms.push_back(token.identifier); //  Add Parms to Scope
            // stackSize += token.identifier->size;  //  Resize Stack Size
          }
          token = table->tokens[--i];
        }
      }
      // if (token.type == Lexer::func) {
      //     scope.specs.isFunc = true;
      // }
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

  Lexer::ValueType Expr = Lexer::undef; //  Expression Type
  bool returnFound = false;             //  returnFlag

  while (id < table->tokens.size()) {
    Lexer::Token token = table->tokens[id];
    scope.innerCode.push_back(token);
    switch (token.type) {
      case Lexer::func :
        scope.specs.isFunc = true;
        break;
      case Lexer::identifier : {
        // if (token.identifier->isFunc)
        //   scope.specs.isFunc = true;
        if (token.identifier->type != Lexer::undef) {
          bool found = false;
          for (auto parm : scope.parms) { //  find identifier in scope parms
            if (parm->name == token.identifier->name) {
              found = true;
              break;
            }
          }
          for (auto ident : scope.Identifiers) { //   find identifier in scope Identifiers
            if (ident->name == token.identifier->name) { 
              found = true;
              break;
            }
          }
          if (found) throw ERROR_THROW_WORD(403, token.identifier->name, table->tokens[id].position); //   if ident was declared before
          scope.offset_length += token.identifier->size;
          token.identifier->offset = scope.offset_length;
          scope.Identifiers.push_back(token.identifier); //  if ident wasn't found before push
        } else {  //  if identifier hasn't got type -> find first declaration
          auto result = checkIdentifier(&scope, table->tokens[id].identifier);
          if (result == nullptr) { //   if identifier's declaration wasn't found
            throw ERROR_THROW_POS(402, table->tokens[id].position);
          }
          table->tokens[id].identifier = result;
          // scope.offset_length += result->size;
        }
        break;
      }
      case Lexer::open_app_brackets : {
        scope.nextScopes.push_back(scopenize(table, id, &scope));
        if (!scope.nextScopes.back().parms.empty() && scope.nextScopes.back().specs.name != "if") {
          for (size_t i=0; i<scope.nextScopes.back().parms.size();++i)
            scope.Identifiers.erase(scope.Identifiers.end()-1);
        }
        // if (scope.nextScopes.back().specs.returnType!=Lexer::undef &&
        //   scope.nextScopes.back().specs.name!="main")
        //                                     scope.Identifiers.erase(scope.Identifiers.end()-1);
        break;
      }
      case Lexer::equals: { //  PolishNotation Check
        Expr = checkNotation(*table, id, scope);
        // if (table->tokens[id-1].identifier->type != Expr)
        if (table->tokens[id-1].type == Lexer::identifier && table->tokens[id-1].identifier->type != Expr) {
          throw ERROR_THROW_POS(407, table->tokens[id-1].position);
        } else if (table->tokens[id-3].type == Lexer::identifier && table->tokens[id-3].identifier->type != Expr) {
          throw ERROR_THROW_POS(407, table->tokens[id-1].position);
        } else if (table->tokens[id-6].type == Lexer::identifier && table->tokens[id-6].identifier->type != Expr) {
          throw ERROR_THROW_POS(407, table->tokens[id-1].position);
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
        return scope;
        break;
      }
      default: {
        ++id;
        continue;
      }
    }
    ++id;
  }

  return scope;
}

using namespace std;

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
      cout << tabs << i << '\t' << scope.nextScopes[i].specs.name << '\t' << type[scope.nextScopes[i].specs.returnType] << endl;
    }
    for(auto nscope : scope.nextScopes) {
      PrintTable(nscope, level+1);
    }
  }
  return;
}
}
