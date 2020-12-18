#include <iostream>
#include <vector>

int solve(const std::vector<int> &v)
{
  for (size_t i = 0; i < v.size(); ++i) {
    int e = v[i];
    int c = 0;
    for (size_t j = 0; j < v.size(); ++j)
      if (v[j] == e) c++;
    if (c > v.size() / 2)
      return 1;
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
