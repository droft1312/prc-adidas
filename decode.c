#include <stdio.h>
#include <stdint.h>

#define leastSignificantBit 0b00000001

void flip(uint8_t byte)
{
    uint8_t d3 = (byte >> 6) & leastSignificantBit;
    uint8_t d2 = (byte >> 5) & leastSignificantBit;
    uint8_t d1 = (byte >> 4) & leastSignificantBit;
    uint8_t d0 = (byte >> 3) & leastSignificantBit;

    uint8_t p2 = (byte >> 2) & leastSignificantBit;
    uint8_t p1 = (byte >> 1) & leastSignificantBit;
    uint8_t p0 = (byte >> 0) & leastSignificantBit;

    printf("hello");
}

int main(int argc, char *argv[])
{
    FILE *input = fopen("D:\\Projects\\Adidas\\output.txt", "rb");
    FILE *output = fopen("D:\\Projects\\Adidas\\output-output.txt", "wb");

    if (input == NULL || output == NULL)
    {
        printf("Error! File not found.");
        return -1;
    }

    uint8_t character;

    while (fread(&character, 1, 1, input) == 1)
    {
        flip(character);
    }

    fclose(input);
    fclose(output);
//int x = rand; number^=x % 8
    return 0;
}