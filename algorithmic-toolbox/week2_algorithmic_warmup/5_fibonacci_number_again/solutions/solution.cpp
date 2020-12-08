#include <iostream>
#include <vector>

typedef long long ll;

ll solve(ll n, int m)
{
  if (n < 2)
   return n;
  std::vector<ll> fibs;
  fibs.push_back(0);
  fibs.push_back(1);
  std::vector<ll> mods;
  mods.push_back(0);
  mods.push_back(1);
  while (true) {
    fibs.push_back((ll) fibs[fibs.size() - 2] + fibs[fibs.size() - 1]);
    mods.push_back((ll) fibs[fibs.size() - 1] % m);
    if (mods[mods.size() - 2] == 0 && mods[mods.size() - 1] == 1)
      break;
  }
  for (ll mod : mods)
    std::cout << mod << " ";
  std::cout << "\n";
  return mods[n % (mods.size() - 2)];
}

int main()
{
  int n, m;
  std::cin >> n;
  std::cin >> m;
  std::cout << solve(n, m) << "\n";
  return 0;
}
