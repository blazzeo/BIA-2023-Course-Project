#pragma once
#include "../Chains/ChainsEnum.h"
#include "../Lexer/newLexer.h"

namespace Fst {
struct RELATION
{
    char symbol;
    short nnode;
    RELATION (
        char c = 0x00,
        short ns = 0
    );
};

struct NODE
{
    short n_relation;
    RELATION *relations;
    NODE() = default;
    template<typename... Args>
    NODE(short num, Args... args): n_relation(num) {
        relations = new RELATION[num]{args...};
    }
};

struct CHAIN {
    Lexer::TokenType type;
    short statesNum;
    Fst::NODE* nodes;

    template<typename... Args>
    CHAIN(short sn, Lexer::TokenType tp, Args... args) : statesNum(sn), type(tp) {
        nodes = new Fst::NODE[sn] {args...};
    }
};

struct FST
{
    char* string;
    short position;
    short nstates;
    NODE* nodes;
    short* rstates;
    short length;
    template<typename... Args>
    FST(const char* s, short ns, Args... args) : nstates(ns) {
        string = new char[strlen(s)+1];
        strcpy(string, s);
        nodes = new NODE[ns] {args...};
        rstates = new short[nstates];
        std::fill_n(rstates, nstates, -1);
        rstates[0] = 0;
        position = -1;
        length = ns;
    }
    FST(const char* s, CHAIN ch) : nstates(ch.statesNum) {
        string = new char[strlen(s)+1];
        strcat(string, s);
        nodes = ch.nodes;
        rstates = new short[ch.statesNum];
        std::fill_n(rstates, nstates, -1);
        rstates[0] = 0;
        position = -1;
        length = ch.statesNum;
    }
    FST(const char s, CHAIN ch) : nstates(ch.statesNum) {
        string = new char[2]{s};
        // string += s;
        nodes = ch.nodes;
        rstates = new short[ch.statesNum];
        std::fill_n(rstates, nstates, -1);
        rstates[0] = 0;
        position = -1;
        length = ch.statesNum;
    }
};

bool execute(FST& fst);
};
