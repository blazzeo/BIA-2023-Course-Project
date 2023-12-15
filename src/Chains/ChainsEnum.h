#pragma once
#include "../fst/FST.h"
#include "../Lexer/newLexer.h"

#define IDENTIFIER Fst::CHAIN(3, Lexer::identifier, \
                Fst::NODE(156, \
Fst::RELATION('q',1),\
Fst::RELATION('w',1),\
Fst::RELATION('e',1),\
Fst::RELATION('r',1),\
Fst::RELATION('t',1),\
Fst::RELATION('y',1),\
Fst::RELATION('u',1),\
Fst::RELATION('i',1),\
Fst::RELATION('o',1),\
Fst::RELATION('p',1),\
Fst::RELATION('a',1),\
Fst::RELATION('s',1),\
Fst::RELATION('d',1),\
Fst::RELATION('f',1),\
Fst::RELATION('g',1),\
Fst::RELATION('h',1),\
Fst::RELATION('j',1),\
Fst::RELATION('k',1),\
Fst::RELATION('l',1),\
Fst::RELATION('z',1),\
Fst::RELATION('x',1),\
Fst::RELATION('c',1),\
Fst::RELATION('v',1),\
Fst::RELATION('b',1),\
Fst::RELATION('n',1),\
Fst::RELATION('m',1),\
Fst::RELATION('Q',1),\
Fst::RELATION('W',1),\
Fst::RELATION('E',1),\
Fst::RELATION('R',1),\
Fst::RELATION('T',1),\
Fst::RELATION('Y',1),\
Fst::RELATION('U',1),\
Fst::RELATION('I',1),\
Fst::RELATION('O',1),\
Fst::RELATION('P',1),\
Fst::RELATION('A',1),\
Fst::RELATION('S',1),\
Fst::RELATION('D',1),\
Fst::RELATION('F',1),\
Fst::RELATION('G',1),\
Fst::RELATION('H',1),\
Fst::RELATION('J',1),\
Fst::RELATION('K',1),\
Fst::RELATION('L',1),\
Fst::RELATION('Z',1),\
Fst::RELATION('X',1),\
Fst::RELATION('C',1),\
Fst::RELATION('V',1),\
Fst::RELATION('B',1),\
Fst::RELATION('N',1),\
Fst::RELATION('M',1),\
Fst::RELATION('q',2),\
Fst::RELATION('w',2),\
Fst::RELATION('e',2),\
Fst::RELATION('r',2),\
Fst::RELATION('t',2),\
Fst::RELATION('y',2),\
Fst::RELATION('u',2),\
Fst::RELATION('i',2),\
Fst::RELATION('o',2),\
Fst::RELATION('p',2),\
Fst::RELATION('a',2),\
Fst::RELATION('s',2),\
Fst::RELATION('d',2),\
Fst::RELATION('f',2),\
Fst::RELATION('g',2),\
Fst::RELATION('h',2),\
Fst::RELATION('j',2),\
Fst::RELATION('k',2),\
Fst::RELATION('l',2),\
Fst::RELATION('z',2),\
Fst::RELATION('x',2),\
Fst::RELATION('c',2),\
Fst::RELATION('v',2),\
Fst::RELATION('b',2),\
Fst::RELATION('n',2),\
Fst::RELATION('m',2),\
Fst::RELATION('Q',2),\
Fst::RELATION('W',2),\
Fst::RELATION('E',2),\
Fst::RELATION('R',2),\
Fst::RELATION('T',2),\
Fst::RELATION('Y',2),\
Fst::RELATION('U',2),\
Fst::RELATION('I',2),\
Fst::RELATION('O',2),\
Fst::RELATION('P',2),\
Fst::RELATION('A',2),\
Fst::RELATION('S',2),\
Fst::RELATION('D',2),\
Fst::RELATION('F',2),\
Fst::RELATION('G',2),\
Fst::RELATION('H',2),\
Fst::RELATION('J',2),\
Fst::RELATION('K',2),\
Fst::RELATION('L',2),\
Fst::RELATION('Z',2),\
Fst::RELATION('X',2),\
Fst::RELATION('C',2),\
Fst::RELATION('V',2),\
Fst::RELATION('B',2),\
Fst::RELATION('N',2),\
Fst::RELATION('M',2)),\
                Fst::NODE(124, \
Fst::RELATION('q',2),\
Fst::RELATION('w',2),\
Fst::RELATION('e',2),\
Fst::RELATION('r',2),\
Fst::RELATION('t',2),\
Fst::RELATION('y',2),\
Fst::RELATION('u',2),\
Fst::RELATION('i',2),\
Fst::RELATION('o',2),\
Fst::RELATION('p',2),\
Fst::RELATION('a',2),\
Fst::RELATION('s',2),\
Fst::RELATION('d',2),\
Fst::RELATION('f',2),\
Fst::RELATION('g',2),\
Fst::RELATION('h',2),\
Fst::RELATION('j',2),\
Fst::RELATION('k',2),\
Fst::RELATION('l',2),\
Fst::RELATION('z',2),\
Fst::RELATION('x',2),\
Fst::RELATION('c',2),\
Fst::RELATION('v',2),\
Fst::RELATION('b',2),\
Fst::RELATION('n',2),\
Fst::RELATION('m',2),\
Fst::RELATION('Q',2),\
Fst::RELATION('W',2),\
Fst::RELATION('E',2),\
Fst::RELATION('R',2),\
Fst::RELATION('T',2),\
Fst::RELATION('Y',2),\
Fst::RELATION('U',2),\
Fst::RELATION('I',2),\
Fst::RELATION('O',2),\
Fst::RELATION('P',2),\
Fst::RELATION('A',2),\
Fst::RELATION('S',2),\
Fst::RELATION('D',2),\
Fst::RELATION('F',2),\
Fst::RELATION('G',2),\
Fst::RELATION('H',2),\
Fst::RELATION('J',2),\
Fst::RELATION('K',2),\
Fst::RELATION('L',2),\
Fst::RELATION('Z',2),\
Fst::RELATION('X',2),\
Fst::RELATION('C',2),\
Fst::RELATION('V',2),\
Fst::RELATION('B',2),\
Fst::RELATION('N',2),\
Fst::RELATION('M',2),\
Fst::RELATION('q',1),\
Fst::RELATION('w',1),\
Fst::RELATION('e',1),\
Fst::RELATION('r',1),\
Fst::RELATION('t',1),\
Fst::RELATION('y',1),\
Fst::RELATION('u',1),\
Fst::RELATION('i',1),\
Fst::RELATION('o',1),\
Fst::RELATION('p',1),\
Fst::RELATION('a',1),\
Fst::RELATION('s',1),\
Fst::RELATION('d',1),\
Fst::RELATION('f',1),\
Fst::RELATION('g',1),\
Fst::RELATION('h',1),\
Fst::RELATION('j',1),\
Fst::RELATION('k',1),\
Fst::RELATION('l',1),\
Fst::RELATION('z',1),\
Fst::RELATION('x',1),\
Fst::RELATION('c',1),\
Fst::RELATION('v',1),\
Fst::RELATION('b',1),\
Fst::RELATION('n',1),\
Fst::RELATION('m',1),\
Fst::RELATION('Q',1),\
Fst::RELATION('W',1),\
Fst::RELATION('E',1),\
Fst::RELATION('R',1),\
Fst::RELATION('T',1),\
Fst::RELATION('Y',1),\
Fst::RELATION('U',1),\
Fst::RELATION('I',1),\
Fst::RELATION('O',1),\
Fst::RELATION('P',1),\
Fst::RELATION('A',1),\
Fst::RELATION('S',1),\
Fst::RELATION('D',1),\
Fst::RELATION('F',1),\
Fst::RELATION('G',1),\
Fst::RELATION('H',1),\
Fst::RELATION('J',1),\
Fst::RELATION('K',1),\
Fst::RELATION('L',1),\
Fst::RELATION('Z',1),\
Fst::RELATION('X',1),\
Fst::RELATION('C',1),\
Fst::RELATION('V',1),\
Fst::RELATION('B',1),\
Fst::RELATION('N',1),\
Fst::RELATION('M',1),\
Fst::RELATION('0',2),\
Fst::RELATION('1',2),\
Fst::RELATION('2',2),\
Fst::RELATION('3',2),\
Fst::RELATION('4',2),\
Fst::RELATION('5',2),\
Fst::RELATION('6',2),\
Fst::RELATION('7',2),\
Fst::RELATION('8',2),\
Fst::RELATION('9',2),\
Fst::RELATION('0',1),\
Fst::RELATION('1',1),\
Fst::RELATION('2',1),\
Fst::RELATION('3',1),\
Fst::RELATION('4',1),\
Fst::RELATION('5',1),\
Fst::RELATION('6',1),\
Fst::RELATION('7',1),\
Fst::RELATION('8',1),\
Fst::RELATION('9',1)),\
                Fst::NODE())
