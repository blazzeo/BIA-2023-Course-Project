#include "../Chains/ChainsEnum.h"
#include "../Error/Error.h"
#include "../In/In.h"
#include "../fst/FST.h"
#include "newLexer.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>

#define NEWLINE '\n'
#define STR '\''
#define SEPARATOR '$'

const std::string SEPARATORS = " /:;=*,+-(){}<>\t";
std::vector<Fst::CHAIN> vectorOfChains = {STR_LITER, MAIN, INT_LITER, BOOL_LITER, RETURN, FUNCTION, PRINT, DECLARE, LITER, IF, FOR, IDENTIFIER};
std::vector<Fst::CHAIN> vectorOfSeparators = {DIV, SEMI, CLOSE_APP_BRACKET, OPEN_APP_BRACKET, OPEN_PARM_BRACKET, CLOSE_PARM_BRACKET, SUM, COLON, SUB, COMMA, MULTIPLY, LESS, GREATER, EQUALS};

namespace Lexer {
void checkLexem(Table& table, std::string word,
                std::vector<Fst::CHAIN> chains, size_t lineNum)
{
  static short identId = 0;
  static bool funcType = false;

  for(auto chain : chains)
  {
    Fst::FST fst(word.c_str(), chain);
    if (Fst::execute(fst))
    {
      switch ((int)chain.type) {
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
          table.tokens[identId-1].identifier->type = i;
          break;
        }
        case 16: {  //      STRING FLAG
          Token token(chain.type, lineNum);
          table.tokens.push_back(token);
          table.identifiers.back()->type = str;
          table.tokens[identId-1].identifier->type = str;
          break;
        }
        case 24: {  //      BOOL FLAG
          // Token token(chain.type, lineNum);
          // table.tokens.push_back(token);
          // table.identifiers.back()->type = bol;
          // table.tokens[identId-1].identifier->type = bol;
          // break;
          std::shared_ptr<Identifier> ident(new Identifier(word, i, 1));
          Token token(chain.type, lineNum, ident);
          table.identifiers.push_back(ident);
          table.tokens.push_back(token);
          break;
        }
        case 14: { //      IDENTIFIER
          std::shared_ptr<Identifier> ident(new Identifier(word, undef));
          table.identifiers.push_back(ident);
          Token token(chain.type, lineNum, ident);
          table.tokens.push_back(token);
          break;
        }
        case 18: {  //      LITERAL
          Token token(chain.type, lineNum, word);
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
        if (!word.empty()) {
          checkLexem(table, word, vectorOfChains, lineNum);
          word.clear();
        }
        if (in.text[i]!=' ' && in.text[i]!='\t') {
          word.push_back(in.text[i]);
          checkLexem(table, word, vectorOfSeparators, lineNum);
          word.clear();
        }
        break;
      case STR : {       // STR LITER
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

void generateLog(Table &table) {
  std::ofstream it("IdentifierTable.it");
  if (it.is_open()) {
    it << "-------- IdentifierTable ---------" << std::endl;
    for (auto ident : table.identifiers) {
      it << ident->name << "\t";
      switch (ident->type) {
        case i:
          it << "int\t" << std::get<int>(ident->value) << (ident->isFunc?"func\n":"\n");
          break;
        case str:
          it << "str\t" << std::get<std::string>(ident->value) << (ident->isFunc?"func\n":"\n");
          break;
        case bol:
          it << "bool\t" << std::get<bool>(ident->value) << (ident->isFunc?"func\n":"\n");
          break;
        default:
          it << "undef\t" << std::endl;
          break;
      }
    }
  } else Error::geterror(202);
  it.close();
  std::ofstream lt("LexemTable.lt");
  if (lt.is_open()) {
    lt << "-------- LexemTable ---------" << std::endl;
    for (auto token : table.tokens) {
      lt << token.type << '\t' << token.lexema << '\t' << token.lineNum << std::endl;
    }
  } else Error::geterror(203);
  lt.close();
}

}
