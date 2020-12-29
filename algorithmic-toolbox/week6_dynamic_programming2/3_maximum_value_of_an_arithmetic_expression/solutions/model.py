import sys


def calc(a, b, op):
  if op == '*':
    return a * b
  elif op == '+':
    return a + b
  else:
    return a - b


def min_max(mins, maxs, ops, i, j): 
  _min = sys.maxsize
  _max = -sys.maxsize - 1 
  for k in range(i, j):
    a = calc(mins[i][k], mins[k+1][j], ops[k])
    b = calc(mins[i][k], maxs[k+1][j], ops[k])
    c = calc(maxs[i][k], mins[k+1][j], ops[k])
    d = calc(maxs[i][k], maxs[k+1][j], ops[k])
    _min = min(_min, a, b, c, d)
    _max = max(_max, a, b, c, d)
  return (_min, _max)


def solve(exp):
  if len(exp) == 0:
    return 0
  if len(exp) == 1:
    return int(exp)
  nums = []
  ops = []
  for c in range(0, len(exp), 2):
    nums.append(int(exp[c]))
  for c in range(1, len(exp), 2):
    ops.append(exp[c])
  min = [[0]*len(nums) for _ in range(len(nums))]
  max = [[0]*len(nums) for _ in range(len(nums))]
  for i in range(len(nums)):
    min[i][i] = nums[i]
    max[i][i] = nums[i]
  for c in range(len(nums)-1):
    j = c+1
    for i in range(len(nums)-j):
      min[i][j], max[i][j] = min_max(min, max, ops, i, j)
      j = j+1
  return max[0][len(nums)-1]


exp = input()
print(solve(exp))
