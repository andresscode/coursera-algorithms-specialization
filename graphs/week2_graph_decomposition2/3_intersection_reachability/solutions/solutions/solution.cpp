#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::pair;
using std::string;
using std::make_pair;
using std::sort;
using std::greater;

template <class T>
class Graph {
public:
  Graph(vector<vector<T>> &adj): adj(adj), visited(adj.size(), false),
    clock(1), ticks(adj.size(), make_pair(-1, -1)) {
    reversed = vector<vector<T>>(adj.size());
    for (size_t i = 0; i < adj.size(); ++i) {
      for (auto v : adj[i])
        reversed[v].emplace_back(i);
    }
  }

  void dfs(T v, bool rev) {
    if (!visited[v]) {
      previsit(v);
      visited[v] = true;
      if (rev) {
        for (T c : reversed[v]) {
          if (!visited[c])
            dfs(c, rev);
        }
      } else {
        for (T c : adj[v]) {
          if (!visited[c])
            dfs(c, rev);
        }
      }
      postvisit(v);
    }
  }

  void dfs_simple(T v, bool rev) {
    if (!visited[v]) {
      visited[v] = true;
      if (rev) {
        for (T c : reversed[v]) {
          if (!visited[c])
            dfs_simple(c, rev);
        }
      } else {
        for (T c : adj[v]) {
          if (!visited[c])
            dfs_simple(c, rev);
        }
      }
    }
  }

  bool is_visited(T v) {
    return visited[v];
  }

  void clear_visited() {
    for (size_t i = 0; i < visited.size(); ++i)
      visited[i] = false;
  }

  vector<pair<int, size_t>> get_ticks() {
    return ticks;
  }

  void print_adj() {
    std::cout << "adj\n";
    for (size_t i = 0; i < adj.size(); ++i) {
      std::cout << i+1 << " -> ";
      for (size_t j = 0; j < adj[i].size(); ++j)
        std::cout << adj[i][j]+1 << " ";
      std::cout << "\n";
    }
  }

  void print_reversed() {
    std::cout << "reversed\n";
    for (size_t i = 0; i < reversed.size(); ++i) {
      std::cout << i+1 << " -> ";
      for (size_t j = 0; j < reversed[i].size(); ++j)
        std::cout << reversed[i][j]+1 << " ";
      std::cout << "\n";
    }
  }

  void print_order() {
    std::cout << "order -> ";
    for (size_t i = 0; i < ticks.size(); ++i)
      std::cout << ticks[i].first+1 << "(" << ticks[i].second << ") ";
    std::cout << "\n";
  }

  void print_vector(const vector<T> &v, const string &label) {
    std::cout << label << " -> ";
    for (T n : v)
      std::cout << n+1 << " ";
    std::cout << "\n";
  }

private:
  vector<vector<T>> adj;
  vector<vector<T>> reversed;
  vector<bool> visited;
  size_t clock;
  vector<pair<int, size_t>> ticks;

  void previsit(T v) {
    clock++;
  }

  void postvisit(T v) {
    ticks[v].first = v;
    ticks[v].second = clock++;
  }
};

int number_of_strongly_connected_components(vector<vector<int> > adj) {
  int result = 0;
  Graph<int> g(adj);
  //@log g.print_adj();
  //@log g.print_reversed();
  for (size_t i = 0; i < adj.size(); ++i) {
    if (!g.is_visited(i))
      g.dfs(i, true);
  }
  g.clear_visited();
  vector<pair<int, size_t>> post_order = g.get_ticks();
  sort(post_order.begin(), post_order.end(), 
    [](const auto &p1, const auto &p2) {return p1.second > p2.second;});
  //for (auto p : post_order)
    //std::cout << p.first << ":" << p.second << " ";
  //std::cout << "\n";
  //@log g.print_order();
  for (auto p : post_order) {
    if (!g.is_visited(p.first)) {
      g.dfs_simple(p.first, false);
      result++;
    }
  }
  return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << number_of_strongly_connected_components(adj);
}
