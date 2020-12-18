#include <iostream>

int change(int money, const int *coins, int n)
{
  if (money == 0)
    return 0;
  int min = 1000;
  for (size_t i = 0; i < n; ++i) {
    if (money >= coins[i]) {
      int tmp = change(money - coins[i], coins, n);
      if (tmp + 1 < min)
        min = tmp + 1;
    }
  }
  return min;
}

int main()
{
  int money;
  std::cin >> money;
  int coins[] {1, 3 ,4};
  std::cout << change(money, coins, 3) << "\n";
  return 0;
}
