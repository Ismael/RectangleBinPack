#!/usr/bin/env python

import sys

x = int(sys.argv[1])
y = int(sys.argv[2])
z = int(sys.argv[3])

piezas = [
 (x, y),
 (x, y),
 (x, y),
 (y, y),
 (z, x),
 (z, y),
 (z, y),
]

sorted(piezas, key=lambda x: x[0])
piezas.reverse()

vals = []
for i in piezas:
    for j in i:
        vals.append(str(int(j)))

r = "./BinPackTest 260 180 " + " ".join(vals)

print r

import os
os.system(r)
