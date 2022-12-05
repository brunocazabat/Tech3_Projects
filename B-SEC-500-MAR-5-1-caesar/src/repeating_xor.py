#! /usr/bin/env python3
# coding: utf-8
import os
import sys
import re
import string

def check_file(file):
    try:
        open(file, "r")
        return True
    except IOError:
        return False

def check_hexa(value):
    for letters in value:
        if letters not in string.hexdigits and letters is not '\n':
            return False
    return True

def check_args():
    lines = []
    if len(sys.argv) is not 2 or check_file(sys.argv[1]) is not True:
        exit(84)
    file = open(sys.argv[1], "r")
    content = file.readlines()
    lines = content
    if len(lines) is 0 or check_hexa(lines[0]) is not True:
        exit(84)
    if (len(lines[0]) - 1) % 2 is not 0:
        exit(84)
    file.close()
    return lines

def repeating_xor(message, key):
    index, output = 0, b''
    for byte in message:
        output += bytearray([int(byte, 16) ^ int(key[index], 16)])
        if (index < len(key) - 1):
            index += 1
        else:
            index = 0
    string = output.hex().replace('00', 'O').replace('01', '1').replace('02', '2').replace('03', '3').replace('04', '4').replace('05', '5').replace('06', '6').replace('07', '7').replace('08', '8').replace('09', '9').replace('0a', 'a').replace('0b', 'b').replace('0c', 'c').replace('0d', 'd').replace('0e', 'e').replace('0f', 'f').replace('O', '0')
    return string.upper()

def main():
    try:
        if (len(sys.argv) != 2):
            sys.exit(84)
        if (os.stat(sys.argv[1]).st_size == 0):
            sys.exit(84)
        lines = check_args()
        key = re.sub(r'\s', "", lines[0])
        message = re.sub(r'\s', "", lines[1])
        print(repeating_xor(message, key))
        sys.exit(0)
    except Exception as e:
        sys.exit(84)

if __name__ == "__main__":
    main()