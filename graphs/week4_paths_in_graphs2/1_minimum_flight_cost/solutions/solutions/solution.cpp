#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using std::vector;
using std::queue;
using std::pair;
using std::make_pair;
using std::priority_queue;
using std::numeric_limits;
using std::stack;

class Graph {
public:
  Graph(const vector<vector<int>> &V, const vector<vector<int>> &E) : V(V), E(E), 
    dist(V.size(), numeric_limits<long long>::max()), prev(V.size(), -1) {}

  void dijkstra(int s) {
    dist[s] = 0;
    auto comp = [](const auto &p1, const auto &p2) {return p1.second > p2.second;};
    priority_queue<pair<int, long long>, vector<pair<int, long long>>, decltype(comp)> pq(comp); 
    for (size_t i = 0; i < V.size(); ++i)
      pq.push(make_pair(i, dist[i]));
    while (!pq.empty()) {
      auto u = pq.top();
      pq.pop();
      //@log std::cout << "vertex: " << u.first+1 << ", dist: " << u.second << "\n";
      for (size_t i = 0; i < E[u.first].size(); ++i) {
        /*@log 
        std::cout << "neighbour: " << V[u.first][i]+1 << ", edge: " << E[u.first][i] 
          << ", dist: " << dist[V[u.first][i]] << "\n";
        */ 
        if (dist[u.first] + E[u.first][i] >= 0 && 
            dist[V[u.first][i]] > dist[u.first] + E[u.first][i]) {
          //@log std::cout << "distance updated to " << dist[u.first] + E[u.first][i] << "\n";
          dist[V[u.first][i]] = dist[u.first] + E[u.first][i];
          prev[V[u.first][i]] = u.first;
          pq.push(make_pair(V[u.first][i], dist[V[u.first][i]]));
        }
      }
    }
  }

  int shortest(int t) {
    return dist[t] == numeric_limits<long long>::max() ? -1 : dist[t];  
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

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  Graph g(adj, cost);
  //@log g.print_vertices(); g.print_edges();
  g.dijkstra(s);
  //@log g.print_dist(); g.print_prev(); 
  return g.shortest(t);
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
