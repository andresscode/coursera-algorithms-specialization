#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> solve(int n)
{
  std::vector<int> seq;
  std::vector<int> a(n+1, 0);

  for (size_t i = 1; i <= n; ++i) {
    a[i] = a[i-1] + 1;
    if (i % 2 == 0) a[i] = std::min(a[i/2]+1, a[i]);
    if (i % 3 == 0) a[i] = std::min(a[i/3]+1, a[i]);
  }

  int i = n;
  while (i > 1) {
    seq.push_back(i);
    if (a[i-1] == a[i] - 1)
      i = i - 1;
    else if (i%2 == 0 && a[i/2] == a[i]-1)
      i = i / 2;
    else if (i%3 == 0 && a[i/3] == a[i]-1)
      i = i / 3;
  }

  seq.push_back(1);
  std::reverse(seq.begin(), seq.end());

  return seq;
}

int main()
{
  int n;
  std::cin >> n;
  std::vector<int> r = solve(n);
  std::cout << r.size() - 1 << "\n";
  for (int num : r)
    std::cout << num << " ";
  std::cout << "\n";
  return 0;
}
