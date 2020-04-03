#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include<time.h>

void writeOut(uint8_t byte, FILE *file)
{
    fwrite(&byte, 1, 1, file);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Pass all arguments!");
        return -1;
    }

    FILE *input = fopen(argv[1], "rb");
    FILE *output = fopen(argv[2], "wb");

    if (input == NULL || output == NULL)
    {
        printf("Error! File not found.");
        return -1;
    }

    uint8_t character;

    srand(time(0));

    while (fread(&character, 1, 1, input) == 1)
    {
        int randomNumber = rand();

        if (randomNumber % 3 == 0)
        {
            uint8_t corruptedByte = character ^ (1 << (randomNumber % 8));

            writeOut(corruptedByte, output);
        }
        else
        {
            writeOut(character, output);
        }
    }

    fclose(input);
    fclose(output);


    return 0;
}