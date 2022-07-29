import sys

def fibonacci(n: int) -> int:
    if n in (0, 1):
        return n
    return fibonacci(n-1) + fibonacci(n-2)

n = int(sys.argv[1])
ans = fibonacci(n)
print(f"F({n}) = {ans}")
