#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


//this file is a substitution cypher
int main(int argc, string argv[])
{
    //get the string and argument numbers
    int n = argc; //number of arguments (after command name)
    int check; //boolean which checks validity of key

    //check to see if there is only one string
    if (n > 2 || n < 2)
    {
        //if multiple or no arguments are returned, then give
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        //convert to lowercase
        int l = strlen(argv[1]); //length of the key

        if (l < 26 || l > 26)
        {
            //check string length
            printf("Key must contain 26 characters.\n");
            check = 0;
            return 1;
        }
        else
        {
            //initialize character count
            int count[30] = {0};

            //check if all characters are letters
            for (int i = 0 ; i < l; i++)
            {
                //see if the key has valid characters
                argv[1][i] = tolower(argv[1][i]);

                if (argv[1][i] < 'a' || argv[1][i] > 'z')
                {
                    //if not a character, return
                    printf("Usage: ./substitution key\n");
                    check = 0;
                    return 1;
                }
                else
                {
                    //generate count index
                    int index = (int) argv[1][i] - 97;
                    count[index]++;
                }
            }

            //check if a character appears more than once
            for (int i = 0; i < 30; i++)
            {
                if (count[i] > 1)
                {
                    return 1;
                }
                else
                {
                    check = 1;
                }
            }

            //if a valid key, convert to a ciper and return the cipher
            if (check == 1)
            {
                string plaintext = get_string("plain text: ");

                //initialize variables
                int l_text = strlen(plaintext); //string length
                char ciphertext[l_text]; //cipher text
                int index = 0; //ASCII index for cipher text

                for (int i = 0; i < l_text; i++)
                {
                    if (isupper(plaintext[i]))
                    {
                        index = (int) plaintext[i] - 65;  //'A' in ASCII is 65
                        ciphertext[i] = (char) toupper(argv[1][index]);
                    }
                    else if (islower(plaintext[i]))
                    {
                        index = (int) plaintext[i] - 97;  //'a' in ASCII is 97
                        ciphertext[i] = (char) tolower(argv[1][index]);
                    }
                    else
                    {
                        //special characters are left alone
                        ciphertext[i] = plaintext[i];
                    }
                }

                //set last character equal to null
                ciphertext[l_text] = '\0';

                printf("ciphertext: %s\n", ciphertext);
                return 0;
            }
        }

    }
}

