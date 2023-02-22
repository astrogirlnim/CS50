#include "helpers.h"

int corners(int i, int j, int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Inputs are an RGBTRIPLE struct
    //A grayscale makes it so that all color values (red, green, blue) are the same

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Get the average of the rgbt components
            int avg = ((int) image[i][j].rgbtRed + (int) image[i][j].rgbtGreen + (int) image[i][j].rgbtBlue) / 3;

            //Replace color values
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //create temporary variables
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            //convert to sepia
            int sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            int sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            int sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            //replace with sepia colors
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //Find current pixel
            RGBTRIPLE curr_pix = image[j][i];

            //Find the pixel at the opposite side of the row
            RGBTRIPLE opp_pix = image[j][width - i];

            //Switch the pixels
            image[j][i] = opp_pix;
            image[j][width - i] = curr_pix;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Make an image copy to store original pixel values
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    //Iterate and blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (corners(i, j, height, width) == 1)
            {
                //top left corner
                int length = 4;
                RGBTRIPLE colors[length];

                colors[0] = temp[i][j];
                colors[1] = temp[++i][j];
                colors[2] = temp[++i][++j];
                colors[3] = temp[i][++j];

                //sum pixel values
                int sumblue = 0;
                int sumred = 0;
                int sumgreen = 0;

                for (int k = 0; k < length; k++)
                {
                    sumblue = sumblue + colors[k].rgbtBlue;
                    sumgreen = sumgreen + colors[k].rgbtGreen;
                    sumred = sumred + colors[k].rgbtRed;
                }

                //average and replace
                int avgblue = sumblue / length;
                int avgred = sumred / length;
                int avggreen = sumgreen / length;

                image[i][j].rgbtRed = avgred;
                image[i][j].rgbtBlue = avgblue;
                image[i][j].rgbtGreen = avggreen;
            }
            else if (corners(i, j, height, width) == 2)
            {
                //top right corner
                int length = 4;
                RGBTRIPLE colors[length];

                colors[0] = temp[i][j];
                colors[1] = temp[++i][j];
                colors[2] = temp[++i][--j];
                colors[3] = temp[i][--j];

                //sum pixel values
                int sumblue = 0;
                int sumred = 0;
                int sumgreen = 0;

                for (int k = 0; k < length; k++)
                {
                    sumblue = sumblue + colors[k].rgbtBlue;
                    sumgreen = sumgreen + colors[k].rgbtGreen;
                    sumred = sumred + colors[k].rgbtRed;
                }

                //average and replace
                int avgblue = sumblue / length;
                int avgred = sumred / length;
                int avggreen = sumgreen / length;

                image[i][j].rgbtRed = avgred;
                image[i][j].rgbtBlue = avgblue;
                image[i][j].rgbtGreen = avggreen;
            }
            else if (corners(i, j, height, width) == 3)
            {
                //bottom left corner
                int length = 4;
                RGBTRIPLE colors[length];
                colors[0] = temp[i][j];
                colors[1] = temp[--i][j];
                colors[2] = temp[--i][++j];
                colors[3] = temp[i][++j];

                //sum pixel values
                int sumblue = 0;
                int sumred = 0;
                int sumgreen = 0;

                for (int k = 0; k < length; k++)
                {
                    sumblue = sumblue + colors[k].rgbtBlue;
                    sumgreen = sumgreen + colors[k].rgbtGreen;
                    sumred = sumred + colors[k].rgbtRed;
                }

                //average and replace
                int avgblue = sumblue / length;
                int avgred = sumred / length;
                int avggreen = sumgreen / length;

                image[i][j].rgbtRed = avgred;
                image[i][j].rgbtBlue = avgblue;
                image[i][j].rgbtGreen = avggreen;
            }
            else if (corners(i, j, height, width) == 4)
            {
                //bottom right corner
                int length = 4;
                RGBTRIPLE colors[length];

                colors[0] = temp[i][j];
                colors[1] = temp[--i][j];
                colors[2] = temp[--i][--j];
                colors[3] = temp[i][--j];

                //sum pixel values
                int sumblue = 0;
                int sumred = 0;
                int sumgreen = 0;

                for (int k = 0; k < length; k++)
                {
                    sumblue = sumblue + colors[k].rgbtBlue;
                    sumgreen = sumgreen + colors[k].rgbtGreen;
                    sumred = sumred + colors[k].rgbtRed;
                }

                //average and replace
                int avgblue = sumblue / length;
                int avgred = sumred / length;
                int avggreen = sumgreen / length;

                image[i][j].rgbtRed = avgred;
                image[i][j].rgbtBlue = avgblue;
                image[i][j].rgbtGreen = avggreen;

            }
            else
            {
                if (i == 0 || j == 0 || i == height || j == width)
                {
                    //edge detection

                    //Store values of all neighboring pixels
                    int length = 6;
                    RGBTRIPLE colors[length];

                    //i corresponds to columns, j to rows
                    if (i == 0)
                    {
                        //Get each row of pixels
                        int n = 0; //position relative to jth pixel
                        do
                        {
                            //top row
                            colors[n] = temp[i + n][j + n];

                            //bottom row
                            colors[2 + n] = temp[i + n][j];

                            //base row
                            colors[4 + n] = temp[i + n][j - n];

                            n++;
                        }
                        while (n < 1);

                        //sum pixel values
                        int sumblue = 0;
                        int sumred = 0;
                        int sumgreen = 0;

                        for (int k = 0; k < length; k++)
                        {
                            sumblue = sumblue + colors[k].rgbtBlue;
                            sumgreen = sumgreen + colors[k].rgbtGreen;
                            sumred = sumred + colors[k].rgbtRed;
                        }

                        //average and replace
                        int avgblue = sumblue / length;
                        int avgred = sumred / length;
                        int avggreen = sumgreen / length;

                        image[i][j].rgbtRed = avgred;
                        image[i][j].rgbtBlue = avgblue;
                        image[i][j].rgbtGreen = avggreen;
                    }
                    if (i == width)
                    {
                        //Get each row of pixels
                        int n = 0; //position relative to jth pixel
                        do
                        {
                            //top row
                            colors[n] = temp[i - n][j + n];

                            //bottom row
                            colors[2 + n] = temp[i - n][j];

                            //base row
                            colors[4 + n] = temp[i - n][j - n];

                            n++;
                        }
                        while (n < 1);

                        //sum pixel values
                        int sumblue = 0;
                        int sumred = 0;
                        int sumgreen = 0;

                        for (int k = 0; k < length; k++)
                        {
                            sumblue = sumblue + colors[k].rgbtBlue;
                            sumgreen = sumgreen + colors[k].rgbtGreen;
                            sumred = sumred + colors[k].rgbtRed;
                        }

                        //average and replace
                        int avgblue = sumblue / length;
                        int avgred = sumred / length;
                        int avggreen = sumgreen / length;

                        image[i][j].rgbtRed = avgred;
                        image[i][j].rgbtBlue = avgblue;
                        image[i][j].rgbtGreen = avggreen;
                    }
                    if (j == 0)
                    {
                        //first row
                        //Get each row of pixels
                        int n = 0; //position relative to jth pixel
                        do
                        {
                            //top row
                            colors[n] = temp[i + n][j + n];

                            //bottom row
                            colors[2 + n] = temp[i][ j + n];

                            //base row
                            colors[4 + n] = temp[i - n][j + n];

                            n++;
                        }
                        while (n < 1);

                        //sum pixel values
                        int sumblue = 0;
                        int sumred = 0;
                        int sumgreen = 0;

                        for (int k = 0; k < length; k++)
                        {
                            sumblue = sumblue + colors[k].rgbtBlue;
                            sumgreen = sumgreen + colors[k].rgbtGreen;
                            sumred = sumred + colors[k].rgbtRed;
                        }

                        //average and replace
                        int avgblue = sumblue / length;
                        int avgred = sumred / length;
                        int avggreen = sumgreen / length;

                        image[i][j].rgbtRed = avgred;
                        image[i][j].rgbtBlue = avgblue;
                        image[i][j].rgbtGreen = avggreen;
                    }
                    if (j == width)
                    {
                        //last row
                        //Get each row of pixels
                        int n = 0; //position relative to jth pixel
                        do
                        {
                            //top row
                            colors[n] = temp[i + n][j - n];

                            //bottom row
                            colors[2 + n] = temp[i][j - n];

                            //base row
                            colors[4 + n] = temp[i - n][j - n];

                            n++;
                        }
                        while (n < 1);

                        //sum pixel values
                        int sumblue = 0;
                        int sumred = 0;
                        int sumgreen = 0;

                        for (int k = 0; k < length; k++)
                        {
                            sumblue = sumblue + colors[k].rgbtBlue;
                            sumgreen = sumgreen + colors[k].rgbtGreen;
                            sumred = sumred + colors[k].rgbtRed;
                        }

                        //average and replace
                        int avgblue = sumblue / length;
                        int avgred = sumred / length;
                        int avggreen = sumgreen / length;

                        image[i][j].rgbtRed = avgred;
                        image[i][j].rgbtBlue = avgblue;
                        image[i][j].rgbtGreen = avggreen;
                    }
                }
                else
                {
                    //Store values of all neighboring pixels
                    int length = 9;
                    RGBTRIPLE colors[length];

                    //Get each row of pixels
                    int n = -1; //position relative to jth pixel
                    do
                    {
                        //top row
                        colors[1 + n] = temp[i + 1][j + n];

                        //bottom row
                        colors[4 + n] = temp[i - 1][j + n];

                        //base row
                        colors[6 + n] = temp[i][j + n];

                        n++;
                    }
                    while (n < 1);

                    //sum pixel values
                    int sumblue = 0;
                    int sumred = 0;
                    int sumgreen = 0;

                    for (int k = 0; k < length; k++)
                    {
                        sumblue = sumblue + colors[k].rgbtBlue;
                        sumgreen = sumgreen + colors[k].rgbtGreen;
                        sumred = sumred + colors[k].rgbtRed;
                    }

                    //Average summed pixel values
                    int avgblue = sumblue / length;
                    int avgred = sumred / length;
                    int avggreen = sumgreen / length;

                    //Replace original pixel
                    image[i][j].rgbtRed = avgred;
                    image[i][j].rgbtBlue = avgblue;
                    image[i][j].rgbtGreen = avggreen;
                }
            }
        }
    }
    return;
}

//Detect corners for blurring
int corners(int i, int j, int height, int width)
{
    if (i == 0 && j == 0)
    {
        return 1; //top left corner
    }
    else if (i == 0 && j == width)
    {
        return 2; //top right corner
    }
    else if (i == height && j == 0)
    {
        return 3; //bottom left corner
    }
    else if (i == height && j == width)
    {
        return 4; //bottom right corner
    }
    return 0;
}