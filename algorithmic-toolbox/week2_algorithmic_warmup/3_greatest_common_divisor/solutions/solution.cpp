#include <iostream>

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  int tmp = a % b;
  return gcd(b, tmp);
}

int main()
{
  int a, b;
  std::cin >> a;
  std::cin >> b;
  std::cout << gcd(a, b) << "\n";
  return 0;
}
