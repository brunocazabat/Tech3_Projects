#! /usr/bin/env python3
# coding: utf-8

import os
import sys
import base64
from Crypto.Cipher import AES

def decryptEcb(ciphertext, key):
    try:
        cipher = AES.new(key, AES.MODE_ECB)
        txt = cipher.decrypt(ciphertext)
        return txt
    except Exception as e:
        print(e)
        sys.exit(84)

def main():
    try:
        if (len(sys.argv) != 2):
            sys.exit(84)
        if (os.stat(sys.argv[1]).st_size == 0):
            sys.exit(84)
        f = open(sys.argv[1], 'r')
        encodedKey = f.readline().rstrip()
        key = bytes.fromhex(encodedKey).decode('utf-8')
        encryptedContent = ""
        for line in f:
            strippedLine = line.replace("\n", " ")
            encryptedContent += strippedLine
        decryptedContent = base64.b64decode(encryptedContent)
        result = decryptEcb(decryptedContent, key)
        resultEncoded = base64.b64encode(result)
        print(resultEncoded)
        f.close()
        sys.exit(0)
    except Exception as e:
        print(e)
        sys.exit(84)

if __name__ == "__main__":
    main()