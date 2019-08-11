k, x = [int(x) for x in input().split()]
print(" ".join([str(x) for x in range(x-k+1, x+k)]))
