#pragma once
#include "GRB.h"

#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n) GRB::Rule::Chain::isN(n)

namespace GRB {
Greibach greibach(
    NS('S'), TS('$'), // стартовый символ, дно стека
    {Rule(NS('S'),
          GRB_ERROR_SERIES +
              0, // Неверная структура программы
                 // S →	m:t{NrE;};	|	fi:t(F){NrE;};S	|
                 // m:t{NrE;};S	|	fi:t(F){NrE;}; | i{NrE;}
          {Rule::Chain({TS('f'), TS('i'), TS(':'), TS('t'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')}),
           Rule::Chain({TS('m'), TS(':'), TS('t'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')}),
           Rule::Chain({TS('i'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')}),
           Rule::Chain({TS('f'), TS('i'), TS(':'), TS('t'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')}),
           Rule::Chain({TS('m'), TS(':'), TS('t'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')}),
           Rule::Chain({TS('f'), TS('i'), TS(':'), TS('t'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')})}),
     Rule(NS('N'),
          GRB_ERROR_SERIES + 1, // Операторы программы
                 // N	→	di:t; | rE; | i = E; | fi:t(F); | di:t;N | rE;N
                 // | i=E;N | fi:t(F);N | pE; | pE;N | ?(E){N}; | @(Z){N};
          {
              Rule::Chain({TS('d'), TS('i'), TS(':'), TS('t'), TS('='), TS('E'), TS(';')}),
              Rule::Chain({TS('d'), TS('i'), TS(':'), TS('t'), TS(';')}),
              Rule::Chain({TS('i'), TS('='), NS('E'), TS(';')}),
              Rule::Chain({TS('r'), NS('E'), TS(';')}),
              Rule::Chain({TS('f'), TS('i'), TS(':'), TS('t'), TS('('), NS('F'), TS(')'), TS(';')}),
              Rule::Chain({TS('d'), TS('i'), TS(':'), TS('t'), TS(';'), NS('N')}),
              Rule::Chain({TS('d'), TS('i'), TS(':'), TS('t'), TS('='), TS('E'), TS(';'), NS('N')}),
              Rule::Chain({TS('r'), NS('E'), TS(';'), NS('N')}),
              Rule::Chain({TS('i'), TS('='), NS('E'), TS(';'), NS('N')}),
              Rule::Chain({TS('f'), TS('i'), TS(':'), TS('t'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')}),
              Rule::Chain({TS('p'), NS('E'), TS(';')}),
              Rule::Chain({TS('p'), NS('E'), TS(';'), NS('N')}),
              Rule::Chain({TS('?'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')}), // IF
              Rule::Chain({TS('@'), TS('('), NS('Z'), TS(';'), NS('Z'), TS(';'), NS('Z'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')}), // FOR
              Rule::Chain({TS('?'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('N')}), // IF
              Rule::Chain({TS('@'), TS('('), NS('Z'), TS(';'), NS('Z'), TS(';'), NS('Z'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('N')}) // IF
          }),
     Rule(NS('E'),
          GRB_ERROR_SERIES + 2, // Выражение
                                // E →	i	|	l	|	(E)
                                // |	i(W)	|	iM	|	lM
                                // |	(E)M	|	i(W)M|	i()
          {Rule::Chain({TS('i')}), Rule::Chain({TS('l')}),
           Rule::Chain({TS('('), NS('E'), TS(')')}),
           Rule::Chain({TS('i'), TS('('), NS('W'), TS(')')}),
           Rule::Chain({TS('i'), TS('('), TS(')')}),
           Rule::Chain({TS('i'), NS('M')}), Rule::Chain({TS('l'), NS('M')}),
           Rule::Chain({TS('('), NS('E'), TS(')'), NS('M')}),
           Rule::Chain({TS('i'), TS('('), NS('W'), TS(')'), NS('M')})}),
     Rule(NS('W'), GRB_ERROR_SERIES + 3, // Подвыражение
                                         // W	→	i	|	l
                                         // |	i,W	|	l,W
          {Rule::Chain({TS('i')}), Rule::Chain({TS('l')}),
           Rule::Chain({TS('i'), TS(','), NS('W')}),
           Rule::Chain({TS('l'), TS(','), NS('W')})}),
     Rule(NS('F'), GRB_ERROR_SERIES + 4, // Параметры функции
                                         // F	→	ti	|	ti,F
          {Rule::Chain({TS('i'), TS(':'), TS('t')}),
           Rule::Chain({TS('i'), TS(':'), TS('t'), TS(','), NS('F')})}),
     Rule(NS('M'), GRB_ERROR_SERIES + 7, // M Error
                  // M →		vE	|	vEM   |   ==E | !=E
          {
              Rule::Chain({TS('v'), NS('E')}),
              Rule::Chain({TS('v'), NS('E'), NS('M')}),
              Rule::Chain({TS('='), TS('='), NS('E')}),
              Rule::Chain({TS('!'), TS('='), NS('E')}),
          }),
     Rule(NS('Z'), GRB_ERROR_SERIES + 8, // Ошибка в условии цикла
          // Z ->      di:t=E | di:t=E,Z | i=E
          {Rule::Chain({TS('d'), TS('i'), TS(':'), TS('t'), TS('='), NS('E')}),
           Rule::Chain({TS('d'), TS('i'), TS(':'), TS('t'), TS('='), NS('E'), TS(','), NS('Z')}),
           Rule::Chain({TS('i'), TS('='), NS('E')})})});
}
