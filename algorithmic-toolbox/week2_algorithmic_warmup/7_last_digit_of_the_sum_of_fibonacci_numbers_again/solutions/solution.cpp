#include <iostream>
#include <vector>

typedef int64_t ll;

int solve(const ll m, const ll n)
{
  if (n < 2)
    return n;
  std::vector<ll> fibs;
  fibs.push_back(0);
  fibs.push_back(1);
  std::vector<int> mods;
  mods.push_back(0);
  mods.push_back(1);
  std::vector<int> sums;
  sums.push_back(0);
  sums.push_back(1);
  int i = 2;
  while (true) {
    fibs.push_back(fibs[i - 2] + fibs[i - 1]);
    mods.push_back(fibs[i] % 10);
    sums.push_back((sums[i - 2] + sums[i - 1] + 1) % 10);
    if (mods[i - 1] == 0 && mods[i] == 1)
      break;
    i++;
  }
  int size = mods.size() - 2;
  if (m == n)
    return mods[n % size];
  int sum_m = sums[(m - 1) % size];
  int sum_n = sums[n % size];
  int result = sum_n - sum_m;
  return result < 0 ? result + 10 : result;
}

int main()
{
  ll m, n;
  std::cin >> m;
  std::cin >> n;
  std::cout << solve(m, n) << "\n";
  return 0;
}
