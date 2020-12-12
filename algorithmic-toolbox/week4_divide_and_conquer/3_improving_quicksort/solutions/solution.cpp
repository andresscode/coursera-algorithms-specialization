#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

struct Partition {
  int left;
  int right;
};

Partition partition3(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l - 1;
  int k = l;
  for (int i = l + 1; i <= r; ++i) {
    if (a[i] < x) {
      j++;
      k++;
      swap(a[i], a[k]);
      swap(a[k], a[j]);
    } else if (a[i] == x) {
      k++;
      swap(a[i], a[k]);
    }
  }
  return Partition{j, k};
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  //int m = partition2(a, l, r);
  Partition m = partition3(a, l, r);

  randomized_quick_sort(a, l, m.left);
  randomized_quick_sort(a, m.right + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
