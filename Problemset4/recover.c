#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        //reject if there are more than 2 command line arguments
        printf("Usage: ./recover image");
        return 1;
    }

    //Try to open the memory card file
    FILE *input = fopen(argv[1], "r");


    if (input == NULL)
    {
        printf("Forensic image could not be opened.");
        return 1;
    }

    //byte to store 3 bytes of data
    BYTE temp[4];

    //boolean to indicate a jpeg
    int jpeg_tracker = 0;
    int jpeg_counter = 0; //number to keep track of new jpegs
    int jpeg_total = 1; //number to keep track of total jpegs

    //loop to extract every byte
    while (1)
    {
        fread(temp, sizeof(uint8_t), 4, input);

        //indicator for jpeg
        if ((int) temp[0] == 255 && (int) temp[1] == 216 && (int) temp[2] == 255)
        {
            int firstBit = temp[3] & 1;
            int secndbit = temp[3] & 2;
            int thrdbit = temp[3] & 3;
            int forthbit = temp[3] & 4;

            //check 4th byte's first 4 bits
            if (firstBit == 1 && secndbit == 1 && thrdbit == 1 && forthbit == 0)
            {
                //update boolean
                jpeg_tracker = 1;
                jpeg_counter++;
                jpeg_total++;
            }
        }


        if (jpeg_tracker == 1)
        {
            //name for the new file
            char str[8];

            sprintf(str, "%i.jpg", jpeg_total);
            FILE *output = fopen(str, "w");
            fwrite(temp, sizeof(uint8_t), 1, output);

            if (jpeg_counter > 2)
            {
                jpeg_counter = 0;
                jpeg_tracker = 0;
                fclose(output);
            }
        }
        else if (feof(input))
        {
            break;
        }
    }

    fclose(input);
    return 0;
}