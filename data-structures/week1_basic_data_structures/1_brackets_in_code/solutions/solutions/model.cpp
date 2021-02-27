#include <iostream>
#include <stack>
#include <string>

bool is_open_bracket(const char c) {
  return c == '[' || c == '{' || c == '(';
}

bool is_closing_bracket(const char c) {
  return c == ']' || c == '}' || c == ')';
}

bool match(const char opening, const char closing) {
  switch (closing) {
    case ']':
      return opening == '[';
    case '}':
      return opening == '{';
    case ')':
      return opening == '(';
    default:
      return false;
  }
}

int find_error(const std::string &str) {
  std::stack<char> brackets;
  std::stack<int> indices;
  for (size_t i = 0; i < str.length(); ++i) {
    //@log std::cout << "char=" << str.at(i) << "\n";
    if (is_open_bracket(str.at(i))) {
      brackets.push(str.at(i));
      indices.push(i);
      //@log std::cout << "added=" << str.at(i) << ", index=" << i << "\n";
    } else if (is_closing_bracket(str.at(i))) {
      if (brackets.empty()) {
        //@log std::cout << "stack empty\n";
        return i;
      }
      char tmp = brackets.top();
      int ind = indices.top();
      brackets.pop();
      indices.pop();
      //@log std::cout << "matching: " << tmp << " " << str.at(i) << "\n";
      if (!match(tmp, str.at(i)))
        return i;
    }
  }
  return brackets.empty() ? -1 : indices.top();
}

void solve(const std::string &str) {
  int result = find_error(str) + 1;
  if (result > 0)
    std::cout << result << "\n";
  else
    std::cout << "Success\n";
}

int main() {
  std::string str;
  std::cin >> str;
  solve(str);
  return 0;
}
