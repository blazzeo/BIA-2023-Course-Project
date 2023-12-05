#include "../Lexer/newLexer.h"
#include "../Error/Error.h"
#include "iostream"
#include "Sem.h"
#include <cstddef>
#include <string>

namespace Sem {

Scope scopenize(Lexer::Table *table, int& id, Scope *prevScope) {
    Scope scope;
    id++;
    if (!prevScope) scope.specs.name = "GLOBAL";
    scope.prevScope = prevScope;

  //  SCOPE SPECS
    if (prevScope != nullptr) {
        bool parmlist = false;
        int i = id;
        while(i > 0) {
            Lexer::Token token = table->tokens[i];
            if (token.type == Lexer::close_parm_brackets) {
                parmlist = true;
                while(token.type != Lexer::open_parm_brackets) {
                    if (token.type == Lexer::identifier) {
                        scope.parms.push_back(token.identifier);
                    }
                    token = table->tokens[--i];
                }
            }
            // if (token.type == Lexer::func) {
            //     scope.specs.isFunc = true;
            // }
            if (token.type == Lexer::condition) {
                scope.specs.name = "if";
                scope.specs.returnType = Lexer::undef;
                break;
            }
            if (token.type == Lexer::identifier) {
                if (!parmlist) break;
                scope.specs.name = token.identifier->name;
                scope.specs.returnType = token.identifier->type;
                scope.specs.isFunc = token.identifier->isFunc;
                break;
            }
            if (token.type == Lexer::main) {
                scope.specs.name = token.identifier->name;
                scope.specs.returnType = token.identifier->type;
                break;
            }
            --i;
        }
    }

    while (id < table->tokens.size()) {
        Lexer::Token token = table->tokens[id];
        switch (token.type) {
            case Lexer::identifier : {
                if (token.identifier->isFunc) scope.specs.isFunc = true;
                if (token.identifier->type != Lexer::undef) {
                    bool found = false;
                    for (auto parm : scope.parms)
                        if (parm->name == token.identifier->name) 
                          found = true;
                    for (auto ident : scope.Identifiers)
                      if (ident->name == token.identifier->name) // if ident was declared before
                          // throw ERROR_THROW(100);
                    if (!found) scope.Identifiers.push_back(token.identifier);
                }
                break;
            }
            case Lexer::open_app_brackets : {
                scope.nextScopes.push_back(scopenize(table, id, &scope));
                if (!scope.nextScopes.back().parms.empty()) {
                    for (size_t i=0; i<scope.nextScopes.back().parms.size();i++)
                        scope.Identifiers.erase(scope.Identifiers.end()-1);
                }
                if (scope.nextScopes.back().specs.name!="undef" &&
                    scope.nextScopes.back().specs.name!="main")
                    scope.Identifiers.erase(scope.Identifiers.end()-1);
                break;
            }
            case Lexer::close_app_brackets : {
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

void PrintTable(Scope scope, short level) {
  std::string type [4] = {
    "int",
    "str",
    "bool",
    "void"
  };
  std::string tabs(level, '\t');
  tabs[level-1]='|';
  std::cout << std::endl << tabs << "==== " << scope.specs.name << " : " << type[scope.specs.returnType] << std::endl;
  std::cout << " ====" << '\n';
  std::cout << tabs << "Parms : \n";
  for (size_t i = 0; i < scope.parms.size(); i++) {
    std::cout << tabs << i << '\t' << scope.parms[i]->name << '\t' << type[scope.parms[i]->type] << std::endl;
  }
  std::cout << tabs << "Identifiers : \n";
  for (size_t i = 0; i < scope.Identifiers.size(); i++) {
    std::cout << tabs << i << '\t' << scope.Identifiers[i]->name << '\t' << type[scope.Identifiers[i]->type] << std::endl;
  }
  if (!scope.nextScopes.empty()) {
    std::cout << tabs << "Next scopes: \n";
    for (size_t i = 0; i < scope.nextScopes.size(); i++) {
      std::cout << tabs << i << '\t' << scope.nextScopes[i].specs.name << '\t' << type[scope.nextScopes[i].specs.returnType] << std::endl;
    }
    for(auto nscope : scope.nextScopes) {
      PrintTable(nscope, level+1);
    }
  }
  return;
}
}
