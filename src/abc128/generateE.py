import random

n = int(2e5)
# n = 4
q = int(2e5)
# q = 10

print(n, q)

for _ in range(n):
    s = random.randint(0, int(1e9)-1)
    t = random.randint(s, int(1e9))
    x = random.randint(1, int(1e9))
    print(s, t, x)

d = 0
for i in range(q):
    d = random.randint(d+1, int(1e9)-(q-i))
    print(d)
