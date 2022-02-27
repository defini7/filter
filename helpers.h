#include "bmp.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width]);
void sepia(int height, int width, RGBTRIPLE image[height][width]);
void reflect(int height, int width, RGBTRIPLE image[height][width]);
void blur(int height, int width, RGBTRIPLE image[height][width]);
void threshold(int height, int width, RGBTRIPLE image[height][width]);
void adaptive_threshold(int height, int width, RGBTRIPLE image[height][width]);
