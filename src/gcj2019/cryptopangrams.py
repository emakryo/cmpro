import string

def solve(n, l, xs):
    i = 0
    while xs[i] == xs[i+1]:
        i += 1

    keys = {i+1: find_gcd(xs[i], xs[i+1])}
    for j in range(i+2, l+1):
        keys[j] = xs[j-1] // keys[j-1]

    for j in range(i, -1, -1):
        keys[j] = xs[j] // keys[j+1]

    keys = [keys[j] for j in range(l+1)]
    primes = sorted(set(keys))
    mapping = dict(zip(primes, string.ascii_uppercase))

    return "".join([mapping[k] for k in keys])

def find_gcd(x, y):
    while(y > 0):
        x, y = y, x%y
    return x

def main():
    T = int(input())
    for i in range(T):
        N, L = [int(x) for x in input().split(' ')]
        Xs = [int(x) for x in input().split(' ')]
        print("Case #{}: {}".format(i+1, solve(N, L, Xs)))

if __name__ == "__main__":
    main()
