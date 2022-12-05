#! /usr/bin/env python3
# coding: utf-8

import os
import sys

def getScore(input):
    freq = {
        'a': .08167, 'b': .01492, 'c': .02782, 'd': .04253,
        'e': .12702, 'f': .02228, 'g': .02015, 'h': .06094,
        'i': .06094, 'j': .00153, 'k': .00772, 'l': .04025,
        'm': .02406, 'n': .06749, 'o': .07507, 'p': .01929,
        'q': .00095, 'r': .05987, 's': .06327, 't': .09056,
        'u': .02758, 'v': .00978, 'w': .02360, 'x': .00150,
        'y': .01974, 'z': .00074, ' ': .13000
    }
    score = 0
    for x in input.lower():
        s = freq.get(chr(x), 0)
        score += s
    result = score
    return result

def single_char_xor(input_bytes, char_value):
    output_bytes = b''
    for byte in input_bytes:
        output_bytes += bytes([byte ^ char_value])
    return output_bytes

def singleXorCipher(file):
    fl = file.readline()
    fl = fl.rstrip("\n ")
    cipherText = bytes.fromhex(fl)
    data = []
    list = []
    for key in range(256):
        data = []
        msg = single_char_xor(cipherText, key)
        data.append(hex(key).replace("0x", ""))
        data.append(getScore(msg))
        list.append(data)
    test = sorted(list, key=lambda x: int(x[1]), reverse=True)
    print(test[0][0].upper())

if __name__ == "__main__":
        try:
            if (len(sys.argv) != 2):
                sys.exit(84)
            if (os.stat(sys.argv[1]).st_size == 0):
                sys.exit(84)
            f = open(sys.argv[1], "r")
            singleXorCipher(f)
            sys.exit(0)
        except Exception as e:
            sys.exit(84)