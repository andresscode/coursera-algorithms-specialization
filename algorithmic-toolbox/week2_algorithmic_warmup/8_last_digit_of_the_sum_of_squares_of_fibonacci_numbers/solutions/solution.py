def solve(n):
  if n < 2:
    return n
  sums = [0, 1]
  mods = [0, 1]
  fibs = [0, 1]
  i = 2
  while True:
    fibs.append(fibs[i - 2] + fibs[i - 1])
    mods.append(fibs[i] % 10)
    sums.append((sums[i - 2] + sums[i - 1] + 1) % 10)
    if mods[-2] == 0 and mods[-1] == 1:
      break
    i += 1
  return sums[n % (len(mods) - 2)]


print(solve(int(input())))
