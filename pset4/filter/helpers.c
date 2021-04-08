#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	//Loop through rows (heights)
	for (int i = 0; i < height; i++)
	{
		//Loop through collums (width)
    	for (int j = 0; j < width; j++)
    	{
	        //Find average of RGB triples of each byte
	        float Red = image[i][j].rgbtRed;
	        float Green = image[i][j].rgbtGreen;
	        float Blue = image[i][j].rgbtBlue;
	        float average = round((Red + Green + Blue)/3);

	        //Assign average to RGB triples to create grayscale filter
	        image[i][j].rgbtRed = average;
	        image[i][j].rgbtGreen = average;
	        image[i][j].rgbtBlue = average;
    	}
	}
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop through rows (heights)
	for (int i = 0; i < height; i++)
	{
	    //Loop through collums (width)
	    for (int j = 0; j < width; j++)
    	{
	        //Declare original RGB triples
	        int originalRed = image[i][j].rgbtRed;
	        int originalGreen = image[i][j].rgbtGreen;
	        int originalBlue = image[i][j].rgbtBlue;
	
	        //Convert to Sepia color
	        int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
	        int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
	        int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

        	//Cap Sepia values to 255 maximum
	        if (sepiaRed > 255)
	        {
	            sepiaRed = 255;
	        }
	        if (sepiaBlue > 255)
	        {
	            sepiaBlue = 255;
	        }
	        if (sepiaGreen > 255)
	        {
	            sepiaGreen = 255;
	        }
	
	        //Assign Sepia values to RGB triples to create Sepia filter
	        image[i][j].rgbtRed = sepiaRed;
	        image[i][j].rgbtGreen = sepiaGreen;
	        image[i][j].rgbtBlue = sepiaBlue;
    	}
	}
    return;
}

// Reflect image horizontally

//Declare swap function
void swap(RGBTRIPLE *a, RGBTRIPLE *b);
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}
        
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop through all rows (heights)
    for (int i = 0; i < height; i++)
    {
    	//If the number of pixels in a row is even, run the below
    	if (width % 2 == 0)
    	{
        	//Loop through half of the collums (width/2)
        	for (int j = 0; j < (width/2); j++)
        	{
        		//Declare k as pixel in the half right to be switched
	        	int k = (width - j - 1);
	        	//Swap to mirror
	        	swap(&image[i][j],&image[i][k]);
        	}
    	}
    	//If the number of pixels in a row is odd, run the below
    	else if (width % 2 == 1)
    	{
	         //Loop through half of the collums and end at 
	         //the pixel next to the middle
	         //The middle pixel should be left untouched by round down wid/2
	         for (int j = 0; j < (round(width / 2)) ; j++)
	         {
		          //Declare k as pixel in the half right to be switched
		          int k = (width - j - 1);
		          //Swap to mirror
		          swap(&image[i][j], &image[i][k]);
	         }
    	}
	}

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	//Declare variables
	RGBTRIPLE imgCopy[height][width];
	float avgRed;
	float avgGreen;
	float avgBlue;

	//create a copy of original image to save original pixel values
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			imgCopy[i][j].rgbtRed = image[i][j].rgbtRed;
			imgCopy[i][j].rgbtGreen = image[i][j].rgbtGreen;
			imgCopy[i][j].rgbtBlue = image[i][j].rgbtBlue;
		}
	}

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			//if the pixel is on the top left edge
			if (w == 0 && h == 0)
			{
				avgRed = (float)(imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 4;

				avgGreen = (float)(imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 4;

				avgBlue = (float)(imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 4;
				avgRed = round(avgRed);
				avgBlue = round(avgBlue);
				avgGreen = round(avgGreen);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}

			//if the pixel is on the lower left edge
			else if (w == 0 && h == (height - 1))
			{
				avgRed =(float)(imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed) / 4;

				avgGreen = (float)(imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen) / 4;

				avgBlue = (float)(imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue) / 4;
				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
                                image[h][w].rgbtBlue = avgBlue;
			}

			//if the pixel is on top Right
			else if (h == 0 && w == (width - 1))
			{
				avgRed = (float)(imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed)/ 4;

				avgGreen = (float)(imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen) / 4;

				avgBlue = (float)(imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue) / 4;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;
			}

			//if the pixel is on lower right
			else if(h == (height - 1) && w == (width - 1))
			{
				avgRed = (float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed) / 4;

		 		avgBlue = (float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue) / 4;

				avgGreen = (float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen) / 4;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;
			}
       //if the pixel is on left side

			else if (w == 0 && (h > 0 && h < height - 1))
			{
				avgRed = (float)(imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 6;

				avgGreen = (float)(imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 6;

				avgBlue = (float)(imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
      //if the pixel is on right side
			else if (w == (width - 1) && (h > 0 && h < height - 1))
			{
				avgRed = (float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed) / 6;

				avgGreen = (float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen) / 6;

				avgBlue = (float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
                                image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
       //if the pixel is on upper side
			else if (h == 0 && (w > 0 &&  w < width - 1))
			{
				avgRed = (float)(imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 6;

				avgGreen = (float)(imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 6;

				avgBlue = (float)(imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
       //if the pixel is on lower side
			else if  (h == height - 1 && (w > 0 && w < width - 1))
			{
				avgRed = (float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed) / 6;

				avgGreen = (float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen) / 6;
				avgBlue = (float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
      //if the pixel is on the middle and can form a 3x3 grid
			else
			{
				avgRed = (float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 9;
				avgGreen = (float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 9;

				avgBlue = (float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 9;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}

		}
	}
    return;
}