#define LITER Fst::CHAIN(3, Lexer::liter, \
    Fst::NODE(19, \
              Fst::RELATION('1',1), \
              Fst::RELATION('2',1), \
              Fst::RELATION('3',1), \
              Fst::RELATION('4',1), \
              Fst::RELATION('5',1), \
              Fst::RELATION('6',1), \
              Fst::RELATION('7',1), \
              Fst::RELATION('8',1), \
              Fst::RELATION('9',1), \
              Fst::RELATION('0',2), \
              Fst::RELATION('1',2), \
              Fst::RELATION('2',2), \
              Fst::RELATION('3',2), \
              Fst::RELATION('4',2), \
              Fst::RELATION('5',2), \
              Fst::RELATION('6',2), \
              Fst::RELATION('7',2), \
              Fst::RELATION('8',2), \
              Fst::RELATION('9',2)), \
    Fst::NODE(20, \
              Fst::RELATION('0',1), \
              Fst::RELATION('1',1), \
              Fst::RELATION('2',1), \
              Fst::RELATION('3',1), \
              Fst::RELATION('4',1), \
              Fst::RELATION('5',1), \
              Fst::RELATION('6',1), \
              Fst::RELATION('7',1), \
              Fst::RELATION('8',1), \
              Fst::RELATION('9',1), \
              Fst::RELATION('0',2), \
              Fst::RELATION('1',2), \
              Fst::RELATION('2',2), \
              Fst::RELATION('3',2), \
              Fst::RELATION('4',2), \
              Fst::RELATION('5',2), \
              Fst::RELATION('6',2), \
              Fst::RELATION('7',2), \
              Fst::RELATION('8',2), \
              Fst::RELATION('9',2)), \
    Fst::NODE())
