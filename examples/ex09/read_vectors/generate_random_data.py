#! /usr/bin/env python3

from random import randrange

for i in range(100):
    n = randrange(10)
    f = "{}\t" * n + "*"
    v = [randrange(10) for j in range(n)]
    print(f.format(*v))
