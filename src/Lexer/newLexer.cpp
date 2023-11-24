#include "../Chains/ChainsEnum.h"
#include "../Error/Error.h"
#include "../In/In.h"
#include "../fst/FST.h"
#include "newLexer.h"
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>

#define NEWLINE '\n'
#define STR '\''
#define SEPARATOR '$'

const std::string SEPARATORS = " /;=*,+-(){}\t";
std::vector<Fst::CHAIN> vectorOfChains = {STR_LITER, MAIN, INT_LITER, BOOL_LITER, RETURN, FUNCTION, PRINT, DECLARE, LITER, IDENTIFIER, COLON};
std::vector<Fst::CHAIN> vectorOfSeparators = {DIV, SEMI, CLOSE_APP_BRACKET, OPEN_APP_BRACKET, OPEN_PARM_BRACKET, CLOSE_PARM_BRACKET, SUM, SUB, COMMA, MULTIPLY, EQUALS};

namespace Lexer {
void checkLexem(Table& table, std::string word,
                std::vector<Fst::CHAIN> chains, size_t lineNum)
{
    static short identId = 0;
    static bool funcType = false;
    static bool intType = false;
    static bool strType = false;
    static bool boolType = false;

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
                    // intType = true;
                    table.tokens.push_back(token);
                    table.identifiers.back().type = i;
                    table.tokens[identId-1].identifier->type = i;
                    break;
                }
                case 16: {  //      STRING FLAG
                    Token token(chain.type, lineNum);
                    // strType = true;
                    table.tokens.push_back(token);
                    table.identifiers.back().type = str;
                    table.tokens[identId-1].identifier->type = str;
                    break;
                }
                case 24: {  //      BOOL FLAG
                    Token token(chain.type, lineNum);
                    table.tokens.push_back(token);
                    table.identifiers.back().type = bol;
                    break;
                }
                case 14: {  //      IDENTIFIER
                    if (intType) {
                        Identifier ident(word, i, funcType);
                        Token token(chain.type, lineNum, ident);
                        table.tokens.push_back(token);
                        table.identifiers.push_back(ident);
                    }
                    else if (strType) {
                        Identifier ident(word, str, funcType);
                        Token token(chain.type, lineNum, ident);
                        table.tokens.push_back(token);
                        table.identifiers.push_back(ident);
                    } else {
                        Identifier ident(word, undef, funcType);
                        Token token(chain.type, lineNum, ident);
                        table.identifiers.push_back(ident);
                        table.tokens.push_back(token);
                        identId = table.tokens.size();
                    }
                    intType = false;
                    funcType = false;
                    strType = false;
                    boolType = false;
                    break;
                }
                case 17: {
                    Identifier ident(word, i);
                    Token token(chain.type, lineNum, ident);
                    table.tokens.push_back(token);
                    table.identifiers.push_back(ident);
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

}
