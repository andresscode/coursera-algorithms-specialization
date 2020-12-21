#include <iostream>
#include <vector>

void solve(int n, std::vector<int> &tmp, std::vector<int> &result)
{
  static int max = 1000001;
  if (tmp[tmp.size()-1] > n)
    return;
  else if (tmp[tmp.size()-1] == n) {
    if (tmp.size() < max) {
      result.clear();
      std::copy(tmp.begin(), tmp.end(), std::back_inserter(result)); 
      max = result.size();
    }
    return;
  }
  for (size_t i = 0; i < 3; ++i) {
    switch (i) {
      case 1:
        tmp.push_back(tmp[tmp.size()-1] * 3);
        break;
      case 0:
        tmp.push_back(tmp[tmp.size()-1] * 2);
        break;
      default:
        tmp.push_back(tmp[tmp.size()-1] + 1);
    }
    solve(n, tmp, result);
    tmp.pop_back();
  }
}

int main()
{
  int n;
  std::cin >> n;
  std::vector<int> tmp;
  tmp.push_back(1);
  std::vector<int> result;
  solve(n, tmp, result);
  std::cout << result.size() - 1 << "\n";
  for (int num : result)
    std::cout << num << " ";
  std::cout << "\n";
  return 0;
}
