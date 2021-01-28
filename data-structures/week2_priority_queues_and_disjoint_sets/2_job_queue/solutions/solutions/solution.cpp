#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;
using std::pair;
using std::greater;
using std::make_pair;

typedef pair<long long, long long> pll;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for (int i = 0; i < num_workers_; ++i)
      pq.push(make_pair(0L, (long long) i));
    for (int i = 0; i < jobs_.size(); ++i) {
      long long duration = jobs_[i];
      pll tmp = pq.top();
      pq.pop();
      assigned_workers_[i] = tmp.second;
      start_times_[i] = tmp.first;
      pq.push(make_pair(tmp.first + duration, tmp.second));
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
