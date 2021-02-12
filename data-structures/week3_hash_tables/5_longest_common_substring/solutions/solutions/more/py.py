# python3

import sys

class Solver:
  def __init__(self, s):
    self.s = s
    self.m1 = int(1e9+7)
    self.m2 = int(1e9+9)
    self.x = 263
    self.h1 = self.hashes(self.m1)
    self.h2 = self.hashes(self.m2)
    self.pows1 = self.pows(self.m1)
    self.pows2 = self.pows(self.m2)
    #@log print(f'm1={self.m1}, m2={self.m2}, x={self.x}')
    #@log print('h1 -> ', end='')
    #@log print(*self.h1)
    #@log print('h2 -> ', end='')
    #@log print(*self.h2)
    #@log print('pows1 -> ', end='')
    #@log print(*self.pows1)
    #@log print('pows2 -> ', end='')
    #@log print(*self.pows2)

  def ask(self, a, b, l):
    return self.hash(self.h1, a, l, self.pows1)%self.m1 == \
      self.hash(self.h1, b, l, self.pows1)%self.m1 and \
      self.hash(self.h2, a, l, self.pows2)%self.m2 == \
      self.hash(self.h2, b, l, self.pows2)%self.m2


  def hashes(self, m):
    h = []
    h.append(0)
    for i in range(1, len(self.s)):
      h.append((self.x * h[i-1] + ord(self.s[i-1])) % m)
    return h

  def pows(self, m):
    p = []
    p.append(1)
    for i in range(1, len(self.s)):
      p.append((p[i-1]*self.x)%m)
    return p

  def hash(self, h, i, j, pow):
    return h[i+j] - pow[j] * h[i]

s = sys.stdin.readline()
q = int(sys.stdin.readline())
solver = Solver(s)
for i in range(q):
  a, b, l = map(int, sys.stdin.readline().split())
  print("Yes" if solver.ask(a, b, l) else "No")
