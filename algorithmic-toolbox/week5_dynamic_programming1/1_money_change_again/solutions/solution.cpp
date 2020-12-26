#include <iostream>
#include <vector>

int change(int money, const std::vector<int> &coins) 
{
  if (money == 0)
    return 0;
  static std::vector<int> cache(money + 1, -1);
  int min = 1000;
  for (int coin : coins) {
    if (money >= coin) {
      if (cache[money-coin] == -1)
        cache[money-coin] = change(money-coin, coins);
      if (cache[money-coin] + 1 < min)
        min = cache[money-coin] + 1;
    }
  }
  return min;
}

int main()
{
  int money;
  std::cin >> money;
  std::vector<int> coins{1, 3, 4};
  std::cout << change(money, coins) << "\n";
  return 0;
}
