#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
  if (tank >= dist)
    return 0;
  stops.push_back(dist);
  int refills = 0;
  int start = 0;
  int left = tank;
  for (int stop : stops) {
    int section = stop - start;
    start = stop;
    left -= section;
    if (left < 0) {
      refills++;
      if (tank - section < 0)
        return -1;
      left = tank - section;
    }
  }
  return refills;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
