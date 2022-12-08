import sys


def factorial(n: int) -> int:
    '''Returns the factorial of `n`.'''
    if n == 0:
        return 1
    return n * factorial(n-1)


n = int(sys.argv[1])
ans = factorial(n)
print(f"{n}! = {ans}")
