#include <iostream>

int solve(int m)
{
  int k = m;
  int n = 0;
  int tens = k / 10;
  k -= tens * 10;
  int fives = k / 5;
  k -= fives * 5;
  int ones = k / 1;
  k -= ones * 1;
  return tens + fives + ones;
}

int main()
{
  int m;
  std::cin >> m;
  std::cout << solve(m) << "\n";
  return 0;
}
