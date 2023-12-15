#include "PolishNotation.h"
#include "../Error/Error.h"
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void printTable(Lexer::Table &table, size_t start, size_t end) {
  for (size_t i = start; i <= end; i++) {
    if (table.tokens[i].identifier && table.tokens[i].identifier->isFunc) {
      cout << "@ ";
    } else cout << table.tokens[i].lexema << ' ';
  }
  cout << endl;
}

map<Lexer::TokenType, int> priority = {
  {Lexer::semi, -3},           {Lexer::comma, -2}, {Lexer::open_parm_brackets, 1},
  {Lexer::close_parm_brackets, -1}, {Lexer::sum, 2},    {Lexer::sub, 2},
  {Lexer::multiply, 3},        {Lexer::div, 3},    {Lexer::mod, 3},
};

map<Lexer::TokenType, char> operators = {
  {Lexer::sum, '+'},
  {Lexer::sub, '-'},
  {Lexer::multiply, '*'},
  {Lexer::div, '/'},
  {Lexer::mod, '%'}
};

bool checkParm(shared_ptr<Lexer::Identifier> &fn, Lexer::Token &token, short id) {
  // switch (token.type) {
  //   case Lexer::identifier: 
  //     break;
  //   case Lexer::liter:
  //     break;
  // }
  if (fn->parms[id].type != token.identifier->type) {
    return false;
  }
  return true;
}

Lexer::ValueType checkNotation(Lexer::Table &table, int id) {
  string result{};
  queue<Lexer::Token> queue;
  stack<Lexer::Token> stack;

  shared_ptr<Lexer::Identifier> fn;
  bool fnFlag = false;
  short parm_id = 0;
  short parm_size = 0;

  Lexer::ValueType returnType = Lexer::undef;
  int start = id, end = id;
  Lexer::Token token = table.tokens[id];
  do {
    switch (table.tokens[id].type) {
      case Lexer::identifier: {
        if (table.tokens[id].identifier->isFunc) {  // IF FUNC
          fn = table.tokens[id].identifier;
          parm_size = fn->parms.size();
          if(returnType == Lexer::undef) {
            cout << "1 RT: " << table.tokens[id].identifier->type << endl;
            returnType = table.tokens[id].identifier->type;
          } else {
            if (returnType != table.tokens[id].identifier->type)
              return Lexer::undef;
          }
          fnFlag = true;
          stack.push(table.tokens[id]);
        } else {                                    // IF NOT FUNC
          if (fnFlag) {
            if(checkParm(fn, table.tokens[id], parm_id))
              stack.push(table.tokens[id]);
            else throw ERROR_THROW(406);
            ++parm_id;
          } else {
            if(returnType == Lexer::undef) {
              cout << "2 RT: " << table.tokens[id].identifier->type << endl;
              returnType = table.tokens[id].identifier->type;
            } else {
              if (returnType != table.tokens[id].identifier->type) {
            cout << "3 RT: " << table.tokens[id].identifier->type << endl;
                return Lexer::undef;
              }
            }
            result += table.tokens[id].identifier->name;
            queue.push(table.tokens[id]);
            result += ' ';
          }
        }
        break;
      }
      case Lexer::liter: {
        result += table.tokens[id].value;
        queue.push(table.tokens[id]);
        result += ' ';
        break;
      }
      case Lexer::multiply:
      case Lexer::sum:
      case Lexer::sub:
      case Lexer::mod:
      case Lexer::div: {
        if (stack.empty()) {
          stack.push(table.tokens[id]);
        } else {
          if (priority[stack.top().type] <
            priority[table.tokens[id].type]) {
            stack.push(table.tokens[id]);
          } else {
            while (!stack.empty() &&
              priority[stack.top().type] >=
              priority[table.tokens[id].type]) {
              result += operators[stack.top().type];
              queue.push(stack.top());
              stack.pop();
            }
            stack.push(table.tokens[id]);
          }
        }
        break;
      }
      case Lexer::open_parm_brackets: {
        stack.push(table.tokens[id]);
        break;
      }
      case Lexer::close_parm_brackets: {
        do {
          if (stack.empty())
            return Lexer::undef;
          if (stack.top().type != Lexer::open_parm_brackets) {
            if (stack.top().type == Lexer::identifier) {
              result += stack.top().identifier->name;
              queue.push(stack.top());
            } else {
              result += operators[stack.top().type];
              queue.push(stack.top());
            }
            stack.pop();
          }
        } while (!stack.empty() &&
        stack.top().type != Lexer::open_parm_brackets);
        stack.pop();
        if (fnFlag) {
          result += "@";
          result += stack.top().identifier->name;
          queue.push(stack.top());
          result += ' ';
          fnFlag = false;
          fn = nullptr;
          stack.pop();
        }
        break;
        while(!stack.empty())
          if (stack.top().type == Lexer::identifier) {
            result += stack.top().identifier->name;
            queue.push(stack.top());
          } else {
            result += operators[stack.top().type];
            queue.push(stack.top());
          }
      }
    };
    ++id;
  } while (table.tokens[id].type != Lexer::semi);
  end = id;
  while (!stack.empty()) {
    result += operators[stack.top().type];
    queue.push(stack.top());
    stack.pop();
  }
  cout << "Result: " << result << endl;

  printTable(table, start - 2, end + 2);
  size_t quSize = queue.size();
  // for (size_t i = start; i < end - quSize; i++) {
  size_t i = start;
    while (!queue.empty()) {
      table.tokens[i++] = queue.front();
      queue.pop();
    }   
  if (i < end)
    for (size_t ii = end - quSize, j = end - quSize; ii < end; ii++)
      table.tokens.erase(table.tokens.begin()+j);
  printTable(table, start - 2, end + 2);
  return returnType;
}
