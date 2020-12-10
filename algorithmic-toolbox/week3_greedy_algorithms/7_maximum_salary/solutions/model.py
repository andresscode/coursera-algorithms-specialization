import sys
from itertools import permutations

def largest_number(a):
    answer = ''
    for pi in permutations(a):
      concat = ''
      for i in pi:
        concat += i
      answer = max(answer, concat)
    return answer

if __name__ == '__main__':
    input()
    data = input().split()
    print(largest_number(data))
    
