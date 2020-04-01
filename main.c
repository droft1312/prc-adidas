#include <stdio.h>
#include <stdbool.h>

#define leastSignificantBit 0x01

void printBits(char c)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (c >> i) & 0x01);
    }
}

char getParityBitForMsb(unsigned char c)
{
    char d3, d2, d1, d0;

    d3 = (c >> 7) & leastSignificantBit;
    d2 = (c >> 6) & leastSignificantBit;
    d1 = (c >> 5) & leastSignificantBit;
    d0 = (c >> 4) & leastSignificantBit;

    char p2, p1, p0;

    p2 = (d2 + d1 + d3) & 1
            ? ((d2 + d1 + d3) == 0 ? 0 : 1)
            : 0;
    p1 = (d1 + d3 + d0) & 1
            ? ((d1 + d3 + d0) == 0 ? 0 : 1)
            : 0;
    p0 = (d2 + d1 + d0) & 1
            ? ((d2 + d1 + d0) == 0 ? 0 : 1)
            : 0;

    char result = 0x00;

    if (d3 != 0)
        result |= 1UL << 0;

    if (d2 != 0)
        result |= 1UL << 1;

    if (d1 != 0)
        result |= 1UL << 2;

    if (d0 != 0)
        result |= 1UL << 3;

    if (p2 != 0)
        result |= 1UL << 4;

    if (p1 != 0)
        result |= 1UL << 5;

    if (p0 != 0)
        result |= 1UL << 6;

    printBits(result);

    return result;
}

void getLsb(char c) {

}


int main() {

    FILE *input = fopen("D:\\Projects\\Adidas\\input.txt", "r");
    char character;

    if (input == NULL)
    {
        printf("Error! File not found.");
        return -1;
    }

    while ((character = fgetc(input)) != EOF)
    {
        getParityBitForMsb(character);
    }

    fclose(input);

    return 0;
}
