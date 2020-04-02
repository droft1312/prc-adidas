#include <stdio.h>
#include <stdint.h>

#define leastSignificantBit 0b00000001

void printByte(uint8_t byte, FILE *file)
{
    fwrite(&byte, 1, 1, file);
}

uint8_t combineBitsAndParityBits(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
{
    uint8_t p2, p1, p0;

    p2 = (d2 + d1 + d3) & 1;
    p1 = (d1 + d3 + d0) & 1;
    p0 = (d2 + d1 + d0) & 1;

    uint8_t result = 0x00;

    // set em up here to be able to later put em together
    d3 = d3 << 6;
    d2 = d2 << 5;
    d1 = d1 << 4;
    d0 = d0 << 3;

    p2 = p2 << 2;
    p1 = p1 << 1;

    result += d3 + d2 + d1 + d0 + p2 + p1 + p0;

    return result;
}

uint8_t processMsb(uint8_t c)
{
    uint8_t d3, d2, d1, d0;

    d3 = (c >> 7) & leastSignificantBit;
    d2 = (c >> 6) & leastSignificantBit;
    d1 = (c >> 5) & leastSignificantBit;
    d0 = (c >> 4) & leastSignificantBit;

    return combineBitsAndParityBits(d0, d1, d2, d3);
}

uint8_t processLsb(uint8_t c)
{
    uint8_t d3, d2, d1, d0;

    d3 = (c >> 3) & leastSignificantBit;
    d2 = (c >> 2) & leastSignificantBit;
    d1 = (c >> 1) & leastSignificantBit;
    d0 = (c >> 0) & leastSignificantBit;

    return combineBitsAndParityBits(d0, d1, d2, d3);
}

int main(int argc, char *argv[])
{
    FILE *input = fopen("D:\\Projects\\Adidas\\input.txt", "rb");
    FILE *output = fopen("D:\\Projects\\Adidas\\output.txt", "wb");

    if (input == NULL || output == NULL)
    {
        printf("Error! File not found.");
        return -1;
    }

    uint8_t character;

    while (fread(&character, 1, 1, input) == 1)
    {
        uint8_t encodedLsb = processLsb(character);
        uint8_t encodedMsb = processMsb(character);

        printByte(encodedMsb, output);
        printByte(encodedLsb, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}
