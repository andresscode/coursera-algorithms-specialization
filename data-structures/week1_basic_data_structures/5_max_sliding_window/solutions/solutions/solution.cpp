#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int find_max(vector<int> const &v, int i, int j) {
  int m = std::numeric_limits<int>::min(); 
  for (size_t k = i; k < j; ++k) {
    /*@log
    std::cout << "k=" << k << ", v[k]=" << v[k] << ", m=" << m << "\n";
    */
    if (v[k] > m)
      m = v[k];
  }
  return m;
}

void print_vector(vector<int> const &v) {
  for (int e : v)
    std::cout << e << " ";
  std::cout << "\n";
}

void max_sliding_window_naive(vector<int> const & A, int w) {
  std::queue<int> q;
  for (size_t i = 0; i < w; ++i)
    q.push(A[i]); 
  vector<int> m;
  m.push_back(find_max(A, 0, w));
  std::cout << m.back() << " ";
  //@log print_vector(m);
  for (size_t i = 1; i < A.size()-w+1; ++i) {
    int r = i+w-1;
    //@log std::cout << "r=" << r;
    int out = q.front();
    //@log std::cout << ", out=" << out;
    q.pop();
    q.push(A[r]);
    //@log std::cout << ", pushing=" << A[r];
    //@log std::cout << ", m.back=" << m.back() << "\n";
    if (A[r] >= m.back())
      m.push_back(A[r]);
    else if (out == m.back())
      m.push_back(find_max(A, i, w+i));
    else
      m.push_back(m.back());
    //@log print_vector(m);
    std::cout << m.back() << " ";
  }

  std::cout << "\n";
  return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
