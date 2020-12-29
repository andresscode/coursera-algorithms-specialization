#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int solve(std::vector<int> &v)
{
  if (v.size() < 3)
    return 0;
  int sum = std::accumulate(v.begin(), v.end(), 0);
  if (sum % 3 != 0)
    return 0;
  std::vector<std::vector<int>> m(sum+1, std::vector<int> (v.size()+1, 0));
  for (size_t i = 1; i <= sum; ++i) {
    for (size_t j = 1; j <= v.size(); ++j) {
      m[i][j] = m[i][j-1];
      int wi = v[j-1];
      int t = i - wi;
      if (wi <= sum && t >= 0) {
        int tmp = m[t][j-1] + v[j-1];
        if (m[i][j] < tmp)
          m[i][j] = tmp;
      }
    }
  }
  return m[sum/3][v.size()] == sum/3
         && m[sum*2/3][v.size()] == sum*2/3
         && m[sum][v.size()] == sum ? 1 : 0;
}

int main()
{
  int n;
  std::cin >> n;
  std::vector<int> v(n);
  for (size_t i = 0; i < n; ++i)
    std::cin >> v[i];
  std::cout << solve(v) << "\n";
  return 0;
}
