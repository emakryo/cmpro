import random
random.seed(0)
t = 3
print(t)
for i in range(t):
    n = 1000000
    k = random.randint(0, 100)
    v = "".join(random.choices("AB", weights=[1, 9], k=n))
    print(n, k)
    print(v)

