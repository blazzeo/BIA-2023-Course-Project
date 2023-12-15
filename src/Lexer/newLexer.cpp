#include "../Chains/ChainsEnum.h"
#include "../Error/Error.h"
#include "../In/In.h"
#include "../fst/FST.h"
#include "newLexer.h"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <ostream>
#include <string>
#include <variant>

#define NEWLINE '\n'
#define STR '\''
#define SEPARATOR '$'

const std::string SEPARATORS = " /:;=*,+-()[]{}<>\t!";
std::vector<Fst::CHAIN> vectorOfChains = {STR_LITER, MAIN, INT_LITER, BOOL_LITER, RETURN, FUNCTION, PRINT, DECLARE, LITER, IF, FOR, IDENTIFIER};
std::vector<Fst::CHAIN> vectorOfSeparators = {DIV, SEMI, CLOSE_APP_BRACKET, OPEN_APP_BRACKET, OPEN_PARM_BRACKET, CLOSE_PARM_BRACKET, OPEN_SQUARE, CLOSE_SQUARE, SUM, COLON, SUB, COMMA, MULTIPLY, MOD, LESS, GREATER, EQUALS, EQUAL, NEQUAL};

namespace Lexer {
void checkLexem(Table& table, std::string word, std::vector<Fst::CHAIN> chains, size_t lineNum)
{
  static short identId = 0;
  static bool offsetFlag = false;
  static int offset_length = 0;
  static bool funcType = false;

  for(auto chain : chains)
  {
    Fst::FST fst(word.c_str(), chain);
    if (Fst::execute(fst))
    {
      switch ((int)chain.type) {
        case 6: {
          offsetFlag = true;
        }
        case 20: {  //      FUNC FLAG
          Token token(chain.type, lineNum);
          funcType = true;
          table.tokens.push_back(token);
          break;
        }
        case 15: {  //      INT FLAG
          Token token(chain.type, lineNum);
          table.tokens.push_back(token);
          table.identifiers.back()->type = i;
          table.identifiers.back()->value = 0;
          table.identifiers.back()->size = 4;
          break;
        }
        case 16: {  //      CHAR FLAG
          Token token(chain.type, lineNum);
          table.tokens.push_back(token);
          table.identifiers.back()->type = str;
          table.identifiers.back()->value = "";
          table.identifiers.back()->size = offset_length + 1;
          break;
        }
        case 24: {  //      BOOL FLAG
          Token token(chain.type, lineNum);
          table.tokens.push_back(token);
          table.identifiers.back()->type = bol;
          table.identifiers.back()->value = false;
          table.identifiers.back()->size = 1;
          break;
        }
        case 14: {  //      IDENTIFIER
          std::shared_ptr<Identifier> ident(new Identifier(word, undef, funcType));
          funcType = false;
          table.identifiers.push_back(ident);
          Token token(chain.type, lineNum, ident);
          table.tokens.push_back(token);
          break;
        }
        case 18: {  //      LITERAL
          if (offsetFlag) {
            offset_length = atoi(word.c_str());
            offsetFlag = false;
          }
          Token token(chain.type, lineNum, word);
          table.tokens.push_back(token);
          break;
        }
        case 17: {  //       MAIN
          std::shared_ptr<Identifier> ident(new Identifier(word, i, 1));
          Token token(chain.type, lineNum, ident);
          table.identifiers.push_back(ident);
          table.tokens.push_back(token);
          break;
        }
        default: {  //      OTHER
          Token token(chain.type, lineNum);
          table.tokens.push_back(token);
          break;
        }
      }
      return;
    }
  }
  throw ERROR_THROW_LEXER(114, lineNum, word);
}

std::string findSymbolIndex(const unsigned char* str) {
  std::string strLiter;
  size_t i = 0;
  while (str[i] != '\'') {
    strLiter += str[i];
    i++;
  }
  return strLiter;
}

Table tokenize(In::IN &in) {
  Table table;
  std::string word;
  for (size_t i = 0, lineNum = 0; i < in.size; i++) {
    char symbol = (SEPARATORS.find(in.text[i]) != std::string::npos) ? 
      '$' : in.text[i];
    switch (symbol) {
      case NEWLINE :         // NEW LINE
        word.clear();
        lineNum++;
        break;
      case SEPARATOR :          // SEPARATOR, WORD
        if (!word.empty()) {                        // WORD CHECK
          checkLexem(table, word, vectorOfChains, lineNum);
          word.clear();
        }
        if (in.text[i]!=' ' && in.text[i]!='\t') {  //  SEPARATOR CHECK
          if ((in.text[i]=='=' && in.text[i+1]=='=') ||
              (in.text[i]=='!' && in.text[i+1]=='=')) {
            word.push_back(in.text[i]);
            word.push_back(in.text[i+1]);
            checkLexem(table, word, vectorOfSeparators, lineNum);
            ++i;
            word.clear();
          } else {
            word.push_back(in.text[i]);
            checkLexem(table, word, vectorOfSeparators, lineNum);
            word.clear();
          }
        }
        break;
      case STR : {                                  // STR LITER
        std::string str = findSymbolIndex(in.text + i + 1); // find substring
        word.insert(0, str);
        Token Token(liter, lineNum, word);
        table.tokens.push_back(Token);
        i+=word.length()+1;
        word.clear();
        break;
      }
      default:            // DEFAULT
        word+=symbol;
        break;
    }
  }
  return table;
}

std::string tokens[33] = {
  "SPACE",
  ";",
  "Open Bracket",
  "Close Bracket",
  "Open Parm",
  "Close Parm",
  "Open Priority",
  "Close Priority",
  "+",
  "*",
  "\\",
  "-",
  ",",
  "=",
  "Identifier",
  "i32",
  "string",
  "main",
  "Literal",
  "return",
  "fn",
  "let",
  "print",
  "Undefined",
  "bool",
  "Colon",
  "if",
  "for",
  "<",
  ">",
  "%",
  "==",
  "!="
};

struct PRNT {
  std::string operator()(std::string value){
    return value;
  }
  std::string operator()(bool value){
    return std::to_string(value);
  }
  std::string operator()(int value){
    return std::to_string(value);
  }
};

void generateLog(Table &table) {
  std::ofstream it("IdentifierTable.it");
  if (it.is_open()) {
    it << "------------- IdentifierTable ---------------" << std::endl;
    it << std::setw(15) << "Name" << std::setw(10) << "DataType" << std::setw(10) << "Value" << std::setw(10) << "IsFunc" << std::endl;
    for (auto ident : table.identifiers) {
      std::string st = std::visit(PRNT(), ident->value);
      it << std::setw(15) << ident->name;
      switch (ident->type) {
        case i: {
          it << std::setw(10) << "i32" << std::setw(10) << st;
          it << std::setw(10) << (ident->isFunc?"Func\n":"\n");
          break;
        }
        case str:
          it << std::setw(10) << "string" << std::setw(10) << st;
          it << std::setw(10) << (ident->isFunc?"Func\n":"\n");
          break;
        case bol:
          it << std::setw(10) << "bool" << std::setw(10) << st;
          it << std::setw(10) << (ident->isFunc?"Func\n":"\n");
          break;
        default:
          it << std::setw(10) << "undef" << std::setw(10) << st;
          it << std::setw(10) << (ident->isFunc?"Func\n":"\n");
          break;
      }
    }
  } else Error::geterror(202);
  it.close();
  std::ofstream lt("LexemTable.lt");
  if (lt.is_open()) {
    lt << "---------------- LexemTable -----------------" << std::endl;
    lt << std::setw(15) << "Type" << std::setw(10) << "Lexem" << std::setw(10) << "LineNum" << std::setw(10) << "Value" << std::endl;
    for (auto token : table.tokens) {
      lt << std::setw(15) << tokens[token.type] << std::setw(10) << token.lexema << std::setw(10) << token.lineNum;
      if(token.type == liter) lt << std::setw(10) << token.value;
      lt << std::endl;
    }
  } else Error::geterror(203);
  lt.close();
}

}
