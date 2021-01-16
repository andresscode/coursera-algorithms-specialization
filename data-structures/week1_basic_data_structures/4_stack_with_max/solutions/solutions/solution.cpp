#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <stack>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;
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

    void Pop() {
        assert(_stack.size());
        if (_stack.back() == _max.top())
          _max.pop();
        _stack.pop_back();
    }

    int Max() const {
        assert(_stack.size());
        return _max.top();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax _stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            _stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            _stack.Pop();
        }
        else if (query == "max") {
            cout << _stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}
