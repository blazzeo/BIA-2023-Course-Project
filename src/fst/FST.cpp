#include <utility>
#include "FST.h"
#include "iostream"
#include <algorithm>
#include <cstring>
#include "memory"

using namespace std;

namespace Fst
{
RELATION::RELATION(char ch, short sh) : symbol(ch), nnode(sh) {}

bool step(FST& fst, short* &rstates) {
    bool flag = false;
    std::swap(rstates, fst.rstates);
    for (short state = 0; state < fst.nstates; state++) {
        if (rstates[state] == fst.position)
            for (short j = 0; j < fst.nodes[state].n_relation; j++) {
                if (fst.nodes[state].relations[j].symbol == fst.string[fst.position]) {
                    fst.rstates[fst.nodes[state].relations[j].nnode] = fst.position + 1;
                    flag = true;
                }
            }
    }
    return flag;
}

bool execute(FST& fst) {
    short* rstates = new short[fst.nstates];
    // std::cout << fst.string << std::endl;
    fill_n(rstates, fst.nstates, -1);
    bool flag = true;
    short lstring = strlen(fst.string);

    for (short i=0; i < lstring && flag; i++) {
        fst.position++;
        flag = step(fst, rstates);
    }
    delete[] rstates;
    return (flag?(fst.rstates[fst.nstates-1] == lstring):flag);
}
}
