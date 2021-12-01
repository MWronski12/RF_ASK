#include <string.h>
#include <inttypes.h>
#include <wiringPi.h>
#include "../include/side_funcs.h"
#include "../include/linked_list.h"
#include "../include/transmitter.h"

/*----------------------------------------------------------------|
|  preamble | start symbol | # bytes | from id |  payload  | FCS  | <--- # bytes refers only to payload
|-----------------------------------------------------------------|
|     16    |      12      |   16    |   16    | < 8*32767 |  16  | <--- bits;
|----------------------------------------------------------------*/
struct frame
{
    const char *preamble;
    const char *start_symbol;
    uint16_t length; // Length of payload in bytes
    uint16_t from_id;
    node *payload;
    char *fcs;
};

/*-------------------------------------------- tx_1 -----------------
| Setup transmitter:
*-------------------------------------------------------------------*/
void setup(int pin)
{
    wiringPiSetupGpio();
    pinMode(pin, OUTPUT);
}

void tx_0(int pin)
{
    digitalWrite(pin, LOW);
    delayMicroseconds(BIT_PERIOD);
}

void tx_1(int pin)
{
    digitalWrite(pin, HIGH);
    delayMicroseconds(BIT_PERIOD);
}

/*-------------------------------------------- tx_1 -----------------
| Encode message
*-------------------------------------------------------------------*/
char *encode(char *message, int len, int encoding)
{
    if (encoding == MANCHESTER)
    {
        char *encoded_msg = (char *)malloc(2 * len * sizeof(char));
        for (int i = 0; i < 2 * len; i++)
        {
            if (message[i] == '1')
            {
                encoded_msg[i] = '1';
                encoded_msg[i + 1] = '0';
            }
            else
            {
                encoded_msg[i] = '0';
                encoded_msg[i + 1] = '1';
            }
        }
        return encoded_msg;
    }
    // TODO
    // Other encoding schemes
}

/*-------------------------------------------- fcs ------------------
| Send 16 bit manchester encoded CRC code
*-------------------------------------------------------------------*/
void append_fcs();

/*-------------------------------------------- message --------------
| Manchester encode array of bits for DC balanced signal transmission
*-------------------------------------------------------------------*/
char *insert_encoded_message();

/*-------------------------------------------- from_id --------------
| Insert ID of a sender to frame buffer
*-------------------------------------------------------------------*/
int insert_from_id();

/*-------------------------------------------- msg_len --------------
| Calculate and insert message length to frame buffer
*-------------------------------------------------------------------*/
int insert_msg_len(char *msg)
{
    
}

/*-------------------------------------------- start_symbol ---------
| Append 0x8e6 binary start symbol to data frame buffer
*-------------------------------------------------------------------*/
int insert_start_symbol(frame *frame_buff)
{
    frame_buff->start_symbol = START_SYMBOL;
}

/*-------------------------------------------- preamble -------------
| Insert training preamble to frame buffer
*-------------------------------------------------------------------*/
void insert_preamble(frame *frame_buff)
{
    frame_buff->preamble = PREAMBLE;
}

/*---------------------------------------------- assemble_packet ----
| Assemble verified data frame for transmission
*-------------------------------------------------------------------*/
char assemble_frame();

/*---------------------------------------------- transmit -----------
| Transmit string of MAX_MSG_LEN max length
*-------------------------------------------------------------------*/
int transmit(char *msg);