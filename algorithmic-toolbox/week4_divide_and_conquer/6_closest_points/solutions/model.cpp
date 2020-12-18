#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

using std::vector;
using std::string;
using std::pair;
using std::min;


double minimal_distance(vector<int> x, vector<int> y) {
  double min = std::numeric_limits<double>::max();
  for (size_t i = 0; i < x.size() - 1; ++i) {
    for (size_t j = i + 1; j < x.size(); ++j) {
      double tmp = std::abs(std::sqrt(std::pow(x[i]-x[j], 2) + std::pow(y[i]-y[j], 2)));
      if (tmp < min)
        min = tmp;
    }
  }
  return min;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
