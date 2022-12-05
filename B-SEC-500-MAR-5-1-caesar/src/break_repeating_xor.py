#! /usr/bin/env python3
# coding: utf-8

import os
import sys
import math
from base64 import b64encode

def hex_to_base64(f):
    try:
        b64 = b64encode(bytes.fromhex(f)).decode()
    except Exception as e:
        sys.exit(84)

def hammingDistance(a, b):
    dist = 0
    for ab, bb in zip (a, b):
        diff = ab ^ bb
        dist += sum([1 for bit in bin(dff) if bit == '1'])
    return dist

def keyLength(ciphertext):
    lowest = None
    bestKeyLength = None
    for key in range(5, 41):
        avg = []
        start = 0
        end = start + key
        while (42):
            first_chunk = ciphertext[start:end]
            second_chunk = ciphertext[start + key:end + key]
            if (len(second_chunk) > key):
                break
            distance = hammingDistance(first_chunk, second_chunk)
            norm = distance / key
            avg.append(norm)
            start = end + key
            end = start + key
            average = sum(avg) / len(avg)
            avg = []
            if lowest == None or average < lowest:
                lowest = average
                bestKeyLength = key
    return bestKeyLength

def transpose_chunks_by_keylength(keylength, ciphertext):
    chunks = dict.fromkeys(range(keylength))

    i = 0
    for octet in data:
        if (i == keylength): i = 0
        if (chunks[i] == None): chunks[i] = []
        chunks[i].append(octet)
        i += 1
    return chunks

def getKey(blocks):
    common = 'ETAOIN SHRDLU'
    key = ''

    for i in blocks:
        current_high_score = 0
        current_key_char = ''

        for j in range(127):
            x = [j ^ the_bytes for the_bytes in blocks[i]]
            b = bytes(x)
            b_str = str(b, 'utf-8')
            score = 0
            for k in b_str.upper():
                if k in common:
                    score += 1
            if score > current_high_score:
                current_high_score = score
                current_key_char = chr(j)
            key += current_key_char
    return key

def detect_single_xor(arrayofbyte):
    character_frequencies = {
        'a': .08167, 'b': .01492, 'c': .02782, 'd': .04253,
        'e': .12702, 'f': .02228, 'g': .02015, 'h': .06094,
        'i': .06094, 'j': .00153, 'k': .00772, 'l': .04025,
        'm': .02406, 'n': .06749, 'o': .07507, 'p': .01929,
        'q': .00095, 'r': .05987, 's': .06327, 't': .09056,
        'u': .02758, 'v': .00978, 'w': .02360, 'x': .00150,
        'y': .01974, 'z': .00074, ' ': .13000
    }
    line, keyvalue = max(((line, key) for line in range(len(arrayofbyte)) for key in range(256)),
        key = lambda byte:
        sum(character_frequencies[count] for count in map(lambda count:
            chr(count ^ byte[1]), arrayofbyte[byte[0]]) if count in character_frequencies))
    keyvalue = bytes([keyvalue]).hex()
    line = str(line + 1)
    string = (line + " " + keyvalue)
    return string

def breakRepeatingXor(st):
    decodedStr = hex_to_base64(st)
    keyLength = keyLength(decodedStr)
    chunks = transpose_chunks_by_keylength(keyLength, ciphertext)
    key = getKey(chunks)
    print(key)

if __name__ == '__main__':
        if (len(sys.argv) != 2):
            sys.exit(84)
        if (os.stat(sys.argv[1]).st_size == 0):
            sys.exit(84)
        f = open(sys.argv[1], 'r')
        buffer = ""
        for line in f:
            strippedLine = line.rstrip()
            buffer += strippedLine
        f.close()
        breakRepeatingXor(buffer)
        sys.exit(0)