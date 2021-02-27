#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::unordered_map;
using std::make_pair;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
  vector<string> result;
  unordered_map<int, string> numbers;
  for (size_t i = 0; i < queries.size(); ++i) {
    //@log cout << "query={" << queries[i].number << ", " << queries[i].name << "}\n";
    auto found = numbers.find(queries[i].number);
    if (queries[i].type == "add") {
      if (found != numbers.end()) {
        //@log cout << found->first << " exists\n";
        found->second = queries[i].name;
      }
      else {
        //@log cout << "adding new number" << queries[i].number << "\n";
        numbers.insert({queries[i].number, queries[i].name});
      }
    }
    else if (queries[i].type == "find") {
      if (found != numbers.end()) {
        //@log cout << "found=" << queries[i].number << ", " << queries[i].name << "\n";
        result.push_back(found->second);
      }
      else
        result.push_back("not found");
    }
    else {
      if (found != numbers.end())
        numbers.erase(queries[i].number);
    }
  }
  return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
