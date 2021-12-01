#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include "../include/linked_list.h"

typedef struct frame frame;

struct frame
{
    const char *preamble;
};

int pow_of_2(int exp)
{
    int res = 1;
    for (int i = 0; i < exp; i++)
    {
        res *= 2;
    }
    return res;
}

char *str_to_binstr(char *string)
{
    char *res = (char *)malloc(8 * strlen(string) * sizeof(char) + 1);
    *res = '\0';

    int bit;
    char buff[9];
    buff[8] = '\0';

    for (int i = 0; i < strlen(string); i++)
    {
        for (int j = 0; j < 8; j++)
        {
            bit = (string[i] & (1 << (7 - j))) >> (7 - j);
            buff[j] = bit + 48; // ascii conversion
        }
        strcat(res, buff);
    }

    return res;
}

int main()
{
    char *name = "ab";
    char *name_bin = str_to_binstr(name);
    printf("%s", name_bin);

    return 1;
}