#include <stdio.h>
#include <stdint.h>

#define leastSignificantBit 0b00000001

void printByte(uint8_t byte)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (byte >> i) & leastSignificantBit);
    }
}

void writeOut(uint8_t byte, FILE *file)
{
    fwrite(&byte, 1, 1, file);
}

// n is the nth bit you wanna switch
uint8_t switchBit(uint8_t byte, uint8_t n)
{
    return (byte ^ (1 << (n - 1)));
}

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

uint8_t fix(uint8_t byte)
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
        return switchBit(byte, 3);
    }
    else if (p2 != correctP2 && p1 != correctP1 && p0 == correctP0)
    {
        // d3 should be switched
        return switchBit(byte, 7);
    }
    else if (p2 != correctP2 && p1 != correctP1 && p0 != correctP0)
    {
        // d1 should be switched
        return switchBit(byte, 5);
    }
    else if (p2 == correctP2 && p1 == correctP1 && p0 != correctP0)
    {
        // p0 should be switched
        return switchBit(byte, 1);
    }
    else if (p2 == correctP2 && p1 != correctP1 && p0 != correctP0)
    {
        // d0 should be switched
        return switchBit(byte, 4);
    }
    else if (p2 != correctP2 && p1 == correctP1 && p0 != correctP0)
    {
        // d2 should be switched
        return switchBit(byte, 6);
    }
    else if (p2 == correctP2 && p1 != correctP1 && p0 == correctP0)
    {
        // p1 should be switched
        return switchBit(byte, 2);
    }
    else
    {
        // nothing to be changed
        return byte;
    }
}

uint8_t decode(uint8_t msb, uint8_t lsb)
{
    uint8_t d3_msb = (msb >> 6) & leastSignificantBit;
    uint8_t d2_msb = (msb >> 5) & leastSignificantBit;
    uint8_t d1_msb = (msb >> 4) & leastSignificantBit;
    uint8_t d0_msb = (msb >> 3) & leastSignificantBit;

    uint8_t d3_lsb = (lsb >> 6) & leastSignificantBit;
    uint8_t d2_lsb = (lsb >> 5) & leastSignificantBit;
    uint8_t d1_lsb = (lsb >> 4) & leastSignificantBit;
    uint8_t d0_lsb = (lsb >> 3) & leastSignificantBit;

    uint8_t result = 0x00;

    d3_msb = d3_msb << 7;
    d2_msb = d2_msb << 6;
    d1_msb = d1_msb << 5;
    d0_msb = d0_msb << 4;

    d3_lsb = d3_lsb << 3;
    d2_lsb = d2_lsb << 2;
    d1_lsb = d1_lsb << 1;
    d0_lsb = d0_lsb << 0;

    result += d3_msb + d2_msb + d1_msb + d0_msb + d3_lsb + d2_lsb + d1_lsb + d0_lsb;

    return result;
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

    uint8_t character1;
    uint8_t character2;

    while (fread(&character1, 1, 1, input) == 1)
    {
        // We know that there is going to be an even number of bytes in a proper (even though
        // slightly corrupted) input (which is the output of the encode program)
        if (fread(&character2, 1, 1, input) != 1)
        {
            printf("Error in your input! It is too corrupted for me to process!");
            break;
        }

        uint8_t msb = fix(character1);
        uint8_t lsb = fix(character2);

        uint8_t decodedChar = decode(msb, lsb);

        writeOut(decodedChar, output);
    }

    fclose(input);
    fclose(output);
//int x = rand; number^=x % 8
    return 0;
}