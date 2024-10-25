#include "helpers.h"
#include <math.h> // not sure if permitted

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;

            BYTE average = round((blue + green + red) / 3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
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
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;

            int sepiaBlue =
                round((0.272 * (float) red) + (0.534 * (float) green) + (0.131 * (float) blue));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            int sepiaGreen =
                round((0.349 * (float) red) + (0.686 * (float) green) + (0.168 * (float) blue));
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            int sepiaRed =
                round((0.393 * (float) red) + (0.769 * (float) green) + (0.189 * (float) blue));
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            RGBTRIPLE newPixel = {(BYTE) sepiaBlue, (BYTE) sepiaGreen, (BYTE) sepiaRed};
            image[i][j] = newPixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // awful implementation
    RGBTRIPLE oldImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oldImage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];

            /**
             * CORNERS
             */
            // TOP LEFT CORNER
            if (i == 0 && j == 0)
            {
                RGBTRIPLE middleRight = oldImage[i][j + 1];
                RGBTRIPLE bottomMiddle = oldImage[i + 1][j];
                RGBTRIPLE bottomRight = oldImage[i + 1][j + 1];

                BYTE averageBlue = round((pixel.rgbtBlue + middleRight.rgbtBlue +
                                          bottomMiddle.rgbtBlue + bottomRight.rgbtBlue) /
                                         4.0);
                BYTE averageGreen = round((pixel.rgbtGreen + middleRight.rgbtGreen +
                                           bottomMiddle.rgbtGreen + bottomRight.rgbtGreen) /
                                          4.0);
                BYTE averageRed = round((pixel.rgbtRed + middleRight.rgbtRed +
                                         bottomMiddle.rgbtRed + bottomRight.rgbtRed) /
                                        4.0);

                RGBTRIPLE blurredPixel = {averageBlue, averageGreen, averageRed};
                image[i][j] = blurredPixel;
                continue;
            }
            // TOP RIGHT CORNER
            else if (i == 0 && (j == width - 1))
            {
                RGBTRIPLE middleLeft = oldImage[i][j - 1];
                RGBTRIPLE bottomMiddle = oldImage[i + 1][j];
                RGBTRIPLE bottomLeft = oldImage[i + 1][j - 1];

                BYTE averageBlue = round((pixel.rgbtBlue + middleLeft.rgbtBlue +
                                          bottomMiddle.rgbtBlue + bottomLeft.rgbtBlue) /
                                         4.0);
                BYTE averageGreen = round((pixel.rgbtGreen + middleLeft.rgbtGreen +
                                           bottomMiddle.rgbtGreen + bottomLeft.rgbtGreen) /
                                          4.0);
                BYTE averageRed = round((pixel.rgbtRed + middleLeft.rgbtRed + bottomMiddle.rgbtRed +
                                         bottomLeft.rgbtRed) /
                                        4.0);

                RGBTRIPLE blurredPixel = {averageBlue, averageGreen, averageRed};
                image[i][j] = blurredPixel;
                continue;
            }
            // BOTTOM LEFT CORNER
            else if ((i == height - 1) && j == 0)
            {
                RGBTRIPLE topMiddle = oldImage[i - 1][j];
                RGBTRIPLE topRight = oldImage[i - 1][j + 1];
                RGBTRIPLE middleRight = oldImage[i][j + 1];

                BYTE averageBlue = round((pixel.rgbtBlue + topMiddle.rgbtBlue + topRight.rgbtBlue +
                                          middleRight.rgbtBlue) /
                                         4.0);
                BYTE averageGreen = round((pixel.rgbtGreen + topMiddle.rgbtGreen +
                                           topRight.rgbtGreen + middleRight.rgbtGreen) /
                                          4.0);
                BYTE averageRed = round(
                    (pixel.rgbtRed + topMiddle.rgbtRed + topRight.rgbtRed + middleRight.rgbtRed) /
                    4.0);

                RGBTRIPLE blurredPixel = {averageBlue, averageGreen, averageRed};
                image[i][j] = blurredPixel;
                continue;
            }
            // BOTTOM RIGHT CORNER
            else if ((i == height - 1) && (j == width - 1))
            {
                RGBTRIPLE topMiddle = oldImage[i - 1][j];
                RGBTRIPLE topLeft = oldImage[i - 1][j - 1];
                RGBTRIPLE middleLeft = oldImage[i][j - 1];

                BYTE averageBlue = round(
                    (pixel.rgbtBlue + topMiddle.rgbtBlue + topLeft.rgbtBlue + middleLeft.rgbtBlue) /
                    4.0);
                BYTE averageGreen = round((pixel.rgbtGreen + topMiddle.rgbtGreen +
                                           topLeft.rgbtGreen + middleLeft.rgbtGreen) /
                                          4.0);
                BYTE averageRed = round(
                    (pixel.rgbtRed + topMiddle.rgbtRed + topLeft.rgbtRed + middleLeft.rgbtRed) /
                    4.0);

                RGBTRIPLE blurredPixel = {averageBlue, averageGreen, averageRed};
                image[i][j] = blurredPixel;
                continue;
            }

            /**
             * SIDES
             */
            // TOP
            else if (i == 0)
            {
                RGBTRIPLE middleLeft = oldImage[i][j - 1];
                RGBTRIPLE middleRight = oldImage[i][j + 1];
                RGBTRIPLE bottomLeft = oldImage[i + 1][j - 1];
                RGBTRIPLE bottomMiddle = oldImage[i + 1][j];
                RGBTRIPLE bottomRight = oldImage[i + 1][j + 1];

                BYTE averageBlue =
                    round((pixel.rgbtBlue + middleLeft.rgbtBlue + middleRight.rgbtBlue +
                           bottomLeft.rgbtBlue + bottomMiddle.rgbtBlue + bottomRight.rgbtBlue) /
                          6.0);
                BYTE averageGreen =
                    round((pixel.rgbtGreen + middleLeft.rgbtGreen + middleRight.rgbtGreen +
                           bottomLeft.rgbtGreen + bottomMiddle.rgbtGreen + bottomRight.rgbtGreen) /
                          6.0);
                BYTE averageRed =
                    round((pixel.rgbtRed + middleLeft.rgbtRed + middleRight.rgbtRed +
                           bottomLeft.rgbtRed + bottomMiddle.rgbtRed + bottomRight.rgbtRed) /
                          6.0);

                RGBTRIPLE blurredPixel = {averageBlue, averageGreen, averageRed};
                image[i][j] = blurredPixel;
                continue;
            }
            // BOTTOM
            else if (i == height - 1)
            {
                RGBTRIPLE middleLeft = oldImage[i][j - 1];
                RGBTRIPLE middleRight = oldImage[i][j + 1];
                RGBTRIPLE topLeft = oldImage[i - 1][j - 1];
                RGBTRIPLE topMiddle = oldImage[i - 1][j];
                RGBTRIPLE topRight = oldImage[i - 1][j + 1];

                BYTE averageBlue =
                    round((pixel.rgbtBlue + middleLeft.rgbtBlue + middleRight.rgbtBlue +
                           topLeft.rgbtBlue + topMiddle.rgbtBlue + topRight.rgbtBlue) /
                          6.0);
                BYTE averageGreen =
                    round((pixel.rgbtGreen + middleLeft.rgbtGreen + middleRight.rgbtGreen +
                           topLeft.rgbtGreen + topMiddle.rgbtGreen + topRight.rgbtGreen) /
                          6.0);
                BYTE averageRed = round((pixel.rgbtRed + middleLeft.rgbtRed + middleRight.rgbtRed +
                                         topLeft.rgbtRed + topMiddle.rgbtRed + topRight.rgbtRed) /
                                        6.0);

                RGBTRIPLE blurredPixel = {averageBlue, averageGreen, averageRed};
                image[i][j] = blurredPixel;
                continue;
            }
            // LEFT
            else if (j == 0)
            {
                RGBTRIPLE topMiddle = oldImage[i - 1][j];
                RGBTRIPLE bottomMiddle = oldImage[i + 1][j];
                RGBTRIPLE topRight = oldImage[i - 1][j + 1];
                RGBTRIPLE middleRight = oldImage[i][j + 1];
                RGBTRIPLE bottomRight = oldImage[i + 1][j + 1];

                BYTE averageBlue =
                    round((pixel.rgbtBlue + topMiddle.rgbtBlue + bottomMiddle.rgbtBlue +
                           topRight.rgbtBlue + middleRight.rgbtBlue + bottomRight.rgbtBlue) /
                          6.0);
                BYTE averageGreen =
                    round((pixel.rgbtGreen + topMiddle.rgbtGreen + bottomMiddle.rgbtGreen +
                           topRight.rgbtGreen + middleRight.rgbtGreen + bottomRight.rgbtGreen) /
                          6.0);
                BYTE averageRed =
                    round((pixel.rgbtRed + topMiddle.rgbtRed + bottomMiddle.rgbtRed +
                           topRight.rgbtRed + middleRight.rgbtRed + bottomRight.rgbtRed) /
                          6.0);

                RGBTRIPLE blurredPixel = {averageBlue, averageGreen, averageRed};
                image[i][j] = blurredPixel;
                continue;
            }
            // RIGHT
            else if (j == width - 1)
            {
                RGBTRIPLE topMiddle = oldImage[i - 1][j];
                RGBTRIPLE bottomMiddle = oldImage[i + 1][j];
                RGBTRIPLE topLeft = oldImage[i - 1][j - 1];
                RGBTRIPLE middleLeft = oldImage[i][j - 1];
                RGBTRIPLE bottomLeft = oldImage[i + 1][j - 1];

                BYTE averageBlue =
                    round((pixel.rgbtBlue + topMiddle.rgbtBlue + bottomMiddle.rgbtBlue +
                           topLeft.rgbtBlue + middleLeft.rgbtBlue + bottomLeft.rgbtBlue) /
                          6.0);
                BYTE averageGreen =
                    round((pixel.rgbtGreen + topMiddle.rgbtGreen + bottomMiddle.rgbtGreen +
                           topLeft.rgbtGreen + middleLeft.rgbtGreen + bottomLeft.rgbtGreen) /
                          6.0);
                BYTE averageRed =
                    round((pixel.rgbtRed + topMiddle.rgbtRed + bottomMiddle.rgbtRed +
                           topLeft.rgbtRed + middleLeft.rgbtRed + bottomLeft.rgbtRed) /
                          6.0);

                RGBTRIPLE blurredPixel = {averageBlue, averageGreen, averageRed};
                image[i][j] = blurredPixel;
                continue;
            }

            RGBTRIPLE topLeft = oldImage[i - 1][j - 1];
            RGBTRIPLE topMiddle = oldImage[i - 1][j];
            RGBTRIPLE topRight = oldImage[i - 1][j + 1];

            RGBTRIPLE middleLeft = oldImage[i][j - 1];
            // pixel
            RGBTRIPLE middleRight = oldImage[i][j + 1];

            RGBTRIPLE bottomLeft = oldImage[i + 1][j - 1];
            RGBTRIPLE bottomMiddle = oldImage[i + 1][j];
            RGBTRIPLE bottomRight = oldImage[i + 1][j + 1];

            BYTE averageBlue =
                round((topLeft.rgbtBlue + topMiddle.rgbtBlue + topRight.rgbtBlue +
                       middleLeft.rgbtBlue + pixel.rgbtBlue + middleRight.rgbtBlue +
                       bottomLeft.rgbtBlue + bottomMiddle.rgbtBlue + bottomRight.rgbtBlue) /
                      9.0);
            BYTE averageGreen =
                round((topLeft.rgbtGreen + topMiddle.rgbtGreen + topRight.rgbtGreen +
                       middleLeft.rgbtGreen + pixel.rgbtGreen + middleRight.rgbtGreen +
                       bottomLeft.rgbtGreen + bottomMiddle.rgbtGreen + bottomRight.rgbtGreen) /
                      9.0);
            BYTE averageRed =
                round((topLeft.rgbtRed + topMiddle.rgbtRed + topRight.rgbtRed + middleLeft.rgbtRed +
                       pixel.rgbtRed + middleRight.rgbtRed + bottomLeft.rgbtRed +
                       bottomMiddle.rgbtRed + bottomRight.rgbtRed) /
                      9.0);

            RGBTRIPLE blurredPixel = {averageBlue, averageGreen, averageRed};
            image[i][j] = blurredPixel;
        }
    }
    return;
}
