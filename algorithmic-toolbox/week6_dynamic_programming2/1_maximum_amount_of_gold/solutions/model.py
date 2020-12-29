from itertools import combinations

def fn(w, a):
  max = 0
  for num in a:
    if num <= w and num > max:
      max = num
  for i in range(2, len(a)+1):
    for c in combinations(a, i):
      s = sum(list(c))
      if s <= w and s > max:
        max = s
  return max


w = int(input().split()[0])
a = [int(i) for i in input().split()]

print(fn(w, a))
