#! /usr/bin/env python3
# coding: utf-8

import sys
import os
from base64 import b64encode

def hex_to_base64(f):
    file = f.readline()
    file.rstrip("\n")
    file.rstrip(" ")
    try:
        b64 = b64encode(bytes.fromhex(file)).decode()
        print(b64)
    except:
        sys.exit(84)

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