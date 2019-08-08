def f(x):
    if x=="Right":
        return ">"
    elif x=="Left":
        return "<"
    else:
        return "A"

s = input().split()
print(" ".join([f(x) for x in s]))
