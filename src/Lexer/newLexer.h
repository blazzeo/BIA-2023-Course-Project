#pragma once
#include <string>
#include <optional>
#include <vector>
#include "../In/In.h"

namespace Lexer {

enum TokenType {
    whitespace = 0,         // SEPARATORS
    semi,
    open_app_brackets,
    close_app_brackets,
    open_parm_brackets,
    close_parm_brackets,
    open_prioirity,
    close_priority,
    sum,
    multiply,
    div,
    sub,
    comma,
    equals,
    identifier,         //  LEXEMS
    integer,
    string,
    main,
    liter,
    ret,
    func,
    declare,
    print,
    undefined,
    bl,
    colon
};

enum ValueType {
    i,
    str,
    bol,
    undef
};

struct Identifier {
    std::string value;
    std::string name;
    ValueType type;
    bool isFunc = 0;

    Identifier(std::string nm, ValueType tp, bool isfunc = 0)
        : name(nm), type(tp), isFunc(isfunc)
    {
        switch(tp) {
            case i:
                value = "0";
                break;
            case str:
                value = "null";
                break;
            case bol:
                value = "0";
                break;
            case undef:
                value = "0";
                break;
        }
    }
};

const std::string tokenTypes = " ;{}()[]vvvv,=ittmlrfdput:";

struct Token {
    TokenType type;
    unsigned short lineNum;
    char lexema = ' ';
    std::optional<Identifier> identifier;
    std::optional<std::string> value;

    Token() : type(undefined), lineNum(-1) {}
    Token(TokenType tp, short ln) : type(tp), lineNum(ln) {
        lexema = tokenTypes[tp];
        if (tp == 17)
            identifier = Identifier("main", i, 1);
    }
    Token(TokenType tp, short ln, Identifier ident)
    : type(tp), lineNum(ln), identifier(ident) {
        lexema = tokenTypes[tp];
        if (tp == 17)
            identifier = Identifier("main", i, 1);
    }
    Token(TokenType tp, short ln, std::string val)
    : type(tp), lineNum(ln), value(val) {
        lexema = tokenTypes[tp];
        if (tp == 17)
            identifier = Identifier("main", i, 1);
    }
};

struct Table {
    std::vector<Token> tokens;
    std::vector<Identifier> identifiers;
};

// void checkLexem(Table&, std::string, std::vector<Fst::CHAIN>, size_t);
Table tokenize(In::IN&);
}
