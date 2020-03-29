#include <stdio.h>

int main() {

    FILE *input = fopen("D:\\Projects\\Adidas\\input.txt", "r");
    char c;

    if (input == NULL) {
        printf("Error! File not found.");
        return -1;
    }

    fscanf(input, "%c", &c);

    printf("Value of c=%c", c);

    fclose(input);

    return 0;
}
