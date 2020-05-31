
def solve():
    n = int(input())
    a = [int(x) for x in input().split()]
    for x in a:
        if x==0:
            print(0)
            return

    ans = 1
    for x in a:
        ans *= x
        if ans > 10**18:
            print(-1)
            return

    print(ans)

solve()
