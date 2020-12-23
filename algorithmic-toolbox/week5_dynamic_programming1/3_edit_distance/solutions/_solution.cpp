#include <iostream>
#include <string>
#include <vector>
#include <limits>

using std::string;

int edit_distance(const string &str1, const string &str2, int m, int n) {
  int matrix[m+1][n+1];
  for (size_t i = 0; i <= m; ++i) {
    for (size_t j = 0; j <= n; ++j) {
      if (i == 0)
        matrix[i][j] = j;
      else if (j == 0)
        matrix[i][j] = i;
      else if (str1[i-1] == str2[j-1])
        matrix[i][j] = matrix[i-1][j-1];
      else
        matrix[i][j] = 1 + std::min(std::min(matrix[i][j-1], matrix[i-1][j]),
                                    matrix[i-1][j-1]);
    }
  }
  return matrix[m][n];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2, str1.length(), str2.length()) << std::endl;
  return 0;
}
