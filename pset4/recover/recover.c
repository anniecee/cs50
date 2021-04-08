#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

//unit8_t: byte -> -255 -> 255 (unitb 0->512)
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //Declare filenames
    char *infile = argv[1];

    //Open input file
    FILE *inptr = fopen(infile, "r");
    
    //Check if file is available
    if (infile == NULL)
    {
        printf("Couldn't find file\n");
        return 2;
    }
    
    //Declare buffer to store things read from input
    BYTE buffer[BLOCK_SIZE];
    
    //Declare counter
    int imageCount = 0;

    //Declare file name for output
    //3 characters for the digits + 4 for the .jpg + 1 for null terminator
    char filename[8]; 
    
    //Create a reference (outptr) that doesn't go to anything
    //(Assign something in outptr later on)
    FILE *outptr = NULL;

    while (true)
    {
        //Read a block of the input file (memory card)
        //fread will return values of the number of bytes that are read
        //Store that number of bytes in bytesRead
        size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr);

        // Break loop when we reach the end of input file
        if (bytesRead == 0 && feof(inptr))
        {
            break;
        }

        // Check if find a JPEG
        bool containsJpegHeader = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;

        // If find another JPEG, close the previous file
        if (containsJpegHeader)
        {
            //Close the previous output file
            if (outptr != NULL)
            {
                fclose(outptr);
                imageCount++;
            }
            //Print out file name, first parameter is pointer to the target string
            sprintf(filename, "%03i.jpg", imageCount);
            //If find a new JPEG, open the file for writing
            outptr = fopen(filename, "w");
        }
     
        //Write anytime we have an open file
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, outptr);
        }
    }

    // close last jpeg file
    fclose(outptr);

    // close infile
    fclose(inptr);

    // success
    return 0;
}
