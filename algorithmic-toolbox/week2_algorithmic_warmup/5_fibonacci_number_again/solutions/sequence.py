def solve(n, m):
  f = [0, 1]
  mods = [0, 1]
  while True:
    f.append(f[-2] + f[-1])
    mods.append(f[-1] % m)
    if mods[-2] == 0 and mods[-1] == 1:
      break
  return mods[n % (len(mods) - 2)]

a = [int(i) for i in input().split()]
print(solve(a[0], a[1]))
