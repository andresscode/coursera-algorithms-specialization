#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  std::sort(segments.begin(), segments.end(), [] (const Segment &s1, const Segment &s2) -> bool {
    return s1.start < s2.start;});
  int p = segments[0].end;
  for (size_t i = 1; i < segments.size(); ++i) {
    if (segments[i].start > p) {
      points.push_back(p);
      p = segments[i].end;
    }
    else if (segments[i].end < p)
      p = segments[i].end;
  }
  points.push_back(p);
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
