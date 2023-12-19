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
    size_t offset_length = 0;
    std::vector<std::shared_ptr<Lexer::Identifier>> Identifiers;
    std::vector<std::shared_ptr<Lexer::Identifier>> parms;
    Scope* prevScope = nullptr;
    std::vector<Scope> nextScopes;
    std::vector<Lexer::Token> innerCode;
};

Scope scopenize(Lexer::Table*, int&, Scope* = nullptr);
void PrintTable(Scope, short = 0);
std::shared_ptr<Lexer::Identifier> checkIdentifier(Scope *scope, std::shared_ptr<Lexer::Identifier> &ident);

}
