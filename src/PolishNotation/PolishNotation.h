#pragma once
#include "../Lexer/newLexer.h"
#include "../Semantics/Sem.h"

Lexer::ValueType checkNotation(Lexer::Table&, int&, Sem::Scope&);
void printTable(Lexer::Table &, size_t , size_t );
