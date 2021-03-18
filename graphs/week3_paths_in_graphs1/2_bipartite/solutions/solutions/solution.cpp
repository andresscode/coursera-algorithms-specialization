#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

class Graph {
public:
  Graph(const vector<vector<int>> &adj) : adj(adj), color(adj.size(), -1) {}

  int bfs(int u) {
    queue<int> q;
    q.emplace(u);
    color[u] = 0;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      if (!explore(v, q))
        return 0;
    }
    return 1;
  }

  bool is_colored(int v) {
    return color[v] != -1;
  }

  void print_adj() {
    for (size_t i = 0; i < adj.size(); ++i) {
      std::cout << i+1 << " -> ";
      for (auto e : adj[i])
        std::cout << e+1 << " ";
      std::cout << "\n";
    }
  }

  void print_color() {
    std::cout << "color -> ";
    for (size_t i = 0; i < color.size(); ++i)
      std::cout << i+1 << ":" << color[i] << " "; 
    std::cout << "\n";
  }

private:
  vector<vector<int>> adj;
  vector<int> color;

  bool explore(int u, queue<int> &q) {
    for (auto v : adj[u]) {
      if (color[v] == -1) {
        q.emplace(v);
        color[v] = (color[u] + 1) % 2;
      }
      else if (color[v] == color[u])
        return false;
    }
    return true;
  }
};

int bipartite(vector<vector<int> > &adj) {
  Graph g(adj);
  for (size_t i = 0; i < adj.size(); ++i) {
    //@log g.print_color();
    if (!g.is_colored(i) && g.bfs(i) == 0)
      return 0;
  }
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
