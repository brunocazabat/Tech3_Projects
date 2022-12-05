#!/usr/bin/python3

import sys
import base64
import os

def b64tohex():
    hexfile = []
    for line in open(sys.argv[1], "r"):
        hexfile.append(base64.b64decode(line).hex())
    return hexfile

def count_repetitions(ciphertext, index):
    division = []
    for i in range(0, len(ciphertext), 16):
        division.append(ciphertext[i:i+16])
    number_of_repetitions = len(division) - len(set(division))
    line_number = index
    result = {
        'repetitions': number_of_repetitions,
        'line': line_number
    }
    return result

def hex_to_base64(file):
    b64 = base64.b64encode(bytes.fromhex(file)).decode()
    return b64

def main():
    try:
        if (len(sys.argv) != 2):
            sys.exit(84)
        if (os.stat(sys.argv[1]).st_size == 0):
            sys.exit(84)
        hexfile = b64tohex()
        ciphertext = []
        repetitions = []
        for line in hexfile:
            ciphertext.append(bytes.fromhex(line.strip()))
        index = 1
        for cipher in ciphertext:
            repetitions.append(count_repetitions(cipher, index))
            index += 1
        most_repetitions = sorted(repetitions, key=lambda x: x['repetitions'], reverse=True)[0]
        print(most_repetitions['line'])
        sys.exit(0)
    except ValueError:
        sys.exit(84)
    except OSError:
        sys.exit(84)

if __name__ == "__main__":
    main()