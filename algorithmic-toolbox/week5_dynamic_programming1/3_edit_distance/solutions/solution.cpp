#include <iostream>
#include <string>
#include <vector>
#include <limits>

using std::string;

int solve(
  const std::vector<std::vector<int>> &v,
  int i,
  int j,
  const string &s1,
  const string &s2) {
  int min = v[i][j-1];
  if (v[i-1][j] < min) min = v[i-1][j];
  if (v[i-1][j-1] < min) min = v[i-1][j-1];
  return s1.at(j-1) == s2.at(i-1) ? min : min + 1;
}

int nav(
  const std::vector<std::vector<int>> &v,
  int i,
  int j,
  const string &s1,
  const string &s2) {
  int dist = 0;
  while (i != 0 || j != 0) {
    int min = std::numeric_limits<int>::max();
    int ix = i;
    int jx = j;
    if (j-1 >= 0) {
      min = v[i][j-1];
      ix = i;
      jx = j-1;
    }
    if (i-1 >= 0 && v[i-1][j] < min) {
      min = v[i-1][j];
      ix = i-1;
      jx = j;
    }
    if (i-1 >= 0 && j-1 >= 0 && v[i-1][j-1] <= min) {
      min = v[--i][--j];
      dist += s2[i] == s1[j] ? 0 : 1;
    } else {
      dist++;
      i = ix;
      j = jx;
    }
  }
  //return i == 0 && j == 0 ? dist : dist+1;
  return dist;
}

int edit_distance(const string &str1, const string &str2) {
  std::vector<std::vector<int>> cache(str2.length()+1, std::vector<int>(str1.length()+1));
  for (size_t i = 0; i <= str1.length(); ++i)
    cache[0][i] = i;
  for (size_t i = 1; i <= str2.length(); ++i)
    cache[i][0] = i;
  for (size_t i = 1; i <=str2.length(); ++i) {
    for (size_t j = 1; j <= str1.length(); ++j)
      cache[i][j] = solve(cache, i, j, str1, str2);
  }
  return nav(cache, str2.length(), str1.length(), str1, str2);
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
