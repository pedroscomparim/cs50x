#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];

            int r = pixel.rgbtRed;
            int g = pixel.rgbtGreen;
            int b = pixel.rgbtBlue;

            // Grayscale value is the average of the three channels
            int average = round((r + g + b) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Only need to go halfway across each row, swapping mirrored pairs
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Work from a copy so each pixel's blur uses original neighbors,
    // not ones already blurred in this same pass
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;
            int count = 0;

            // Look at the 3x3 box of neighbors centered on this pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int neighbor_i = i + di;
                    int neighbor_j = j + dj;

                    // Skip neighbors that fall outside the image (edges and corners)
                    if (neighbor_i >= 0 && neighbor_i < height && neighbor_j >= 0 &&
                        neighbor_j < width)
                    {
                        RGBTRIPLE pixel_neighbor = copy[neighbor_i][neighbor_j];

                        sum_r += pixel_neighbor.rgbtRed;
                        sum_g += pixel_neighbor.rgbtGreen;
                        sum_b += pixel_neighbor.rgbtBlue;

                        count++;
                    }
                }
            }

            // Average only over the neighbors that actually existed
            int average_r = round((double) sum_r / count);
            int average_g = round((double) sum_g / count);
            int average_b = round((double) sum_b / count);

            image[i][j].rgbtRed = average_r;
            image[i][j].rgbtGreen = average_g;
            image[i][j].rgbtBlue = average_b;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Sobel kernels: Gx detects vertical edges, Gy detects horizontal edges
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Work from a copy for the same reason as in blur
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_r, Gx_g, Gx_b;
            int Gy_r, Gy_g, Gy_b;

            Gx_r = Gx_g = Gx_b = 0;
            Gy_r = Gy_g = Gy_b = 0;

            // Apply both kernels over the 3x3 neighborhood
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int neighbor_i = i + di;
                    int neighbor_j = j + dj;

                    // Pixels outside the image contribute 0, so just skip them
                    if (neighbor_i >= 0 && neighbor_i < height && neighbor_j >= 0 &&
                        neighbor_j < width)
                    {
                        RGBTRIPLE pixel_neighbor = copy[neighbor_i][neighbor_j];

                        Gx_r += Gx[di + 1][dj + 1] * pixel_neighbor.rgbtRed;
                        Gx_g += Gx[di + 1][dj + 1] * pixel_neighbor.rgbtGreen;
                        Gx_b += Gx[di + 1][dj + 1] * pixel_neighbor.rgbtBlue;

                        Gy_r += Gy[di + 1][dj + 1] * pixel_neighbor.rgbtRed;
                        Gy_g += Gy[di + 1][dj + 1] * pixel_neighbor.rgbtGreen;
                        Gy_b += Gy[di + 1][dj + 1] * pixel_neighbor.rgbtBlue;
                    }
                }
            }

            // Combine the two directions into a single gradient magnitude
            int r = round(sqrt(Gx_r * Gx_r + Gy_r * Gy_r));
            int g = round(sqrt(Gx_g * Gx_g + Gy_g * Gy_g));
            int b = round(sqrt(Gx_b * Gx_b + Gy_b * Gy_b));

            // Cap each channel at 255, the max value a byte can hold
            if (r > 255)
            {
                r = 255;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (b > 255)
            {
                b = 255;
            }

            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }
}