#define MULTIPLY Fst::CHAIN(2, Lexer::multiply, \
                       Fst::NODE(1, Fst::RELATION('*',1)), \
                       Fst::NODE())
#define DIV Fst::CHAIN(2, Lexer::div, \
                       Fst::NODE(1, Fst::RELATION('/',1)), \
                       Fst::NODE())
#define SUM Fst::CHAIN(2, Lexer::sum, \
                       Fst::NODE(1, Fst::RELATION('+',1)), \
                       Fst::NODE())
#define SUB Fst::CHAIN(2, Lexer::sub, \
                       Fst::NODE(1, Fst::RELATION('-',1)), \
                       Fst::NODE())
#define COMMA Fst::CHAIN(2, Lexer::comma, \
                       Fst::NODE(1, Fst::RELATION(',',1)), \
                       Fst::NODE())
#define PRINT Fst::CHAIN(6, Lexer::print, \
                Fst::NODE(1, Fst::RELATION('p',1)), \
                Fst::NODE(1, Fst::RELATION('r',2)), \
                Fst::NODE(1, Fst::RELATION('i',3)), \
                Fst::NODE(1, Fst::RELATION('n',4)), \
                Fst::NODE(1, Fst::RELATION('t',5)), \
                Fst::NODE())
#define DECLARE Fst::CHAIN(4, Lexer::declare, \
                Fst::NODE(1, Fst::RELATION('l',1)), \
                Fst::NODE(1, Fst::RELATION('e',2)), \
                Fst::NODE(1, Fst::RELATION('t',3)), \
                Fst::NODE())
#define MAIN Fst::CHAIN(5, Lexer::main, \
                Fst::NODE(1, Fst::RELATION('m',1)), \
                Fst::NODE(1, Fst::RELATION('a',2)), \
                Fst::NODE(1, Fst::RELATION('i',3)), \
                Fst::NODE(1, Fst::RELATION('n',4)), \
                Fst::NODE())
#define SEMI Fst::CHAIN(2, Lexer::semi, \
                Fst::NODE(1, Fst::RELATION(';',1)), \
                Fst::NODE())
#define OPEN_APP_BRACKET Fst::CHAIN(2, Lexer::open_app_brackets, \
                Fst::NODE(1, Fst::RELATION('{',1)), \
                Fst::NODE())
#define CLOSE_APP_BRACKET Fst::CHAIN(2, Lexer::close_app_brackets, \
                Fst::NODE(1, Fst::RELATION('}',1)), \
                Fst::NODE())
#define OPEN_PARM_BRACKET Fst::CHAIN(2, Lexer::open_parm_brackets, \
                Fst::NODE(1, Fst::RELATION('(',1)), \
                Fst::NODE())
