#include "../Lexer/newLexer.h"
#include "../Error/Error.h"
#include "iostream"
#include "Sem.h"
#include <cstddef>
#include <iomanip>
#include "iomanip"
#include "format"

namespace Sem {

Scope scopenize(Lexer::Table *table, int& id, Scope *prevScope) {
    Scope scope;
    id++;
    if (!prevScope) scope.specs.name = "GLOBAL";
    scope.prevScope = prevScope;

    if (prevScope != nullptr) {
        bool parmlist = false;
        int i = id;
        while(i > 0) {
            Lexer::Token token = table->tokens[i];
            if (token.type == Lexer::close_parm_brackets) {
                parmlist = true;
                while(token.type != Lexer::open_parm_brackets) {
                    if (token.type == Lexer::identifier) {
                        scope.parms.push_back(token.identifier.value());
                    }
                    token = table->tokens[--i];
                }
            }
            // if (token.type == Lexer::func) {
            //     scope.specs.isFunc = true;
            // }
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
                        if (parm.name == token.identifier->name) 
                        found = true;
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

void PrintTable(Scope scope) {
    std::cout << "===========" << ' '<< scope.specs.name << ' ' << "=============" << '\n';
    std::cout << "Parms : \n";
    for (size_t i = 0; i < scope.parms.size(); i++) {
        std::cout << i << '\t' << scope.parms[i].name << '\t';
        switch(scope.parms[i].type) {
            case 0 :
                std::cout << "int" << std::endl;
                break;
            case 1 :
                std::cout << "str" << std::endl;
                break;
            case 2 :
                std::cout << "bool" << std::endl;
                break;
            case 3 :
                std::cout << "undef" << std::endl;
                break;
        }
    }
    std::cout << "Identifiers : \n";
    for (size_t i = 0; i < scope.Identifiers.size(); i++) {
        std::cout << i << '\t' << scope.Identifiers[i]->name << '\t'; 
        switch(scope.Identifiers[i]->type) {
            case 0 :
                std::cout << "int" << std::endl;
                break;
            case 1 :
                std::cout << "str" << std::endl;
                break;
            case 2 :
                std::cout << "bool" << std::endl;
                break;
            case 3 :
                std::cout << "undef" << std::endl;
                break;
        }
    }
    if (!scope.nextScopes.empty()) {
        std::cout << "Next scopes: \n";
        for (size_t i = 0; i < scope.nextScopes.size(); i++) {
            std::cout << i << '\t' << scope.nextScopes[i].specs.name << '\t'; 
            switch (scope.nextScopes[i].specs.returnType) {
                case 0 :
                    std::cout << "int" << std::endl;
                    break;
                case 1 :
                    std::cout << "str" << std::endl;
                    break;
                case 2 :
                    std::cout << "bool" << std::endl;
                    break;
                case 3 :
                    std::cout << "undef" << std::endl;
                    break;
            }
        }
        for(auto nscope : scope.nextScopes) {
            PrintTable(nscope);
        }
    }
    return;
}
}
