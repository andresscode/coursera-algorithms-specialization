# python3

import sys
from collections import namedtuple
from difflib import SequenceMatcher

Answer = namedtuple('answer_type', 'i j len')

def solve(s, t):
  match = SequenceMatcher(None, s, t).find_longest_match(0, len(s), 0, len(t))
  return Answer(match.a, match.b, match.size)

for line in sys.stdin.readlines():
  s, t = line.split()
  ans = solve(s, t)
  print(ans.i, ans.j, ans.len)
