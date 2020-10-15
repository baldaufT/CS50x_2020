#include "helpers.h"
#include <math.h>

int cap(int num);
int roundit(int num, int count);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int value = image[i][j].rgbtRed;;
            value += image[i][j].rgbtBlue;
            value += image[i][j].rgbtGreen;
            if(value % 3 == 2){
                value = (value / 3) + 1;
            } else {
                value = value / 3;
            }
            image[i][j].rgbtRed = value;
            image[i][j].rgbtBlue = value;
            image[i][j].rgbtGreen = value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width / 2; j++){
            RGBTRIPLE help = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = help;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int count = 1;
    int red = 0;
    int green = 0;
    int blue = 0;

    RGBTRIPLE help[height][width];

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //Initialzing with image i, j
            red = image[i][j].rgbtRed;
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            count = 1;

            if(j >= 1){
                red += image[i][j-1].rgbtRed;
                blue += image[i][j-1].rgbtBlue;
                green += image[i][j-1].rgbtGreen;
                count++;
            }
            if(j < width - 1){
                red += image[i][j+1].rgbtRed;
                blue += image[i][j+1].rgbtBlue;
                green += image[i][j+1].rgbtGreen;
                count++;
            }

            if(i >= 1){
                red += image[i-1][j].rgbtRed;
                blue += image[i-1][j].rgbtBlue;
                green += image[i-1][j].rgbtGreen;
                count++;
                if(j > 0){
                    red += image[i-1][j-1].rgbtRed;
                    blue += image[i-1][j-1].rgbtBlue;
                    green += image[i-1][j-1].rgbtGreen;
                    count++;
                }
                if(j < width - 1){
                    red += image[i-1][j+1].rgbtRed;
                    blue += image[i-1][j+1].rgbtBlue;
                    green += image[i-1][j+1].rgbtGreen;
                    count++;
                }
            }
            if(i < height - 1){
                red += image[i+1][j].rgbtRed;
                blue += image[i+1][j].rgbtBlue;
                green += image[i+1][j].rgbtGreen;
                count++;
                if(j > 0){
                    red += image[i+1][j-1].rgbtRed;
                    blue += image[i+1][j-1].rgbtBlue;
                    green += image[i+1][j-1].rgbtGreen;
                    count++;
                }
                if(j < width - 1){
                    red += image[i+1][j+1].rgbtRed;
                    blue += image[i+1][j+1].rgbtBlue;
                    green += image[i+1][j+1].rgbtGreen;
                    count++;
                }
            }

            //Rounding
            help[i][j].rgbtRed = roundit(red, count);
            help[i][j].rgbtBlue = roundit(blue, count);
            help[i][j].rgbtGreen = roundit(green, count);
        }
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[i][j] = help[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int red = 0;
    int green = 0;
    int blue = 0;

    RGBTRIPLE gx[height][width];
    RGBTRIPLE gy[height][width];
    RGBTRIPLE g[height][width];

    // Gx
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //Initialzing
            red = 0;
            blue = 0;
            green = 0;

            if(j > 0){
                red += image[i][j-1].rgbtRed * -2;
                blue += image[i][j-1].rgbtBlue * -2;
                green += image[i][j-1].rgbtGreen * -2;
            }
            if(j < width - 1){
                red += image[i][j+1].rgbtRed * 2;
                blue += image[i][j+1].rgbtBlue * 2;
                green += image[i][j+1].rgbtGreen * 2;
            }

            if(i > 0){
                if(j > 0){
                    red += image[i-1][j-1].rgbtRed * -1;
                    blue += image[i-1][j-1].rgbtBlue * -1;
                    green += image[i-1][j-1].rgbtGreen * -1;
                }
                if(j < width - 1){
                    red += image[i-1][j+1].rgbtRed;
                    blue += image[i-1][j+1].rgbtBlue;
                    green += image[i-1][j+1].rgbtGreen;
                }
            }
            if(i < height - 1){
                if(j > 0){
                    red += image[i+1][j-1].rgbtRed * -1;
                    blue += image[i+1][j-1].rgbtBlue * -1;
                    green += image[i+1][j-1].rgbtGreen * -1;
                }
                if(j < width - 1){
                    red += image[i+1][j+1].rgbtRed;
                    blue += image[i+1][j+1].rgbtBlue;
                    green += image[i+1][j+1].rgbtGreen;
                }
            }

            //Rounding
            gx[i][j].rgbtRed = cap(red);
            gx[i][j].rgbtBlue = cap(blue);
            gx[i][j].rgbtGreen = cap(green);
        }
    }

    //For Gy now
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //Initialzing
            red = 0;
            blue = 0;
            green = 0;

            if(i > 0){
                red += image[i-1][j].rgbtRed * -2;
                blue += image[i-1][j].rgbtBlue * -2;
                green += image[i-1][j].rgbtGreen * -2;
                if(j > 0){
                    red += image[i-1][j-1].rgbtRed * -1;
                    blue += image[i-1][j-1].rgbtBlue * -1;
                    green += image[i-1][j-1].rgbtGreen * -1;
                }
                if(j < width - 1){
                    red += image[i-1][j+1].rgbtRed * -1;
                    blue += image[i-1][j+1].rgbtBlue * -1;
                    green += image[i-1][j+1].rgbtGreen * -1;
                }
            }
            if(i < height - 1){
                red += image[i+1][j].rgbtRed * 2;
                blue += image[i+1][j].rgbtBlue * 2;
                green += image[i+1][j].rgbtGreen * 2;
                if(j > 0){
                    red += image[i+1][j-1].rgbtRed;
                    blue += image[i+1][j-1].rgbtBlue;
                    green += image[i+1][j-1].rgbtGreen;
                }
                if(j < width - 1){
                    red += image[i+1][j+1].rgbtRed;
                    blue += image[i+1][j+1].rgbtBlue;
                    green += image[i+1][j+1].rgbtGreen;
                }
            }

            //Rounding
            gy[i][j].rgbtRed = cap(red);
            gy[i][j].rgbtBlue = cap(blue);
            gy[i][j].rgbtGreen = cap(green);
        }
    }

    //Calculations Gx
    double dred, dgreen, dblue;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            g[i][j].rgbtRed = cap((int)round(sqrt((double)((gx[i][j].rgbtRed * gx[i][j].rgbtRed) + (gy[i][j].rgbtRed * gy[i][j].rgbtRed)))));
            g[i][j].rgbtGreen = cap((int)round(sqrt((double)((gx[i][j].rgbtGreen * gx[i][j].rgbtGreen) + (gy[i][j].rgbtGreen * gy[i][j].rgbtGreen)))));
            g[i][j].rgbtBlue = cap((int)round(sqrt((double)((gx[i][j].rgbtBlue * gx[i][j].rgbtBlue) + (gy[i][j].rgbtBlue * gy[i][j].rgbtBlue)))));
        }
    }

    //Final
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[i][j] = g[i][j];
        }
    }

    return;
}

int cap(int num){
    if(num < 0){
        num *= -1;
    }
    if(num > 255){
        return 255;
    }
    return num;
}

int roundit(int num, int count){
    int res = num % count;
    if(res == 0){
        return num / count;
    }
    float div = (float) count / res;
    if(div > 2){
        return num / count;
    } else {
        return (num / count) + 1;
    }
}