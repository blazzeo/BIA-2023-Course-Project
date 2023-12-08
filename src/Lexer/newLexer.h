#pragma once
#include <memory>
#include <string>
#include <optional>
#include <variant>
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
    colon,
    condition,
    loop,
    less,
    greater,
    mod,
    equal,
    nequal
};

enum ValueType {
    i,
    str,
    bol,
    undef
};

struct Identifier {
  std::string name;
  ValueType type;
  bool isFunc = 0;
  std::variant<int, std::string, bool> value;
  short parms_count = 0;

    Identifier(std::string nm, ValueType tp, bool isfunc = 0)
        : name(nm), type(tp), isFunc(isfunc)
    {
        switch(tp) {
            case i:
                value = (int)0;
                break;
            case str:
                value = "";
                break;
            case bol:
                value = false;
                break;
            case undef:
                value = "undef";
                break;
        }
    }
};

const std::string tokenTypes = " ;{}()[]vvvv,=ittmlrfdput:?@vvv";

struct Token {
  TokenType type;
  unsigned short lineNum;
  char lexema = ' ';
  std::shared_ptr<Identifier> identifier = nullptr;
  std::string value;

  Token() : type(undefined), lineNum(-1) {}
  Token(TokenType tp, short ln, std::string val = "")
      : type(tp), lineNum(ln), value(val) {
    lexema = tokenTypes[tp];
  }
  Token(TokenType tp, short ln, std::shared_ptr<Identifier> ident)
      : type(tp), lineNum(ln), identifier(ident) {
    lexema = tokenTypes[tp];
  }
  Token& operator=(Token oldToken) {
    this->type = oldToken.type;
    this->lineNum = oldToken.lineNum;
    this->lexema = oldToken.lexema;
    this->identifier = oldToken.identifier;
    this->value = oldToken.value;
    return *this;
  }
};

struct Table {
    std::vector<Token> tokens;
    std::vector<std::shared_ptr<Identifier>> identifiers;
};

// void checkLexem(Table&, std::string, std::vector<Fst::CHAIN>, size_t);
Table tokenize(In::IN&);
void generateLog(Table&);
}
