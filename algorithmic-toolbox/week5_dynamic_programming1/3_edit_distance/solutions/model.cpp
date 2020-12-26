#include <iostream>
#include <string>
#include <vector>
#include <limits>

using std::string;

int edit_distance(const string &str1, const string &str2, int m, int n) {
  if (m == 0)
    return n;
  if (n == 0)
    return m;
  if (str1.at(m-1) == str2.at(n-1))
    return edit_distance(str1, str2, m-1, n-1);
  return 1 + std::min(std::min(edit_distance(str1, str2, m, n-1),
                               edit_distance(str1, str2, m-1, n)),
                      edit_distance(str1, str2, m-1, n-1));
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2, str1.length(), str2.length()) << std::endl;
  return 0;
}
