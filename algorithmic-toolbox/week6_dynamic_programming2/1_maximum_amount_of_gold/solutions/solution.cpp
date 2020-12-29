#include <iostream>
#include <vector>

int solve(int w, const std::vector<int> &v)
{
  std::vector<std::vector<int>> m(w+1, std::vector<int> (v.size()+1, 0));
  for (size_t i = 0; i <= w; ++i) {
    for (size_t j = 0; j <= v.size(); ++j) {
      if (i == 0 || j == 0) {
        m[i][j] = 0;
        continue;
      }
      m[i][j] = m[i][j-1];
      int wi = v[j-1];
      int t = i - wi;
      if (wi <= w && t >= 0) {
        int tmp = m[t][j-1] + v[j-1];
        if (m[i][j] < tmp)
          m[i][j] = tmp;
      }
    }
  }
  return m[w][v.size()];
}

int main()
{
  int w;
  std:: cin >> w;
  int n;
  std::cin >> n;
  std::vector<int> v(n);
  for (size_t i = 0; i < n; ++i)
    std::cin >> v[i];
  std::cout << solve(w, v) << "\n";
  return 0;
}
