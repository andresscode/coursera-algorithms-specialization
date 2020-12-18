#include <iostream>
#include <vector>
#include <cstdlib>

typedef long long ll;

ll merge(std::vector<int> &v, int begin, int pivot, int end)
{
  ll count = 0;
  std::vector<int> tmp;
  int i = begin;
  int j = pivot + 1;
  /*std::cout << "left={ ";
  for (size_t k = begin; k <= pivot; ++k)
    std::cout << v[k] << " ";
  std::cout << "} ";
  std::cout << "right={ ";
  for (size_t k = pivot + 1; k <= end; ++k)
    std::cout << v[k] << " ";
  std::cout << "}\n";*/
  while (i <= pivot && j <= end) {
    if (v[i] > v[j]) {
      count = count + (pivot - i + 1);
      tmp.push_back(v[j++]);
    } else
      tmp.push_back(v[i++]);
  }
  while (i <= pivot)
    tmp.push_back(v[i++]); 
  while (j <= end)
    tmp.push_back(v[j++]);
  i = begin;
  //std::cout << "result={ ";
  for (int e : tmp) {
    v[i++] = e;
    //std::cout << v[i - 1] << " ";
  }
  //std::cout << "}\n";
  return count;
}

ll sort(std::vector<int> &v, int begin, int end)
{
  //std::cout << "begin=" << begin << ", end=" << end << "\n";
  ll count = 0;
  if (end <= begin)
    return count;
  int pivot = (begin + end) / 2;
  //std::cout << "pivot=" << pivot << "\n";
  count += sort(v, begin, pivot);
  count += sort(v, pivot + 1, end);
  count += merge(v, begin, pivot, end);
  return count;
}

int main()
{
  int n;
  std::cin >> n;
  std::vector<int> v(n);
  for (size_t i = 0; i < n; ++i)
    std::cin >> v[i];
  std::cout << sort(v, 0, v.size() - 1);
  return 0;
}
