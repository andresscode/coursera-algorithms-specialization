# python3

import sys

class Rope:
  def __init__(self, s):
    self.s = s
  def result(self):
    return self.s
  def process(self, i, j, k):
    tmp = self.s[i:j+1]
    #@log print(f'tmp={tmp}')
    self.s = self.s[:i] + self.s[j+1:]
    #@log print(f's={self.s}')
    self.s = self.s[:k] + tmp + self.s[k:]
    #@log print(f's={self.s}')

rope = Rope(sys.stdin.readline().strip())
q = int(sys.stdin.readline())
for _ in range(q):
  i, j, k = map(int, sys.stdin.readline().strip().split())
  rope.process(i, j, k)
print(rope.result())
