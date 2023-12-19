#pragma once
#include <memory>
#include <string>
#include <optional>
#include <utility>
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
    open_priority,
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
    nequal,
    truue,
    faalse
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
  size_t size = 0;
  size_t offset = 0;
  bool isFunc = 0;
  std::variant<int, std::string, bool> value = "undef";
  std::vector<std::shared_ptr<Lexer::Identifier>> parms{};

  Identifier(const std::string &nm, ValueType tp, bool isfunc = 0)
  : name(nm), type(tp), isFunc(isfunc) {}
};

const std::string tokenTypes = " ;{}()[]vvvv,=ittmlrfdput:?@vvvvvll";

struct Position {
  short line = 0;
  short col = 0;
};

struct Token {
  TokenType type;
  char lexema = ' ';
  Position position;
  std::shared_ptr<Identifier> identifier = nullptr;
  std::pair<std::string, ValueType> value;

  Token()
    : type(undefined) {}
  Token(TokenType tp, short ln, short col, std::string val = "", ValueType valueType = i)
    : type(tp), position({ln, col}), value({val,valueType}) {
    lexema = tokenTypes[tp];
  }
  Token(TokenType tp, short ln, short col, std::shared_ptr<Identifier> ident)
    : type(tp), position({ln, col}), identifier(ident) {
    lexema = tokenTypes[tp];
  }
  Token& operator=(Token oldToken) {
    this->type = oldToken.type;
    this->position = oldToken.position;
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
