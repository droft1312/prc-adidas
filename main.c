#include <stdio.h>
#include <stdbool.h>

#define leastSignificantBit 0x01

char getParityBitForMsb(char c)
{
    int sum = 0;

    char d3, d2, d1, d0;

    d3 = (c >> 7) & leastSignificantBit;
    d2 = (c >> 6) & leastSignificantBit;
    d1 = (c >> 5) & leastSignificantBit;
    d0 = (c >> 4) & leastSignificantBit;

    for (int i = 7;  i >= 4; i--)
    {
        char bit = (c >> i) & leastSignificantBit;

        if (bit == 1)
        {
            ++sum;
        }
    }

    // if it's odd return 1, else return 0
    return (sum & 1) ? 1 : 0;
}

void getLsb(char c) {

}

void printBits(char c) {

    for (int i = 7; i >= 0; i--)
    {
        char x = c >> i;
        char y = x & 0x01;
        printf("%d", (c >> i) & 0x01);
    }

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
