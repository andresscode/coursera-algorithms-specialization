#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::numeric_limits;
using std::cout;
using std::string;

class Graph {
public:
  Graph(vector<vector<int>> &V,
        vector<vector<int>> &E,
        vector<long long> &dist,
        vector<int> &reac,
        vector<int> &shor) : V(V), E(E), dist(dist), reac(reac), shor(shor), prev(V.size(), -1) {}

  void bellman(const int s) {
    dfs(s);
    dist[s] = 0;
    for (size_t i = 0; i < vertices.size() - 1; ++i) {
      int last = -1;
      for (size_t u = 0; u < vertices.size(); ++u) {
        for (size_t v = 0; v < V[vertices[u]].size(); ++v) {
          if (relax(vertices[u], V[vertices[u]][v], E[vertices[u]][v]))
            last = V[vertices[u]][v];
        }
      }
      if (last == -1)
        break;
    }
    queue<int> q;
    for (size_t u = 0; u < vertices.size(); ++u) {
      for (size_t v = 0; v < V[vertices[u]].size(); ++v) {
        if (relax(vertices[u], V[vertices[u]][v], E[vertices[u]][v]))
          q.push(V[vertices[u]][v]);
      }
    }
    while (!q.empty()) {
      mark_cycles(q.front());
      q.pop();
    }
  }

  template <class T>
  void print_vector(const vector<T> &v, const string &s) {
    cout << s << "\n";
    for (size_t i = 0; i < v.size(); ++i)
      cout << i+1 << ":" << v[i] << " ";
    cout << "\n";
  }

private:
  vector<vector<int>> &V;
  vector<vector<int>> &E;
  vector<long long> &dist;
  vector<int> &reac;
  vector<int> &shor;
  vector<int> prev;
  vector<int> vertices;

  bool relax(const int u, const int v, const int w) {
    if (dist[u] != numeric_limits<long long>::max() &&
        dist[v] > dist[u] + w) {
      dist[v] = dist[u] + w;
      prev[v] = u;
      return true;
    }
    return false;
  }

  void dfs(const int s) {
    reac[s] = 1;
    vertices.push_back(s);
    for (size_t i = 0; i < V[s].size(); ++i) {
      if (!reac[V[s][i]])
        dfs(V[s][i]);
    }
  }

  void mark_cycles(const int s) {
    shor[s] = 0;
    for (size_t i = 0; i < V[s].size(); ++i) {
      if (shor[V[s][i]])
        mark_cycles(V[s][i]);
    }
  }
};

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  Graph g(adj, cost, distance, reachable, shortest);
  g.bellman(s);
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
