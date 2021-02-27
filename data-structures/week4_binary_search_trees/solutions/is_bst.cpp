#include <iostream>
#include <vector>
#include <stack>

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

vector<int> in_order(const vector<Node> &v){
  vector<int> result;
  stack<Node> s;
  int i = 0;
  while (i != -1 || !s.empty()) {
    while (i != -1) {
      s.push(v[i]);
      i = v[i].left;
    }
    Node n = s.top();
    s.pop();
//    cout << n.key << " ";
    result.emplace_back(n.key);
    i = n.right;
  }
//  cout << "\n";
  return result;
}

bool IsBinarySearchTree(const vector<Node> &tree) {
  if (tree.empty())
    return true;
  vector<int> result = in_order(tree);
//  for (int e : result)
//    cout << e << " ";
//  cout << "\n";
  int prev = result[0];
  for (size_t i = 1; i < result.size(); ++i) {
    if (prev > result[i])
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
