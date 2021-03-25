#include <iostream>
#include <vector>
#include <limits>

using std::vector;
using std::numeric_limits;
using std::abs;

class Graph {
public:
  Graph(const vector<vector<int>> &adj, const vector<vector<int>> &cost) : V(adj), E(cost),
    dist(adj.size(), numeric_limits<long long>::max()) {}

  bool has_cycle(int s) {
    vector<bool> visited(V.size(), false);
    for (size_t i = 0; i < V.size(); ++i) {
      if (!visited[i]) {
        if (bellman(i))
          return true;
        for (size_t j = 0; j < V.size(); ++j) {
          if (dist[j] != numeric_limits<long long>::max())
            visited[j] = true;
        }
      }
    }
    return false;
  }

  bool bellman(int s) {
    dist[s] = 0;
    for (size_t i = 0; i < V.size(); ++i) {
      for (size_t j = 0; j < E[i].size(); ++j) {
        if (dist[i] != numeric_limits<long long>::max() &&
            dist[V[i][j]] > dist[i] + E[i][j])
          dist[V[i][j]] = dist[i] + E[i][j];
      }
    }
    for (size_t i = 0; i < V.size(); ++i) {
      for (size_t j = 0; j < E[i].size(); ++j) {
        if (dist[i] != numeric_limits<long long>::max() &&
            dist[V[i][j]] > dist[i] + E[i][j])
          return true;
      }
    }
    return false;
  }

  void print_vertices() {
    std::cout << "vertices\n";
    for (size_t i = 0; i < V.size(); ++i) {
      std::cout << i+1 << " -> ";
      for (auto e : V[i])
        std::cout << e+1 << " ";
      std::cout << "\n";
    }
  }

  void print_edges() {
    std::cout << "edges\n";
    for (size_t i = 0; i < E.size(); ++i) {
      std::cout << i+1 << " -> ";
      for (auto e : E[i])
        std::cout << e << " ";
      std::cout << "\n";
    }
  }

  void print_dist() {
    std::cout << "dist\n";
    for (size_t i = 0; i < dist.size(); ++i)
      std::cout << i+1 << ":" << dist[i] << " ";
    std::cout << "\n";
  }
 
private:
  vector<vector<int>> V;
  vector<vector<int>> E;
  vector<long long> dist;
};

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  Graph g(adj, cost);
  //@log g.print_vertices(); g.print_edges();
  bool ans = g.has_cycle(0);      
  //@log g.print_dist();
  return ans;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
