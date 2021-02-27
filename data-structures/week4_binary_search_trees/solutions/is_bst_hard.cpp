#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::stack;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}

  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

struct Result {
  struct Node node;
  int level;

  Result(struct Node node, int level) : node(node), level(level) {}
};

vector<Result> in_order(const vector<Node> &v) {
  vector<Result> result;
  stack<Result> s;
  int i = 0;
  int l = 0;
  while (i != -1 || !s.empty()) {
    while (i != -1) {
      s.push(Result(v[i], l));
      i = v[i].left;
      l++;
    }
    Result n = s.top();
    s.pop();
//    cout << "{key=" << n.node.key << " level=" << n.level << "} ";
    result.emplace_back(n);
    i = n.node.right;
    l = n.level + 1;
  }
//  cout << "\n";
  return result;
}

bool IsBinarySearchTree(const vector<Node> &tree) {
  if (tree.empty())
    return true;
  vector<Result> result = in_order(tree);
  Result prev = result[0];
  for (size_t i = 1; i < result.size(); ++i) {
    if (prev.node.key > result[i].node.key ||
        (prev.node.key == result[i].node.key && prev.level > result[i].level))
      return false;
    prev = result[i];
  }
  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.emplace_back(key, left, right);
  }
  cout << (IsBinarySearchTree(tree) ? "CORRECT" : "INCORRECT") << endl;
  return 0;
}
