#include <iostream>
#include <vector>

typedef long long ll;

ll solve(std::vector<int> &v)
{
  ll count = 0;
  for (size_t i = 0; i < v.size() - 1; ++i) {
    for (size_t j = i+1; j < v.size(); ++j) {
      if (v[i] > v[j])
        count++;
    }
  }
  return count;
}
      
int main()
{
  int n;
  std::cin >> n;
  std::vector<int> v(n);
  for (size_t i = 0; i < n; ++i)
    std::cin >> v[i];
  std::cout << solve(v);
  return 0;
}
