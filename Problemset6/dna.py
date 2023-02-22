# Load libraries
import csv
import sys


def main():
    # Restrict the argument number
    if len(sys.argv) < 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit()

    db = []
    # Read dna sequence database and save
    with open(sys.argv[1], "r") as database:
        reader = csv.DictReader(database)
        db = list(reader)
        STR = reader.fieldnames[1:]  # Short tandem repeat strings

    # Read from the unknown csv
    with open(sys.argv[2]) as sequences:
        unknown_seq = sequences.read().strip()  # read and strip whitespace

    # Initialize empty counter dictionary
    counter = dict(zip(STR, [0] * len(STR)))

    # Iterate through sequence and count consecutive strs
    for sequence in STR:

        length = len(sequence)
        count = 0   # counts consecutive repeats
        max_count = 0  # stores maximum consecutive repeats
        length_seq = len(unknown_seq)

        # Check each amino acid against the sequence
        for i in range(length_seq):
            # ignore the first sequence counted (only count repeat sequences)
            while count > 0:
                count = count - 1

            # Compare unknown sequence substring and person sequence
            if unknown_seq[i:i + length] == sequence:
                while unknown_seq[i:i + length] == unknown_seq[i - length:i]:
                    count += 1
                    i += length  # jump to next segment
            # Update if current count is higher than previous
            if count > max_count:
                max_count = count
                count = 0  # reset count
                i += 1  # move forward by 1

        # store max_count in counter dictionary
        counter[sequence] += max_count + 1

    # Iterate through each person and compare
    for person in db:
        match = 0  # match counter
        for sequence in STR:
            # Compare counts
            if int(counter[sequence]) == int(person[sequence]):
                match += 1

        # compare matches for all STR sequences
        if match == len(STR):
            print(person['name'])
            return

    print("No match")  # catch-all in case no match is found


if __name__ == "__main__":
    main()

