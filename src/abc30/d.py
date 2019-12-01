N, a = [int(x) for x in input().split()]
k = int(input())
b = [int(x) for x in input().split()]

a = a - 1;
b = [x-1 for x in b]

def find_loop(i, m, b, seen):
    if i in seen:
        return i

    seen[i] = m
    return find_loop(b[i], m+1, b, seen)

def main():
    global k
    seen = {}
    loop_start = find_loop(a, 0, b, seen)

    v = [0] * len(seen)
    for j, m in seen.items():
        v[m] = j

    until_loop = seen[loop_start]
    n_loop = len(seen) - until_loop
    if k >= until_loop:
        k = until_loop + (k - until_loop) % n_loop

    print(b[v[k-1]]+1)



main()
