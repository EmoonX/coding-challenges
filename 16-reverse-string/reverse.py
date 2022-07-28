# `reversed(s)` is more efficient than `s[::-1] due to
# returning an iterator (instead of creating a whole new list)
s = input()
for c in reversed(s):
    print(c, end='')
print()
