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
    removed(adj.size(), false) {}

  bool path_exists(T begin, T end) {
    if (begin == end)
      return true;
    dfs(begin);
    return visited[begin] && visited[end];
  }

  bool dfs(T v) {
    if (!visited[v]) {
      visited[v] = true;
      removed[v] = true;
      for (int n : adj[v]) {
        if (!visited[n] && dfs(n))
          return true;
        else if (removed[n])
          return true;
      }
    }
    removed[v] = false;
    return false;
  }

  bool is_visited(T v) {
    return visited[v];
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
  vector<bool> removed;
};

int acyclic(vector<vector<int> > &adj) {
  Graph<int> g(adj);
  //@log g.print_adj();
  for (size_t i = 0; i < adj.size(); ++i) {
    if (g.dfs(i))
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
