#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::pair;
using std::string;

template <class T>
class Graph {
public:
  Graph(vector<vector<T>> &adj): adj(adj), visited(adj.size(), false),
    path(adj.size(), false) {}

  bool path_exists(T begin, T end) {
    if (begin == end)
      return true;
    dfs(begin);
    return visited[begin] && visited[end];
  }

  void dfs(T v) {
    if (!visited[v]) {
      visited[v] = true;
      path[v] = true;
      for (T c : adj[v]) {
        if (path[c])
          cycles = true;
        if (!visited[c])
          dfs(c);
      }
      path[v] = false;
    }
  }

  bool is_visited(T v) {
    return visited[v];
  }

  bool has_cycles() {
    return cycles;
  }

  void print_adj() {
    for (size_t i = 0; i < adj.size(); ++i) {
      std::cout << i+1 << " -> ";
      for (size_t j = 0; j < adj[i].size(); ++j)
        std::cout << adj[i][j]+1 << " ";
      std::cout << "\n";
    }
  }

  void print_visited() {
    std::cout << "visited -> ";
    for (size_t i = 0; i < visited.size(); ++i)
      std::cout << i+1 << ":" << visited[i] << " ";
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
  vector<bool> visited;
  vector<bool> path;
  bool cycles = false;
};

int acyclic(vector<vector<int> > &adj) {
  Graph<int> g(adj);
  //@log g.print_adj();
  for (size_t i = 0; i < adj.size(); ++i) {
    if (!g.is_visited(i))
      g.dfs(i);
    if (g.has_cycles())
      return 1;
  }
  //@log g.print_visited();
  return 0;
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
  std::cout << acyclic(adj);
}
