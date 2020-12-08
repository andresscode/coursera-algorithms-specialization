#include <iostream>
#include <vector>

typedef int64_t ll;

int solve(const ll n)
{
  if (n < 2)
    return n;
  std::vector<int> fibs;
  fibs.push_back(0);
  fibs.push_back(1);
  int i = 2;
  while (true) {
    fibs.push_back((fibs[i - 2] + fibs[i - 1]) % 10);
    if (fibs[i - 1] == 0 && fibs[i] == 1)
      break;
    i++;
  }
  int sum = 0;
  int limit = n % (fibs.size() - 2);
  for (int j = 0; j <= limit; ++j) {
    fibs[j] = (fibs[j] * fibs[j]) % 10;
    sum += fibs[j];
  }
  return sum % 10;
}

int main()
{
  ll n;
  std::cin >> n;
  std::cout << solve(n) << "\n";
  return 0;
}
