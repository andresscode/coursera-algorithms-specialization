#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

class DSet {
    int *rank, *parent, n;
  
public:
    // Constructor to create and
    // initialize sets of n items
    DSet(int n)
    {
        rank = new int[n];
        parent = new int[n];
        this->n = n;
        makeSet();
    }

    ~DSet()
    {
      delete[] rank;
      delete[] parent;
    }
  
    // Creates n single item sets
    void makeSet()
    {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
  
    // Finds set of given item x
    int find(int x)
    {
        // Finds the representative of the set
        // that x is an element of
        if (parent[x] != x) {
  
            // if x is not the parent of itself
            // Then x is not the representative of
            // his set,
            parent[x] = find(parent[x]);
  
            // so we recursively call Find on its parent
            // and move i's node directly under the
            // representative of this set
        }
  
        return parent[x];
    }
  
    // Do union of two sets represented
    // by x and y.
    void Union(int x, int y)
    {
        // Find current sets of x and y
        int xset = find(x);
        int yset = find(y);
  
        // If they are already in same set
        if (xset == yset)
            return;
  
        // Put smaller ranked item under
        // bigger ranked item if ranks are
        // different
        if (rank[xset] < rank[yset]) {
            parent[xset] = yset;
        }
        else if (rank[xset] > rank[yset]) {
            parent[yset] = xset;
        }
  
        // If ranks are same, then increment
        // rank.
        else {
            parent[yset] = xset;
            rank[xset] = rank[xset] + 1;
        }
    }
};

struct Edge {
  size_t u;
  size_t v;
  double cost;
};

double calc_length(double x1, double y1, double x2, double y2) {
  return sqrt((pow((x1-x2), 2) + pow((y1 - y2), 2)));
}

double clustering(vector<int> x, vector<int> y, int k) {
  DSet ds(x.size());
  vector<Edge> edges;

  auto cmp = [](const Edge &u, const Edge &v) {
    return u.cost > v.cost; };
  priority_queue<Edge, vector<Edge>, decltype(cmp)> pq(cmp);

  for (size_t i = 0; i < x.size(); ++i) {
    for (size_t j = i+1; j < x.size(); ++j)
      pq.emplace(Edge{i, j, calc_length(x[i], y[i], x[j], y[j])});
  }

  while (!pq.empty()) {
    auto e = pq.top();
    pq.pop();

    if (ds.find(e.u) != ds.find(e.v)) {
      edges.push_back(e);
      ds.Union(e.u, e.v);
    }
  }

  //for (auto e : edges)
    //cout << "{u: " << e.u << ", v: " << e.v << ", cost: " << e.cost << "} ";
  //cout << "\n";

  int i = edges.size();
  for (size_t j = 0; j < k-1; j++)
    i--;

  return edges[i].cost;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
