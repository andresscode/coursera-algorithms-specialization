#include <iostream>
#include <vector>

using namespace std;

vector<int> solve(int k, const string &text, const string &pattern) {
	vector<int> pos;
    if (pattern.size() > text.size())
      return pos;
    for (size_t i = 0; i < ((text.size()-pattern.size())+1); ++i) {
      int count = 0;
      for (size_t j = 0; j < pattern.size(); ++j) {
        if (count > k)
          break;
        else if (text[i+j] != pattern[j]) {
          count++;
        }
      }
      if (count <= k)
        pos.push_back(i);
    }
	return pos;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
