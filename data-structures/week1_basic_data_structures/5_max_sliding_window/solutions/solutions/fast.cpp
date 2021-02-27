#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits>

using std::cin;
using std::cout;
using std::vector;
using std::stack;

class StackWithMax {
    vector<int> _stack;
    stack<int> _max;

  public:

    void Push(int value) {
        _stack.push_back(value);
        if (_max.empty() || _max.top() <= value)
          _max.push(value);
    }

    int Back() {
      return _stack.back();
    }

    void Pop() {
        if (_stack.back() == _max.top())
          _max.pop();
        _stack.pop_back();
    }

    bool Empty() {
      return _stack.empty();
    }

    int Max() const {
        return _max.empty() ? std::numeric_limits<int>::min() : _max.top();
    }
};

class QueueWithMax {
  StackWithMax head;
  StackWithMax tail;

  public:
  QueueWithMax() {
    head = StackWithMax();
    tail = StackWithMax();
  }

  void Push(int value) {
    tail.Push(value);
  }

  void Pop() {
    if (head.Empty()) {
      while (!tail.Empty()) {
        int tmp = tail.Back();
        tail.Pop();
        head.Push(tmp);
      }
    }
    head.Pop();
  }

  int Max() {
    /*@log
    cout << "tailMax=" << tail.Max() << ", headMax=" << head.Max() << "\n";
    */
    return std::max(head.Max(), tail.Max());
  }
};

void max_sliding_window_naive(vector<int> const & A, int w) {
  QueueWithMax q;
  for (size_t i = 0; i < w; ++i)
    q.Push(A[i]);
  cout << q.Max() << " ";
  for (size_t i = w; i < A.size(); ++i) {
    q.Push(A[i]);
    q.Pop();
    cout << q.Max() << " ";
  }
  return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;
    
    max_sliding_window_naive(A, w);

    return 0;
}
