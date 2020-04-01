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

char combineBitsAndParityBits(char d0, char d1, char d2, char d3)
{
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
        result |= 1 << 0;

    if (d2 != 0)
        result |= 1 << 1;

    if (d1 != 0)
        result |= 1 << 2;

    if (d0 != 0)
        result |= 1 << 3;

    if (p2 != 0)
        result |= 1 << 4;

    if (p1 != 0)
        result |= 1 << 5;

    if (p0 != 0)
        result |= 1 << 6;

    printBits(result);

    return result;
}

char processMsb(unsigned char c)
{
    char d3, d2, d1, d0;

    d3 = (c >> 7) & leastSignificantBit;
    d2 = (c >> 6) & leastSignificantBit;
    d1 = (c >> 5) & leastSignificantBit;
    d0 = (c >> 4) & leastSignificantBit;

    return combineBitsAndParityBits(d0, d1, d2, d3);
}

char processLsb(char c) {
    char d3, d2, d1, d0;

    d3 = (c >> 3) & leastSignificantBit;
    d2 = (c >> 2) & leastSignificantBit;
    d1 = (c >> 1) & leastSignificantBit;
    d0 = (c >> 0) & leastSignificantBit;

    return combineBitsAndParityBits(d0, d1, d2, d3);
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
//        processMsb(character);
        processLsb(character);
    }

    fclose(input);

    return 0;
}
