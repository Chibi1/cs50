from cs50 import get_int
import sys

def main():
    """prints half pyramids of specified height"""
    while(True):
        integer = get_int("Height: ")
        if integer == 0:
            sys.exit()
        if integer > 0 and integer < 24:
            break

    """draw pyramid"""
    for i in range(integer):
        for j in range(1, integer * 2 + 3):
            if j < integer - i:
                print(" ", end="")
            elif j >= integer - i and j < integer + 1:
                print("#", end="")
            elif j >= integer + 1 and j < integer + 3:
                print(" ", end="")
            elif j >= integer - 3 and j < integer + i + 4:
                print("#", end="")
        print("")




if __name__ == "__main__":
    main()