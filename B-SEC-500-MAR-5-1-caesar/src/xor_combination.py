#! /usr/bin/env python3
# coding: utf-8

import os
import sys

def hex_to_base64(f):
    tab = []
    for x in f:
        tab.append(x)
    tab[0] = tab[0].rstrip("\n ")
    tab[1] = tab[1].rstrip("\n ")
    if (len(tab[0]) != len(tab[1])):
        sys.exit(84)
    else:
        test = hex(int(tab[0], 16) ^ int(tab[1], 16)).replace("0x", "")
        print(test.upper())

if __name__ == "__main__":
    try:
        if (len(sys.argv) != 2):
            sys.exit(84)
        if (os.stat(sys.argv[1]).st_size == 0):
            sys.exit(84)
        f = open(sys.argv[1], "r")
        hex_to_base64(f)
        sys.exit(0)
    except Exception as e:
        sys.exit(84)