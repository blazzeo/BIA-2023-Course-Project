#pragma once
#include "../Error/Error.h"
#include "../Lexer/newLexer.h"
#include <memory>
#include <optional>
#include <vector>

namespace Sem {

struct Scope {
    struct Specs {
        Lexer::ValueType returnType = Lexer::undef;
        bool isFunc = false;
        std::string name = "undef";
    } specs;
    std::vector<Lexer::Identifier> Identifiers;
    std::vector<Lexer::Identifier> parms;
    Scope* prevScope = nullptr;
    std::vector<Scope> nextScopes;
    std::vector<Lexer::Token> innerCode;
};

Scope scopenize(Lexer::Table*, int&, Scope* = nullptr);
void PrintTable(Scope, short = 0);

}
