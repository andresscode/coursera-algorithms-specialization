#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using std::stack;

template <class T>
class Graph {
public:
  Graph(vector<vector<T>> &adj): adj(adj), visited(adj.size(), false) {}

  bool path_exists(T begin, T end) {
    if (begin == end)
      return true;
    dfs(begin);
    return visited[begin] && visited[end];
  }

  void dfs(T v) {
    stack<T> s;
    s.push(v);
    while (!s.empty()) {
      T curr = s.top();
      s.pop();
      if (visited[curr]) continue;
      visited[curr] = true;
      for (T n : adj[curr]) {
        if (!visited[n])
          s.push(n);
      }
    }
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
    for (size_t i = 0; i < visited.size(); ++i)
      std::cout << i+1 << ":" << visited[i] << " ";
    std::cout << "\n";
  }

private:
  vector<vector<T>> adj;
  vector<bool> visited;
};

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  Graph<int> g(adj);
  for (size_t i = 0; i < adj.size(); ++i) {
    if (!g.is_visited(i)) {
      g.dfs(i);
      res++; 
    }
  }
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
