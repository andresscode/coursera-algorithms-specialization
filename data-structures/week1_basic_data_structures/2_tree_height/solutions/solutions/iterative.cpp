#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

int recurse(Node* n) {
  if (n == 0)
    return 0;
  int m = 0;
  for (Node* child : n->children) {
    int h = recurse(child);
    m = std::max(m, h);
  }
  return m + 1;
}

int iterate(Node* n) {
  std::queue<Node*> q;
  q.push(n);
  Node* last = nullptr;
  while (!q.empty()) {
    last = q.front();
    q.pop();
    for (Node* child : last->children)
      q.push(child);
  }
  int h = 1;
  while (last->parent != 0) {
    last = last->parent;
    h++;
  }
  return h;
}

int get_height(const std::vector<Node> &nodes) {
  Node root;
  for (Node n : nodes) {
    if (n.parent == 0) {
      root = n;
      break;
    }
  }
  //@log std::cout << recurse(&root) << "\n";
  return iterate(&root);
}

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

  std::cout << get_height(nodes) << "\n";
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
