"""Implement a program that encrypts messages using Vigenère’s cipher"""

import cs50
import sys



def main():
    """Check for one argument"""
    if len(sys.argv) > 2:
        print("error: Program only accepts one argument")
        sys.exit(1)

    """Check whether argument is alpha"""
    if not sys.argv[1].isalpha():
        print("error: Argument must only contain alphabetical characters")
        sys.exit(1)

    key = sys.argv[1]

    """get string from user"""
    plaintext = cs50.get_string("plaintext: ")

    ALPHALEN = 26
    keyLen = len(key)
    k = []

    """find integer values of key"""
    for i in key:
        if ord(i) >= ord("A") and ord(i) <= ord("Z"):
            k.append(ord(i) - 65)                # k is an int array
        elif ord(i) >= ord("a") and ord(i) <= ord("z"):
            k.append(ord(i) - 97)               # k is an int array
    # print(f"{k}")


    j = 0
    cipher = []

    """perform key additions on cipher"""
    for i, l in enumerate(plaintext):
        if l.isalpha():
            # print(f"{i}")

            """build up cipher string"""
            if plaintext[i].isupper():
                cipher.append(chr((ord(plaintext[i]) + k[j]))) # convert plain text chars to ascii, then add key then convert back to ascii
                if ord(cipher[i]) > 90:            # wrapping implementation
                    cipher[i] = chr(ord(cipher[i]) - 26)

            elif plaintext[i].islower():
                cipher.append(chr((ord(plaintext[i]) + k[j]))) # convert plain text chars to ascii, then add key then convert back to ascii
                if ord(cipher[i]) > 122:            # wrapping implementation
                    cipher[i] = chr(ord(cipher[i]) - 26)
            j += 1

        else:
            """if plain text char isnt alpha"""
            cipher.append(plaintext[i]) # append as is

        """reset j at end of key"""
        if j == keyLen:
            j = 0

    # print(f"{cipher}")

    ciphertext = "".join(cipher)

    print(f"ciphertext: {ciphertext}")



if __name__ == "__main__":
    main()