#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <queue>

using std::vector;
using std::numeric_limits;
using std::priority_queue;
using std::cout;
using std::pair;
using std::make_pair;

template <class T>
void print_vector(const vector<T> &v) {
  for (auto e : v)
    cout << e << " ";
  cout << "\n";
}

double calc_length(double x1, double y1, double x2, double y2) {
  return sqrt((pow((x1-x2), 2) + pow((y1 - y2), 2)));
}

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;

  vector<double> cost(x.size(), numeric_limits<double>::max());
  vector<int> parent(x.size(), -1);
  vector<bool> pending(x.size(), true);

  cost[0] = 0;

  auto cmp = [](const pair<int, double> &p1, const pair<int, double> &p2) {
    return p1.second > p2.second; };
  priority_queue<pair<int, double>, vector<pair<int, double>>, decltype(cmp)> pq(cmp);

  for (size_t i = 0; i < x.size(); ++i)
    pq.emplace(make_pair(i, cost[i]));

  while (!pq.empty()) {
    auto v = pq.top();
    pq.pop();
    pending[v.first] = false;

    for (size_t i = 0; i < x.size(); ++i) {
      if (pending[i] && cost[i] > calc_length(x[v.first], y[v.first], x[i], y[i])) {
        cost[i] = calc_length(x[v.first], y[v.first], x[i], y[i]);
        parent[i] = v.first;
        pq.emplace(make_pair(i, cost[i]));
      }
    }
  }

  //@log print_vector<double>(cost);

  for (size_t i = 1; i < x.size(); ++i)
    result += cost[i];

  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
