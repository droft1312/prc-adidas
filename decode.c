#include <stdio.h>
#include <stdint.h>

#define leastSignificantBit 0b00000001

// pNumber number of a parity bit you want to get
uint8_t getParityBit(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, unsigned char pNumber)
{
    if (pNumber == 0)
        return (d2 + d1 + d0) & 1;

    if (pNumber == 1)
        return (d1 + d3 + d0) & 1;

    if (pNumber == 2)
        return (d2 + d1 + d3) & 1;

    return -1;
}

void flip(uint8_t byte)
{
    uint8_t d3 = (byte >> 6) & leastSignificantBit;
    uint8_t d2 = (byte >> 5) & leastSignificantBit;
    uint8_t d1 = (byte >> 4) & leastSignificantBit;
    uint8_t d0 = (byte >> 3) & leastSignificantBit;

    uint8_t p2 = (byte >> 2) & leastSignificantBit;
    uint8_t p1 = (byte >> 1) & leastSignificantBit;
    uint8_t p0 = (byte >> 0) & leastSignificantBit;

    uint8_t correctP2 = getParityBit(d0, d1, d2, d3, 2);
    uint8_t correctP1 = getParityBit(d0, d1, d2, d3, 1);
    uint8_t correctP0 = getParityBit(d0, d1, d2, d3, 0);

    if (p2 != correctP2 && p1 == correctP1 && p0 == correctP0)
    {
        // p2 should be switched
    }
    else if (p2 != correctP2 && p1 != correctP1 && p0 == correctP0)
    {
        // d3 should be switched
    }
    else if (p2 != correctP2 && p1 != correctP1 && p0 != correctP0)
    {
        // d1 should be switched
    }
    else if (p2 == correctP2 && p1 == correctP1 && p0 != correctP0)
    {
        // p0 should be switched
    }
    else if (p2 == correctP2 && p1 != correctP1 && p0 != correctP0)
    {
        // d0 should be switched
    }
    else if (p2 != correctP2 && p1 == correctP1 && p0 != correctP0)
    {
        // d2 should be switched
    }
    else if (p2 == correctP2 && p1 != correctP1 && p0 == correctP0)
    {
        // p1 should be switched
    }
    else
    {
        return;
    }
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