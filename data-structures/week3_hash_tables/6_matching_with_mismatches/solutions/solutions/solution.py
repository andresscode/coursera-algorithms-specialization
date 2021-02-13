# python3

import sys

m1 = 1000000000039
m2 = 1000000000061
x = 31

def hashes(s, m): 
  h = []
  h.append(0)
  for i in range(1, len(s)+1):
    h.append((x * h[i-1] + ord(s[i-1])) % m)
  return h

def get_hashes(s, mods):
  h = []
  for mod in mods:
    h.append(hashes(s, mod))
  return h
  
def pows(n, m): 
  p = []
  p.append(1)
  for i in range(1, n+1):
    p.append((p[i-1]*x)%m)
  return p

def get_pows(n, mods):
  p = []
  for mod in mods:
    p.append(pows(n, mod))
  return p

def hash(h, i, j, pow, mod):
  return (h[i+j] - pow[j] * h[i]) % mod

def compute_hashes(th, tl, pl, pow, mod):
  h = []
  for i in range((tl-pl)+1):
    h.append(hash(th, i, pl, pow, mod)) 
  return h

def get_base_hashes(ths, tl, pl, pows, mods):
  res = []
  for i, th in enumerate(ths):
    res.append(compute_hashes(th, tl, pl, pows[i], mods[i]))
  return res

def get_patt_hashes(phs, i, j, pows, mods):
  res = []
  for k, h in enumerate(phs):
    res.append(hash(h, i, j, pows[k], mods[k]))
  return res

def print_list(label, data):
  print(f'{label} -> ', end=' ')
  print(*data)

def print_lists(label, lists):
  for l in lists:
    print_list(label, l)

def mid(l, r):
  return int((l+r)/2)

def equal_patt(ths, tl, patt_hs, step, pows, mods):
  return hash(ths[0], tl, step, pows[0], mods[0]) == patt_hs[0] and \
    hash(ths[1], tl, step, pows[1], mods[1]) == patt_hs[1]

def equal_sect(ths, tl, phs, pl, step, pows, mods):
  return hash(ths[0], tl, step, pows[0], mods[0]) == hash(phs[0], pl, step, pows[0], mods[0]) and \
    hash(ths[1], tl, step, pows[1], mods[1]) == hash(phs[1], pl, step, pows[1], mods[1])

def valid_misses(text, ths, t_left, pattern, phs, step, pows, mods, k):
  stack = []
  counter = 0
  stack.append((t_left, (t_left+step)-1, 0, step-1, step))
  while len(stack) > 0:
    tl, tr, pl, pr, st = stack.pop()
    tm = mid(tl, tr)
    #@log print(f'{text[tl:tl+st]} [mid={text[tm]}]', end=' ')
    pm = mid(pl, pr)
    #@log print(f'|| {pattern} [mid={pattern[pm]}]')
    if text[tm] != pattern[pm]:
      counter = counter + 1
      if counter > k:
        return False
    tmp = pm-1
    if pl <= tmp: 
      _s = (tmp-pl)+1
      if not equal_sect(ths, tl, phs, pl, _s, pows, mods):
        stack.append((tl, (tl+_s)-1, pl, (pl+_s)-1, _s))
    tmp = pm+1
    if pr >= tmp:
      _s = (pr-tmp)+1
      if not equal_sect(ths, tm+1, phs, pm+1, _s, pows, mods):
        stack.append((tm+1, tr, pm+1, pr, _s))
  return counter <= k

  
def solve(k, text, pattern):
  mods = [m1, m2]
  patt_len = len(pattern)

  #@log print('*********************************************************')
  if patt_len > len(text):
    return []
  if k >= patt_len:
    return range((len(text)-patt_len)+1)

  # Precomputing hashes
  ths = get_hashes(text, mods)
  #@log print_lists(f'{text}[{len(text)}]', ths)
  phs = get_hashes(pattern, mods)
  #@log print_lists(f'{pattern}[{patt_len}]', phs)

  # Precomputing pows
  _pows = get_pows(patt_len, mods)
  #@log print_lists('pows', _pows)

  # Precomputing text hashes based on pattern length
  #base_hs = get_base_hashes(ths, len(text), patt_len, _pows, mods)
  #print_lists(f'base[{len(base_hs[0])}]', base_hs)

  # Precompute pattern hashes
  patt_hs = get_patt_hashes(phs, 0, patt_len, _pows, mods)
  #@log print(f'pattern_hashes -> {" ".join(str(i) for i in patt_hs)}')
  
  result = []
  for i in range((len(text)-patt_len)+1):
    #@log print(f'[checking] -> {text[i:i+patt_len]} == {pattern}')
    if not equal_patt(ths, i, patt_hs, patt_len, _pows, mods):
      if valid_misses(text, ths, i, pattern, phs, patt_len, _pows, mods, k):
        result.append(i)
    else:
      #@log print('OK')
      result.append(i)
  return result

for line in sys.stdin.readlines():
  k, t, p = line.split()
  ans = solve(int(k), t, p)
  print(len(ans), *ans)
