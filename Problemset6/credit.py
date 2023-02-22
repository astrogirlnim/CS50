from cs50 import get_int


def check_first_digits(number):

    # Returned Value Key:
    # 1 - American Express
    # 2 - Mastercard
    # 3 - Visa
    # 0 - Other/undefined

    american_express = [34, 37]
    mastercard = [51, 52, 53, 54, 55]

    # Convert the number to a string to check digits
    if int(str(number)[0]) == 4:
        return 3
    elif int(str(number)[:2]) in american_express:
        return 1
    elif int(str(number)[:2]) in mastercard:
        return 2
    else:
        return 0


def luhn_algorithm(number):

    # Apply Luhn's Algorithm to check validity

    sum_even = 0  # Even number sum
    sum_odd = 0   # Odd number sum

    # Even digits
    for digits in str(number)[-2::-2]:
        doubled_digits = 2 * int(digits)
        for digit in str(doubled_digits):
            sum_even += int(digit)

    # Odd digits
    for digits in str(number)[-1::-2]:
        sum_odd += int(digits)

    # Check the last digit of the total sum
    if int(str(sum_even + sum_odd)[-1]) == 0:
        return 1
    else:
        return 0


def main():

    # get initial number
    while True:
        number = get_int("Number: ")
        if number > 1000000000 or number < 10000000000000000:
            break  # break if number of valid length

    luhn_algorithm(number)

    # Check number according to helper functions
    if check_first_digits(number) == 0 or luhn_algorithm(number) == 0:
        print("INVALID")
    elif check_first_digits(number) == 1:
        print("AMEX")
    elif check_first_digits(number) == 2:
        print("MASTERCARD")
    elif check_first_digits(number) == 3:
        print("VISA")


if __name__ == "__main__":
    main()
