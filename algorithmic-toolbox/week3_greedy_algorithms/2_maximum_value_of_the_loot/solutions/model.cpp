#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct Item {
  int index;
  double ratio;
};

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  if (capacity == 0)
    return 0.0;
  double value = 0.0;
  vector<Item> items(values.size());
  for (int i = 0; i < values.size(); i++)
    items[i] = Item{i, (double) values[i] / weights[i]};
  std::sort(items.begin(), items.end(), [](const auto &lhs, const auto &rhs) {
    return lhs.ratio > rhs.ratio; });
  int i = 0;
  while (capacity > 0 && i < values.size()) {
    if (capacity >= weights[items[i].index])
      value += values[items[i].index];
    else
      value += (double) capacity / weights[items[i].index] * values[items[i].index];
    capacity -= weights[items[i].index];
    i++;
  }
  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout << std::fixed;
  std::cout.precision(4);
  std::cout << optimal_value << std::endl;
  return 0;
}
