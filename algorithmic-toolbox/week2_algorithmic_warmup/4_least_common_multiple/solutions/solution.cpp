#include <iostream>

typedef int64_t lint;

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  int tmp = a % b;
  return gcd(b, tmp);
}

lint lcm(int a, int b)
{
  int g = gcd(a, b);
  return ((lint) a / g) * b;
}
  
int main()
{
  int a, b;
  std::cin >> a;
  std::cin >> b;
  std::cout << lcm(a, b) << "\n";
  return 0;
}
