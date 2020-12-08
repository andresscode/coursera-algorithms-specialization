#include <iostream>

int solve(const int n)
{
  if (n < 2)
    return n;
  int a = 0;
  int b = 1;
  for (int i = 2; i <= n; ++i) {
    int tmp = (a + b + 1) % 10;
    a = b;
    b = tmp;
  }
  return b;
}

int main()
{
  int n;
  std::cin >> n;
  std::cout << solve(n) << "\n";
  return 0;
}
