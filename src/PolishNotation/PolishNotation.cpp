#include "PolishNotation.h"
#include <iostream>
#include <map>
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
  {Lexer::semi, -3},           {Lexer::comma, -2}, {Lexer::open_prioirity, 1},
  {Lexer::close_priority, -1}, {Lexer::sum, 2},    {Lexer::sub, 2},
  {Lexer::multiply, 3},        {Lexer::div, 3},
};

map<Lexer::TokenType, char> operators = {
  {Lexer::sum, '+'},
  {Lexer::sub, '-'},
  {Lexer::multiply, '*'},
  {Lexer::div, '/'},
};

bool checkNotation(Lexer::Table &table, int id) {
  bool fnFlag = false;
  string result{};
  queue<Lexer::Token> queue;
  stack<Lexer::Token> stack;
  int start = id, end = id;
  Lexer::Token token = table.tokens[id];
  do {
    switch (table.tokens[id].type) {
      case Lexer::identifier: {
        if (table.tokens[id].identifier->isFunc) {
          fnFlag = true;
          stack.push(table.tokens[id]);
        } else {
          if (fnFlag) {
            stack.push(table.tokens[id]);
          } else {
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
            return false;
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

  printTable(table, start - 3, end + 3);
  size_t quSize = queue.size();
  for (size_t i = start; i < end - quSize; i++) {
    if (!queue.empty()) {
      table.tokens[i] = queue.front();
      queue.pop();
    }   
  }
  for (size_t i = end - quSize, j = end - quSize; i < end; i++)
      table.tokens.erase(table.tokens.begin()+j);
  printTable(table, start - 3, end + 3);
  return true;
}
