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

struct Point {
  int x, y;
};

double calc_dist(const Point &p1, const Point &p2) {
  return std::abs(std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2)));
}

double calc(vector<Point> &v, int begin, int end) {
  double min = std::numeric_limits<double>::max();
  for (size_t i = begin; i < end; ++i) {
    for (size_t j = i + 1; j <= end; ++j) {
      double tmp = calc_dist(v[i], v[j]);
      if (tmp <  min)
        min = tmp;
    }
  }
  return min;
}

double divide(vector<Point> &v, int begin, int end) {
  if (end - begin + 1 <= 3)
    return calc(v, begin, end);
  int mid = (begin + end) / 2;
  double left = divide(v, begin, mid);
  double right = divide(v, mid + 1, end);
  double min = std::min(left, right);
  vector<Point>strip;
  for (size_t i = begin; i <= end; ++i) {
    if (std::abs(v[mid].x - v[i].x) < min)
      strip.push_back(v[i]);
  }
  std::sort(strip.begin(), strip.end(), [] (const Point &p1, const Point &p2) {
    return p1.y < p2.y;});
  for (size_t i = 0; i < strip.size(); ++i) {
    for (size_t j = i + 1; j < i + 8 && j < strip.size(); ++j) {
      double tmp = calc_dist(strip[i], strip[j]);
      if (tmp < min)
        min = tmp;
    }
  }
  return min; 
}

double minimal_distance(vector<int> x, vector<int> y) {
  vector<Point> points(x.size());
  for (size_t i = 0; i < x.size(); ++i)
    points[i] = Point{x[i], y[i]};
  std::sort(points.begin(), points.end(), [] (const Point &p1, const Point &p2) {
    return p1.x < p2.x;});
  return divide(points, 0, points.size() - 1);
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
