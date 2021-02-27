#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void swift_down(int node) {
    int i = node;
    int l = i * 2 + 1;
    int r = l + 1;
    if (l < data_.size() && data_[l] < data_[i])
      i = l;
    if (r < data_.size() && data_[r] < data_[i])
      i = r;
    if (i == node)
      return;
    swap(data_[node], data_[i]);
    swaps_.push_back(make_pair(node, i));
    swift_down(i);
  }

  void GenerateSwaps() {
    swaps_.clear();
    for (int i = data_.size() / 2; i >= 0; --i) {
      //@log cout << "i=" << i << "\n";
      swift_down(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
