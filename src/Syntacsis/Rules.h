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
        GRB_ERROR_SERIES + 0, // Неверная структура программы
        // S →	m:t{NrE;};|	fi:t(F){NrE;};S	|
        // m:t{NrE;};S	|	fi:t(F){NrE;}; | i{NrE;}
        {
        Rule::Chain(grb("fi:t(F){NrE;};S")),
        Rule::Chain(grb("fi:t(F){rE;};S")),
        Rule::Chain(grb("di:t=E;S")),
        Rule::Chain(grb("di:t;S")),
        Rule::Chain(grb("di[l]:t=E;S")),
        Rule::Chain(grb("di[l]:t;S")),
        Rule::Chain(grb("m:t{NrE;};")),
        Rule::Chain(grb("m:t{rE;};")),
        }
        ),
    Rule(NS('N'),
         GRB_ERROR_SERIES + 1, // Операторы программы
         // N	→	di:t; | rE; | i = E; | fi:t(F); | di:t;N | rE;N
         // | i=E;N | fi:t(F);N | pE; | pE;N | ?(E){N}; | @(Z){N};
         {
         Rule::Chain(grb("di[l]:t=E;")),
         Rule::Chain(grb("di:t=E;")),
         Rule::Chain(grb("di[l]:t;")),
         Rule::Chain(grb("di:t;")),
         Rule::Chain(grb("i=E;")),
         Rule::Chain(grb("i=E;N")),
         Rule::Chain(grb("fi:t(F);")),
         Rule::Chain(grb("fi:t(F);N")),
         Rule::Chain(grb("di[l]:t;N")),
         Rule::Chain(grb("di:t;N")),
         Rule::Chain(grb("di:t=E;N")),
         Rule::Chain(grb("di[l]:t=E;N")),
         Rule::Chain(grb("rE;")),
         Rule::Chain(grb("pE;")),
         Rule::Chain(grb("pE;N")),
         Rule::Chain(grb("?(ivi){N};")),
         Rule::Chain(grb("?(i){N};")),
         Rule::Chain(grb("?(ivl){N};")),
         Rule::Chain(grb("?(lvl){N};")),
         Rule::Chain(grb("?(lvi){N};")),
         // Rule::Chain({TS('@'), TS('('), NS('Z'), TS(';'), NS('Z'), TS(';'), NS('Z'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')}), // FOR
         Rule::Chain(grb("?(E){N};N")),
         // Rule::Chain({TS('@'), TS('('), NS('Z'), TS(';'), NS('Z'), TS(';'), NS('Z'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('N')}) // FOR
         }),
    Rule(NS('E'),
         GRB_ERROR_SERIES + 2, // Выражение
         // E →	i	|	l	|	(E)
         // |	i(W)	|	iM	|	lM
         // |	(E)M	|	i(W)M|	i()
         // |  'l'
         {
         Rule::Chain(grb("i")), 
         Rule::Chain(grb("l")),
         Rule::Chain(grb("(E)")),
         Rule::Chain(grb("i(W)")),
         Rule::Chain(grb("i()")),
         Rule::Chain(grb("iM")),
         Rule::Chain(grb("lM")),
         Rule::Chain(grb("(E)M")),
         Rule::Chain(grb("i(W)M"))
         }),
    Rule(NS('W'), GRB_ERROR_SERIES + 3, // Подвыражение
         // W	→	i	|	l
         //     |	i,W	|	l,W
         {
         Rule::Chain(grb("i")),
         Rule::Chain(grb("l")),
         Rule::Chain(grb("i,W")),
         Rule::Chain(grb("l,W"))
         }),
    Rule(NS('F'), GRB_ERROR_SERIES + 4, // Параметры функции
         // F	→	i:t |	i:t,F
         {
         Rule::Chain(grb("i:t")),
         Rule::Chain(grb("i:t,F")),
         }),
    Rule(NS('M'), GRB_ERROR_SERIES + 6, // M Error
         // M →	vE | vEM | ==E | !=E
         {
         Rule::Chain(grb("vE")),
         Rule::Chain(grb("vEM")),
         Rule::Chain(grb("==E")),
         Rule::Chain(grb("!=E")),
         }),
    // Rule(NS('Z'), GRB_ERROR_SERIES + 7, // Ошибка в условии цикла
    //      // Z -> di:t=E | di:t=E,Z | i=E
    //      {
    //      Rule::Chain(grb("di:t=E")),
    //      Rule::Chain(grb("di:t=E,Z")),
    //      Rule::Chain(grb("i=E"))
    //      })
  });
}
