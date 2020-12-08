#include <iostream>

int last_digit(const int n)
{
  if (n < 2)
    return n;
  int a = 0;
  int b = 1;
  for (int i = 2; i < n; ++i) {
    int tmp = (a + b) % 10;
    a = b;
    b = tmp;
  }
  return (a + b) % 10;
}

int main()
{
  int n;
  std::cin >> n;
  std::cout << last_digit(n) << "\n";
  return 0;
}
