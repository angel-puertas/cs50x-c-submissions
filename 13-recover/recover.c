#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    FILE *newJpeg;
    char newFileName[8];
    uint8_t buffer[512];
    int fileNumber = 0;

    /**
     * while (fread(buffer, sizeof(uint8_t), 512, card) == 512)
     * 1. reads 512 bytes into the buffer array
     * 2. returns the amount of bytes read
     * 3. compares it to 512. if its less than 512 it means we reached the end of the file
     */
    while (fread(buffer, sizeof(uint8_t), 512, card) == 512)
    {
        // checks for the first 4 bytes in a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(newFileName, "%03i.jpg", fileNumber);
            newJpeg = fopen(newFileName, "w");
            fileNumber++;
            fwrite(buffer, sizeof(uint8_t), 512, newJpeg);
            fclose(newJpeg);
        }
        // appends to current JPEG if we have already found one
        else if (fileNumber > 0)
        {
            newJpeg = fopen(newFileName, "a");
            fwrite(buffer, sizeof(uint8_t), 512, newJpeg);
            fclose(newJpeg);
        }
    }
    fclose(card); // important to prevent memory leaks
}
