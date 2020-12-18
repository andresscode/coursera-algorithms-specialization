import sys


def divide(begin, end, right=False):
  pivot = int((end-begin)/2) + 1
  if right:
    pivot = pivot + begin
  print(f'pivot={pivot}')
  if end - begin <= 1:
    return
  print('Less or greater')
  answer = int(input())
  if answer == 1:
    divide(begin, pivot)
  else:
    divide(pivot, end, True)


divide(1, int(sys.argv[1]))
