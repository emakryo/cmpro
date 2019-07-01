import random
t = 3
print(t)
for _ in range(t):
    n = 50
    h = 1000000
    print(n, h)
    x = random.randint(0, 100000)
    a = 0
    b = random.randint(1, h)
    print(x, a, b)
    x = random.randint(0, 100000)
    a = random.randint(0, 99999)
    b = h
    print(x, a, b)
    for _ in range(n-2):
        x = random.randint(0, 100000)
        a = random.randint(0, 20000)
        b = random.randint(40000, h)
        print(x, min(a, b), max(a, b))
