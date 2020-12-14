#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int binary_starts(const vector<int> &v, int begin, int end, int p) {
  if (end < begin)
    return 0;
  int mid = (begin + end) / 2;
  if (p < v[mid]) {
    return binary_starts(v, begin, mid - 1, p)
      + end - mid + 1; 
  }
  else
    return binary_starts(v, mid + 1, end, p);
}

int binary_ends(const vector<int> &v, int begin, int end, int p) {
  if (end < begin)
    return 0;
  int mid = (begin + end) / 2;
  if (p > v[mid]) {
    return binary_ends(v, mid + 1, end, p)
      + mid - begin + 1; 
  }
  else
    return binary_ends(v, begin, mid - 1, p);
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  std::sort(starts.begin(), starts.end());
  std::sort(ends.begin(), ends.end());
  for (size_t i = 0; i < points.size(); ++i) {
    cnt[i] = starts.size() - binary_starts(starts, 0, starts.size() - 1, points[i])
      - binary_ends(ends, 0, ends.size() - 1, points[i]);
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
