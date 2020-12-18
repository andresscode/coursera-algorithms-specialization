#include <iostream>
#include <vector>

int search(int n, const std::vector<int> &v, int begin, int end)
{
  if (end < begin)
    return -1;
  int pivot = ((end - begin) / 2) + begin;
  if (v[pivot] == n)
    return pivot;
  else if (v[pivot] > n)
    return search(n, v, begin, pivot - 1);
  else
    return search(n, v, pivot + 1, end);
}

std::vector<int> solve(const std::vector<int> &n, const std::vector<int> &k)
{
  std::vector<int> results;
  results.reserve(k.size());
  for (size_t i = 0; i < k.size(); ++i)
    results.push_back(search(k[i], n, 0, n.size() - 1));
  return results;
}

int main()
{
  int n, k;
  std::cin >> n;
  std::vector<int> nv(n);
  for (size_t i = 0; i < n; ++i)
    std::cin >> nv[i];  
  std::cin >> k;
  std::vector<int> kv(k);
  for (size_t i = 0; i < k; ++i)
    std::cin >> kv[i];
  std::vector<int> results = solve(nv, kv);
  for (size_t i = 0; i < results.size(); ++i)
    std::cout << results[i] << " ";
  std::cout << "\n";
  return 0;
}
