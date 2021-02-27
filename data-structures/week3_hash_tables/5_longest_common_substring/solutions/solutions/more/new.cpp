#include <iostream>
#include <string>

using namespace std;

struct Answer {
	size_t i, j, len;
};

int mid(int left, int right) {
  return (left + right) / 2;
}

Answer find(const string &s, const string &t, int l) {
  for (size_t i = 0; i <= (s.size()-l); ++i) {
    auto f = t.find(s.substr(i, l));
    if (f != string::npos)
      return Answer{i, f, (size_t)l};
  }
  return Answer{0, 0, 0};
}

Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
    int left = 1;
    //@log cout << "left=" << left;
    int right = min(s.size(), t.size());
    //@log cout << " right=" << right;
    int middle = mid(left, right);
    //@log cout << " middle=" << middle << "\n";
    do {
      auto found = find(s, t, middle);
      //@log cout << "found={" << found.i << ", " << found.j << ", " << found.len << "}\n";
      if (found.len == 0) {
        right = middle-1;
        middle = mid(left, right);
      } else {
        left = middle+1;
        middle = mid(left, right);
      }
      if (found.len > ans.len)
        ans = found;
    } while (left <= right);
    return ans;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
