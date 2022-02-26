#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float i = image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed;
            float j = i / 3;
            int n = round(j);

            image[h][w].rgbtBlue = n;
            image[h][w].rgbtGreen = n;
            image[h][w].rgbtRed = n;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float sepiaRed = .393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue;
            float sepiaGreen = .349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue;
            float sepiaBlue = .272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue;

            int sr = round(sepiaRed);
            int sg = round(sepiaGreen);
            int sb = round(sepiaBlue);

            if (sr > 255)
            {
                sr = 255;
            }
            if (sg > 255)
            {
                sg = 255;
            }
            if (sb > 255)
            {
                sb = 255;
            }

            image[h][w].rgbtRed = sr;
            image[h][w].rgbtGreen = sg;
            image[h][w].rgbtBlue = sb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_red;
            float sum_blue;
            float sum_green;
            int counter;
            sum_red = sum_blue = sum_green = counter = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    sum_red += temp[i + k][j + l].rgbtRed;
                    sum_blue += temp[i + k][j + l].rgbtBlue;
                    sum_green += temp[i + k][j + l].rgbtGreen;
                    counter++;
                }
            }
            image[i][j].rgbtRed = round(sum_red / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
            image[i][j].rgbtBlue = round(sum_blue / counter);
        }
    }
    return;
}

void threshold(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            BYTE value = 0;

            if (image[i][j].rgbtRed > 122 || image[i][j].rgbtGreen > 122 || image[i][j].rgbtBlue > 122)
                value = 255;

            image[i][j].rgbtRed = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtBlue = value;
        }

    return;
}

void adaptive_threshold(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE region_sum;

            region_sum.rgbtRed = 0;
            region_sum.rgbtGreen = 0;
            region_sum.rgbtBlue = 0;

            for (int n = -2; n < 3; n++)
                for(int m = -2; m < 3; m++)
                {
                    int x = (j + n < width) ? j + m : width;
                    int y = (i + m < height) ? i + m : height;

                    x = (x <= 0) ? 0 : x;
                    y = (y <= 0) ? 0 : y;

                    region_sum.rgbtRed += image[y][x].rgbtRed;
                    region_sum.rgbtGreen += image[y][x].rgbtGreen;
                    region_sum.rgbtBlue += image[y][x].rgbtBlue;
                }

            region_sum.rgbtRed /= 2;
            region_sum.rgbtGreen /= 2;
            region_sum.rgbtBlue /= 2;

            BYTE value = 0;

            if (image[i][j].rgbtRed > region_sum.rgbtRed && image[i][j].rgbtGreen > region_sum.rgbtGreen && image[i][j].rgbtBlue > region_sum.rgbtBlue)
                value = 255;

            image[i][j].rgbtRed = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtBlue = value;
        }
    return;
}
