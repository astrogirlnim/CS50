# Include libraries
from cs50 import get_int


def main():
    while True:
        height = get_int("Height: ")
        if height <= 8 and height >= 1:
            break

    for rows in range(1, height + 1):
        # left pyramid
        for spaces in range(0, height-rows):
            print(" ", end="")  # print whitespaces

        for columns in range(0, rows):
            print("#", end="")

        print("  ", end="")

        # right pyramid
        for columns in range(0, rows):
            print("#", end="")

        print()


if __name__ == "__main__":
    main()
