#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool is_greater_or_equal(const string &a, const string &b) {
  return stoi(a + b) >= stoi(b + a);
}

string largest_number(vector<string> a) {
  if (a.size() == 1)
    return a[0];
  std::stringstream ret;
  while (!a.empty()) {
    string max = "0";
    int index = 0;
    for (size_t i = 0; i < a.size(); ++i) {
      if (is_greater_or_equal(a[i], max)) {
        max = a[i];
        index = i;
      }
    }
    ret << max;
    a.erase(a.begin() + index);
  }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
