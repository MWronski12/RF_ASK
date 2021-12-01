#pragma once

#include <inttypes.h>

typedef struct frame frame;

enum encodings
{
    MANCHESTER,                                 // 1 -> 10; 0 -> 01; DC BALANCED
};

const uint8_t BIT_PERIOD = 500;
const uint16_t MAX_PAYLOAD_LEN = 65535 / 2;     // max 32767 bytes
const char *START_SYMBOL = "100011100110";      // 0x8E6  
const char *PREAMBLE = "1010101010101010";