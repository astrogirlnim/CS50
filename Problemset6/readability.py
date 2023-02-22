import cs50


def main():
    # Although my code is correct, there seems to be a
    # rounding error in the calculation

    # Ask the user for text
    text = cs50.get_string("Text: ")

    # Calculate number of letters
    L = 0
    for character in text:
        if character.isalpha():
            L += 1

    # Count words and sentences
    W = sum(map(text.count, " ")) + 1
    S = sum(map(text.count, (".", "!", "?")))

    # Apply Coleman-Liau index
    avg_letters = (L/W) * 100
    avg_words = (S/W) * 100

    level = 0.0588 * avg_letters - 0.296 * avg_words - 15.8

    if round(level) < 16 and round(level) >= 1:
        print(f"Grade {round(level)}")
    elif level < 1:
        print(f"Before Grade 1")
    else:
        print(f"Grade 16+")


if __name__ == "__main__":
    main()