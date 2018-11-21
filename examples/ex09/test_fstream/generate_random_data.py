#! /usr/bin/env python3

import random

for i in range(90):
    print("09804{:03d}\t{:3d}\t{:3d}".format(i, random.randrange(50, 100),
                                             random.randrange(50, 100)))
