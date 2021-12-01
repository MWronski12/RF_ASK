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
| RETURNS uint16_t NUMBER TO BINARY STRING REPRESENTATION
*--------------------------------------------------------------------*/
char *char_to_binarystr(char character)
{
    char str[8] = (char*)malloc(9 * sizeof(char));
    for (int i = 0; i < 8; i++)
    {
        if (character / pow_of_2(7 - i) == 1)
        {
            str[i] = '1';
            character -= pow_of_2(7 - i);
        }
        else
        {
            str[i] = '0';
        }
    }
    return str;
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