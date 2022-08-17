import sys
import random

random.seed(int(sys.argv[1]))

n = 10
s = set()
for i in range(10):
    s.add((random.randint(1, 20), random.randint(1, 20)))

print(len(s))
for x, y in s:
    print(x, y)
