# python3

import sys
from collections import namedtuple

Answer = namedtuple('answer_type', 'i j len')

m1 = 1000000000039
m2 = 1000000000061
x = 31

def hashes(s, m): 
  h = []
  h.append(0)
  for i in range(1, len(s)+1):
    h.append((x * h[i-1] + ord(s[i-1])) % m)
  return h

def pows(n, m): 
  p = []
  p.append(1)
  for i in range(1, n+1):
    p.append((p[i-1]*x)%m)
  return p

def hash(h, i, j, pow):
  return h[i+j] - pow[j] * h[i]

def mid(l, r):
  return int((l+r)/2)

def hash_table(l, r, s, h, pow, mod):
  ht = {}
  for i in range(l, r-s+1):
    _hash = hash(h, i, s, pow) % mod
    if _hash not in ht:
      ht[_hash] = i
  return ht

def find(ht, l, r, s, h, pow, mod):
  for i in range(l, r-s+1):
    _hash = hash(h, i, s, pow) % mod
    if _hash in ht:
      return Answer(ht[_hash], i-l, s)
  return Answer(0,0,0)
    
def ans_eq(ans1, ans2):
  return ans1.i == ans2.i and ans1.j == ans2.j and ans1.len == ans2.len;

def solve(s, t):
  ans = Answer(0, 0, 0)

  merge = s+t
  #@log print(merge)

  h1 = hashes(merge, m1)
  #@log print('h1 -> ', end=' ')
  #@log print(*h1)
  h2 = hashes(merge, m2)
  #@log print('h2 -> ', end=' ')
  #@log print(*h2)
  pow1 = pows(len(merge), m1)
  #@log print('pow1 -> ', end=' ')
  #@log print(*pow1)
  pow2 = pows(len(merge), m2)
  #@log print('pow2 -> ', end=' ')
  #@log print(*pow2)

  left = 1
  right = min(len(s), len(t))
  middle = mid(left, right)

  while True:
    #@log print(f'left={left} right={right} middle={middle}')
    ht1 = hash_table(0, len(s), middle, h1, pow1, m1)
    #@log print('ht1 -> ', end=' ')
    #@log print(*ht1)
    ht2 = hash_table(0, len(s), middle, h2, pow2, m2)
    #@log print('ht2 -> ', end=' ')
    #@log print(*ht2)
    found1 = find(ht1, len(s), len(s)+len(t), middle, h1, pow1, m1)
    #@log print(f'found1={found1}')
    found2 = find(ht2, len(s), len(s)+len(t), middle, h2, pow2, m2)
    #@log print(f'found2={found2}')
    if not ans_eq(found1, found2) or (found1.len == 0 and found2.len == 0):
      right = middle-1
    else:
      left = middle+1
    middle = mid(left, right)
    if ans_eq(found1, found2) and found1.len > ans.len:
      ans = found1
    if left > right:
      break
  return ans

for line in sys.stdin.readlines():
  s, t = line.split()
  ans = solve(s, t)
  print(ans.i, ans.j, ans.len)
