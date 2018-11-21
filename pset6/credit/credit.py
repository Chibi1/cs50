# implements credit card validator
import cs50
import sys



def main():
    while (True):
        numStr = cs50.get_string("Number: ")
        if numStr.isnumeric():
            break

    numLen = len(numStr)


    """loop through digits starting from second last digit"""
    digits = []
    for i in range(numLen - 2, -1, -2):
        digit = int(numStr[i]) # convert digit to int
        digit *= 2
        digitStr = str(digit) # convert digit back to string to prepare for extension to digits array
        digits.extend(digitStr)
    # print(f"{digits}")

    """sum digits"""
    firstSum = 0
    for i in range(len(digits)):
        digits[i] = int(digits[i]) # convert back to int
        firstSum += digits[i]

    """loop through digits starting from last digit"""
    _digits = []
    for i in range(numLen - 1, -1, -2):
        _digits.append(numStr[i])
    # print(f"{_digits}")

    """sum second digits"""
    secondSum = firstSum
    for i in range(len(_digits)):
        _digits[i] = int(_digits[i]) # convert back to int
        secondSum += _digits[i]

    # print(f"{type(numLen)}")
    # print(f"{type(numStr[:2])}")
    # print(f"{type(secondSum)}")

    """check whether last digit of second sum is 0"""
    secondSumStr = str(secondSum)
    # print(f"{secondSumStr[-1]}")
    if int(secondSumStr[-1]) != 0:
        print("INVALID")

    """VISA, MASTERCARD or AMEX"""
    if (numLen == 13 or numLen == 16) and int(numStr[0]) == 4:
        print("VISA")
    elif numLen == 15 and (int(numStr[:2]) == 34 or int(numStr[:2]) == 37):
        print("AMEX")
    elif numLen == 16 and int(numStr[:2]) >= 51 and int(numStr[:2]) <= 55:
        print("MASTERCARD")
    else:
        print("INVALID")





if __name__ == "__main__":
    main()