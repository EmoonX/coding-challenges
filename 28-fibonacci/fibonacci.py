import sys

# Dict of F(n) fibonacci values
fib = {0: 0, 1: 1}

def fibonacci(n: int) -> int:
    '''Returns value of `F(n)`, using memoization
    to keep track of previously calculated values.'''
    if not n in fib:
        fib[n] = fibonacci(n-1) + fibonacci(n-2)
    return fib[n]

n = int(sys.argv[1])
ans = fibonacci(n)
print(f"F({n}) = {ans}")
