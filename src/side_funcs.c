#include <stdio.h>
#include <sys/time.h>
#include <inttypes.h>
#include <math.h>
#include "../include/side_funcs.h"

int pow_of_2(int exp)
{
    int res = 1;
    for (int i = 0; i < exp; i++)
    {
        res *= 2;
    }
    return res;
}

/*-------------------------------------------- uint16_t_to_binstring -
| Convert string to UTF-8 binary encoded string 
| [ "abcd" --> "01100001 01100010 01100011 01100100" ]
*--------------------------------------------------------------------*/
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

/*-------------------------------------------- u_timestamp -----------
| RETURNS CURRENT TIME IN MICROSECONDS
*--------------------------------------------------------------------*/
uint64_t u_timestamp(void)
{
    struct timeval timer_usec;
    long long int timestamp_usec; /* timestamp in microsecond */
    if (!gettimeofday(&timer_usec, NULL))
    {
        timestamp_usec = ((long long int)timer_usec.tv_sec) * 1000000ll +
                         (long long int)timer_usec.tv_usec;
    }
    else
    {
        timestamp_usec = -1;
    }
    return timestamp_usec;
}