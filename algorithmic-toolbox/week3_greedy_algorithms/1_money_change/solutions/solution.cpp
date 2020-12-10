#include <iostream>
#include <vector>

int get_change(int m) {
  std::vector<int> coins{10, 5, 1};
  int k = m;
  int n = 0;
  for (int coin : coins) {
    int c = k / coin;
    k -= c * coin;
    n += c;
    if (k == 0)
      break;
  }
  return n;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
