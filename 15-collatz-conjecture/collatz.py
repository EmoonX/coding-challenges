from collections.abc import Generator
import sys


def collatz(n: int) -> Generator[int, None, None]:
    '''Generates next element in the Collatz sequence;
    being it `⌊n/2⌋` if `n` is even, or `3n + 1` if `n` is odd'''
    while True:
        yield n
        if n == 1:
            return
        if n % 2 == 0:
            n //= 2
        else:
            n = 3*n + 1


n = int(sys.argv[1])
last = n
steps = -1
for k in collatz(n):
    color = (
        2 if k == n or k == 1
        else 1 if k > last
        else 3
    )
    print(f"\x1b[3{color};1m{k}\x1b[0m", end=' ')
    last = k
    steps += 1

print(f"\nTotal steps: {steps}")
