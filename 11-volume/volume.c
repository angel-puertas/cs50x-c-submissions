// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    int8_t header[HEADER_SIZE];
    // reads into header, HEADER_SIZE number of elements of size sizeOf(int8_t) (so 1 byte), from
    // file input
    /**
     * ARG 1 -> pointer to memory location where data will be read from (for fwrite)/written to (for
     * fread) ARG 2 -> size in bytes of each element to be read ARG 3 -> number of elements to be
     * read ARG 4 -> file pointer to read/write from
     */
    fread(header, sizeof(int8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(int8_t), HEADER_SIZE, output);
    fclose(output); // closed output file so we can open it in append-binary mode

    // TODO: Read samples from input file and write updated data to output file
    output = fopen(argv[2], "ab");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input) !=
           0) // while the current sample is different from 0
    {
        sample *= factor;
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
