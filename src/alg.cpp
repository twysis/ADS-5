// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int calculator(char operatorr, int a, int b) {
switch (operatorr) {
  case '+': return (b + a);
  case '-': return (b - a);
  case '*': return (b * a);
  case '/':
    if (a != 0)
      return b / a;
  default: return 0;
  }
}

int priority(char operatorr) {
switch (operatorr) {
  case '(': return 0;
  case ')': return 1;
  case '+': return 2;
  case '-': return 2;
  case '/': return 3;
  case '*': return 3;
  case ' ': return 5;
  default: return 4;
  }
}

std::string infx2pstfx(std::string inf) {
  std::string result;
  char space = ' ';
  TStack <char, 100> stack;
  for (int i = 0; i < inf.size(); i++) {
    if (priority(inf[i]) == 4) {
    result.push_back(inf[i]);
    result.push_back(space);
    } else {
      if (priority(inf[i]) == 0) {
        stack.push(inf[i]);
    } else if (stack.isEmpty()) {
      stack.push(inf[i]);
    } else if ((priority(inf[i]) > priority(stack.get()))) {
      stack.push(inf[i]);
  } else if (priority(inf[i]) == 1) {
  while (priority(stack.get()) != 0) {
    result.push_back(stack.get());
    result.push_back(space);
    stack.pop();
  }
  stack.pop();
  } else {
    while (!stack.isEmpty() && (priority(inf[i]) <= priority(stack.get()))) {
      result.push_back(stack.get());
      result.push_back(space);
      stack.pop();
  }
  stack.push(inf[i]);
    }
  }
}
while (!stack.isEmpty()) {
  result.push_back(stack.get());
  result.push_back(space);
  stack.pop();
}
for (int j = 0; j < result.size(); j++) {
  if (result[result.size() - 1] == ' ')
  result.erase(result.size() - 1);
}
return result;
}

int eval(std::string pref) {
  TStack <int, 100> stack1;
  int result = 0;
  for (int i = 0; i < pref.size(); i++) {
    if (priority(pref[i]) == 4) {
      stack1.push(pref[i] - '0');
  } else if (priority(pref[i]) < 4) {
    int n = stack1.get();
    stack1.pop();
    int f = stack1.get();
    stack1.pop();
    stack1.push(calculator(pref[i], n, f));
  }
}
result = stack1.get();
return result;
}
