#include <iostream>
#include <vector>
#include <algorithm>

int solve(std::vector<int> &v)
{
  std::sort(v.begin(), v.end());
  int mid = v.size() / 2;
  int end = mid;
  if (v.size() % 2 == 0) {
    for (size_t i = 0; i < mid; ++i) {
      if (v[i] == v[end++])
        return 1;
    }
  } else {
    for (size_t i = 0; i <= mid; ++i) {
      if (v[i] == v[end++])
        return 1;
    }
  }
  return 0;
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
