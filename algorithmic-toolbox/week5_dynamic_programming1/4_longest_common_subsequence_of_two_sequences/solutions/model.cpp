#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int lcs2(vector<int> &a, vector<int> &b) {
  int m[b.size()+1][a.size()+1];
  std::fill(m[0], m[0] + (b.size()+1) * (a.size()+1), 0);
  for (size_t i = 1; i <= b.size(); ++i) {
    for (size_t j = 1; j <= a.size(); ++j) {
      int indel = std::max(m[i-1][j], m[i][j-1]);
      if (indel > m[i-1][j-1])
        m[i][j] = indel;
      else
        m[i][j] = a[j-1] == b[i-1] ? 1 + m[i-1][j-1] : m[i-1][j-1];
    }
  }
  return m[b.size()][a.size()];
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
