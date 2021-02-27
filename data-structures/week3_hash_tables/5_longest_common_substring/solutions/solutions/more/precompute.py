# python3

import sys
from collections import namedtuple

Answer = namedtuple('answer_type', 'i j len')

m1 = int(1e9+7)
m2 = int(1e9+9)
x = 263 

def poly_hash(s, p, x):
  hash = 0
  for i in range(len(s)-1, 0, -1):
    hash = (hash*x+ord(s[i]))%p
  return hash

def precompute_hashes(t, l, p, x):
  h = list(range(len(t)-l+1))
  s = t[len(t)-l:]
  h[-1] = poly_hash(s,p,x)
  y = 1
  for i in range(1, l+1):
    y = (y*x) % p
  for i in range(len(t)-l-1, -1, -1):
    h[i] = (x*h[i+1]+ord(t[i])-y*ord(t[i+l-1]))%p
  return h

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

def solve(s, t):
  ans = Answer(0,0,0)

  left = 1
  right = min(len(s), len(t))
  middle = mid(left, right)

  while True:
    #@log print(f's={s} l={middle}')
    s_hashes = precompute_hashes(s, middle, m1, x)
    #@log print('s_hashes -> ', end=' ')
    #@log print(*s_hashes)
    
    #@log print(f't={t} l={middle}')
    t_hashes = precompute_hashes(t, middle, m1, x)
    #@log print('t_hashes -> ', end=' ')
    #@log print(*t_hashes)
    right = -1
    if left > right:
      break
  return ans

def sol2(s, t):
  ans = Answer(0, 0, 0)

  sh1 = hashes(s, m1)
  #@log print('sh1 -> ', end=' ')
  #@log print(*sh1)
  sh2 = hashes(s, m2)
  #@log print('sh2 -> ', end=' ')
  #@log print(*sh2)
  th1 = hashes(t, m1)
  #@log print('th1 -> ', end=' ')
  #@log print(*th1)
  th2 = hashes(t, m2)
  #@log print('th2 -> ', end=' ')
  #@log print(*th2)
  pow1 = pows(max(len(s), len(t)), m1)
  #@log print('pow1 -> ', end=' ')
  #@log print(*pow1)
  pow2 = pows(max(len(s), len(t)), m2)
  #@log print('pow2 -> ', end=' ')
  #@log print(*pow2)

  left = 1
  right = min(len(s), len(t))
  middle = mid(left, right)

  while True:
    #@log print(f'left={left} right={right} middle={middle}')
    for i in range(len(s)-middle+1):
      print(hash(sh1, i, middle, pow1), end=' ')
    print()
    for i in range(len(t)-middle+1):
      print(hash(th1, i, middle, pow1), end=' ')
    print()
    right = -1 
    if left > right:
      break
  return ans

for line in sys.stdin.readlines():
  s, t = line.split()
  ans = solve(s, t)
  print(ans.i, ans.j, ans.len)
