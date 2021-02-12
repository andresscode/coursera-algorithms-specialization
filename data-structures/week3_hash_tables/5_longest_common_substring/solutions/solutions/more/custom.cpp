#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct Answer {
	size_t i, j, len;
};

class HashTable {
private:
  size_t m;
  vector<vector<pair<string, size_t>>*> table;

public:
  HashTable(size_t m): m(m) {
    table.resize(m);
    for (auto& e : table)
      e = new vector<pair<string, size_t>>();
  }

  ~HashTable() {
    for (auto& e : table)
      delete e;
  }

  void insert(const string &key, size_t val, size_t i) {
    auto p = make_pair(key, val);
    table[i]->push_back(p);
  }

  void print_table() {
    for (size_t i = 0; i < table.size(); ++i) {
      cout << i << " -> ";
      for (size_t j = 0; j < table[i]->size(); ++j)
        cout << "{key=" << table[i]->at(j).first << " val=" << table[i]->at(j).second << "} ";
      cout << "\n";
    }
  }
};

int mid(int left, int right) {
  return (left + right) / 2;
}

void add_substrs(const string &s, int l, unordered_map<string, int> &m) {
  //@log cout << "substrs for -> " << s << "\n";
  for (size_t i = 0; i <= (s.size()-l); ++i) {
    auto ss = s.substr(i, l);
    //@log cout << ss << " ";
    if (m.find(ss) == m.end())
      m.insert(make_pair(ss, i));
  }
  //@log cout << "\n";
}

Answer find(const string &t, int l, unordered_map<string, int> &m) {
  for (size_t i = 0; i <= (t.size()-l); ++i) {
    auto f = m.find(t.substr(i, l));
    if (f != m.end())
      return Answer{(size_t)f->second, i, (size_t)l};
  }
  return Answer{0, 0, 0};
}

Answer solve(const string &s, const string &t) {
    HashTable ht(3);
    ht.insert("hello", 1, 0);
    ht.insert("world", 2, 0);
    ht.insert("fuck", 1, 2);
    ht.print_table();
	Answer ans = {0, 0, 0};
    unordered_map<string, int> m;
    int left = 1;
    //@log cout << "left=" << left;
    int right = min(s.size(), t.size());
    //@log cout << " right=" << right;
    int middle = mid(left, right);
    //@log cout << " middle=" << middle << "\n";
    do {
      add_substrs(s, middle, m);
      //@log cout << "map_size=" << m.size() << "\n";
      auto found = find(t, middle, m);
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