#define CLOSE_PARM_BRACKET Fst::CHAIN(2, Lexer::close_parm_brackets, \
                Fst::NODE(1, Fst::RELATION(')',1)), \
                Fst::NODE())
#define WHITESPACE Fst::CHAIN(2, Lexer::whitespace, \
                Fst::NODE(1, Fst::RELATION(' ',1)), \
                Fst::NODE())
#define FUNCTION Fst::CHAIN(3, Lexer::func, \
                Fst::NODE(1, Fst::RELATION('f',1)), \
                Fst::NODE(1, Fst::RELATION('n',2)), \
                Fst::NODE())
#define RETURN Fst::CHAIN(7, Lexer::ret, \
                Fst::NODE(1, Fst::RELATION('r',1)), \
                Fst::NODE(1, Fst::RELATION('e',2)), \
                Fst::NODE(1, Fst::RELATION('t',3)), \
                Fst::NODE(1, Fst::RELATION('u',4)), \
                Fst::NODE(1, Fst::RELATION('r',5)), \
                Fst::NODE(1, Fst::RELATION('n',6)), \
                Fst::NODE())
#define INT_LITER Fst::CHAIN(4, Lexer::integer, \
                Fst::NODE(1, Fst::RELATION('i',1)), \
                Fst::NODE(1, Fst::RELATION('3',2)), \
                Fst::NODE(1, Fst::RELATION('2',3)), \
                Fst::NODE())
#define STR_LITER Fst::CHAIN(7, Lexer::string, \
                Fst::NODE(1, Fst::RELATION('s',1)), \
                Fst::NODE(1, Fst::RELATION('t',2)), \
                Fst::NODE(1, Fst::RELATION('r',3)), \
                Fst::NODE(1, Fst::RELATION('i',4)), \
                Fst::NODE(1, Fst::RELATION('n',5)), \
                Fst::NODE(1, Fst::RELATION('g',6)), \
                Fst::NODE())
#define BOOL_LITER Fst::CHAIN(5, Lexer::bl, \
                Fst::NODE(1, Fst::RELATION('b',1)), \
                Fst::NODE(1, Fst::RELATION('o',2)), \
                Fst::NODE(1, Fst::RELATION('o',3)), \
                Fst::NODE(1, Fst::RELATION('l',4)), \
                Fst::NODE())
#define EQUALS Fst::CHAIN(2, Lexer::equals, \
                Fst::NODE(1, Fst::RELATION('=',1)), \
                Fst::NODE())
#define COLON Fst::CHAIN(2, Lexer::colon, \
                Fst::NODE(1, Fst::RELATION(':',1)), \
                Fst::NODE())
#define IF Fst::CHAIN(3, Lexer::condition, \
                Fst::NODE(1, Fst::RELATION('i',1)), \
                Fst::NODE(1, Fst::RELATION('f',2)), \
                Fst::NODE())
#define FOR Fst::CHAIN(4, Lexer::loop, \
                Fst::NODE(1, Fst::RELATION('f',1)), \
                Fst::NODE(1, Fst::RELATION('o',2)), \
                Fst::NODE(1, Fst::RELATION('r',3)), \
                Fst::NODE())
#define LESS Fst::CHAIN(2, Lexer::less, \
                Fst::NODE(1, Fst::RELATION('<',1)), \
                Fst::NODE())
#define GREATER Fst::CHAIN(2, Lexer::greater, \
                Fst::NODE(1, Fst::RELATION('>',1)), \
                Fst::NODE())
#define MOD Fst::CHAIN(2, Lexer::mod, \
                Fst::NODE(1, Fst::RELATION('%',1)), \
                Fst::NODE())
#define OPEN_SQUARE Fst::CHAIN(2, Lexer::open_priority, \
                Fst::NODE(1, Fst::RELATION('[',1)), \
                Fst::NODE())
#define CLOSE_SQUARE Fst::CHAIN(2, Lexer::close_priority, \
                Fst::NODE(1, Fst::RELATION(']',1)), \
                Fst::NODE())
#define EQUAL Fst::CHAIN(3, Lexer::equal, \
                Fst::NODE(1, Fst::RELATION('=',1)), \
                Fst::NODE(1, Fst::RELATION('=',2)), \
                Fst::NODE())
#define NEQUAL Fst::CHAIN(3, Lexer::nequal, \
                Fst::NODE(1, Fst::RELATION('!',1)), \
                Fst::NODE(1, Fst::RELATION('=',2)), \
                Fst::NODE())
