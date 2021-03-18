#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

class Graph {
public:
  Graph(const vector<vector<int>> &adj) : adj(adj), dist(adj.size(), -1), parent(adj.size(), -1) {}

  vector<int> shortest_path(int u, int v) {
    bfs(u);
    vector<int> path;
    if (parent[v] == -1)
      return path;
    path.push_back(v);
    int p = parent[v];
    while (parent[p] != p) {
      path.push_back(p);
      p = parent[p];
    }
    path.push_back(u);
    return path;
  }

  void bfs(int u) {
    queue<int> q;
    q.emplace(u);
    dist[u] = 0;
    parent[u] = u;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      explore(v, q);
    }
  }

  void print_adj() {
    for (size_t i = 0; i < adj.size(); ++i) {
      std::cout << i+1 << " -> ";
      for (auto e : adj[i])
        std::cout << e+1 << " ";
      std::cout << "\n";
    }
  }

  void print_dist() {
    std::cout << "dist -> ";
    for (size_t i = 0; i < dist.size(); ++i)
      std::cout << i+1 << ":" << dist[i] << " "; 
    std::cout << "\n";
  }

  void print_path(const vector<int> &p) {
    std::cout << "path -> ";
    for (auto v : p)
      std::cout << v+1 << " ";
    std::cout << "\n";
  }

private:
  vector<vector<int>> adj;
  vector<int> dist;
  vector<int> parent;

  void explore(int u, queue<int> &q) {
    for (auto v : adj[u]) {
      if (dist[v] == -1) {
        q.emplace(v);
        dist[v] = dist[u] + 1;
        parent[v] = u;
      }
    }
  }
};

int distance(vector<vector<int> > &adj, int s, int t) {
  Graph g(adj);
  vector<int> path = g.shortest_path(s, t);
  //@log g.print_adj(); g.print_dist(); g.print_path(path);
  return path.size() - 1;
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
