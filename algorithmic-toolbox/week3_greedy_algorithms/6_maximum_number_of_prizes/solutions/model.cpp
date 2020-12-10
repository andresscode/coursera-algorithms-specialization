#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  int tmp = n;
  int left = 0;
  int right = 0;
  while (tmp > 0) {
    left++;
    right = tmp - left;
    if (right > left) {
      summands.push_back(left);
      tmp = right;
    } else
      break;
  }
  summands.push_back(tmp);
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
