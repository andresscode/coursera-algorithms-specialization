#include <iostream>
#include <vector>
#include <limits>

using std::vector;
using std::numeric_limits;
using std::abs;

class Graph {
public:
  Graph(const vector<vector<int>> &adj, const vector<vector<int>> &cost) : V(adj), E(cost),
    dist(adj.size(), numeric_limits<long long>::max()), prev(adj.size(), -1) {}

  int bellman(int s) {
    dist[s] = 0;
    int last = -1;
    for (size_t i = 0; i < V.size(); ++i) {
      for (size_t j = 0; j < E.size(); ++j) {
        for (size_t k = 0; k < E[j].size(); ++k) {
          if (dist[j] != numeric_limits<long long>::max() && 
              dist[V[j][k]] > dist[j] + E[j][k]) {
            dist[V[j][k]] = dist[j] + E[j][k];
            prev[V[j][k]] = j;
            last = V[j][k];
          }
        }
      }
    }
    for (size_t i = 0; i < V.size(); ++i) {
      if (prev[last] == -1)
        return 0;
      last = prev[last];
    }
    return 1;
  }

  bool was_relaxed(int v) {
    return dist[v] != numeric_limits<long long>::max();
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
  
  void print_prev() {
    std::cout << "prev\n";
    for (size_t i = 0; i < prev.size(); ++i)
      std::cout << i+1 << ":" << prev[i]+1 << " ";
    std::cout << "\n";
  }
 
private:
  vector<vector<int>> V;
  vector<vector<int>> E;
  vector<long long> dist;
  vector<int> prev;
};

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  Graph g(adj, cost);
  //@log g.print_vertices(); g.print_edges();
  for (size_t i = 0; i < adj.size(); ++i) {
    if (!g.was_relaxed(i) && g.bellman(i) == 1)
      return 1;
  }
  //@log g.print_dist(); g.print_prev();
  return 0;
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
