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
| Encode message: string -> binary string -> dc balanced binary string
*-------------------------------------------------------------------*/
char *encode(char *str, int encoding)
{
    char *buff = str_to_binstr(str);
    int len = strlen(buff);

    if (encoding == MANCHESTER)
    {
        char *encoded = (char *)malloc(2 * len * sizeof(char) + 1);
        *encoded = '\0';
        for (int i = 0; i < 2 * len; i++)
        {
            if (buff[i] == '1')
            {
                strcat(encoded, "10");
            }
            else if (buff[i] == '0')
            {
                strcat(encoded, "01");
            }
        }
        free(buff);
        return encoded;
    }
}

/*-------------------------------------------- fcs ------------------
| Send 16 bit manchester encoded CRC code
*-------------------------------------------------------------------*/
void append_fcs();

/*-------------------------------------------- message --------------
| Manchester encode array of bits for DC balanced signal transmission
*-------------------------------------------------------------------*/
char *insert_encoded_msg(frame *frame_buff, char *encoded_msg)
{
    for (int i = 0; i < strlen(encoded_msg); i++)
    {
        append(&frame_buff->payload, encoded_msg[i]);
    }
}

/*-------------------------------------------- from_id --------------
| Insert ID of a sender to frame buffer
*-------------------------------------------------------------------*/
int insert_from_id(frame *frame_buff)
{
    frame_buff->from_id = 6969;
}

/*-------------------------------------------- msg_len --------------
| Calculate and insert message length to frame buffer
*-------------------------------------------------------------------*/
int insert_msg_len(frame *frame_buff, char *encoded_msg)
{
    frame_buff->length = strlen(encoded_msg);
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
char assemble_frame(frame *frame_buff, char *msg)
{
    char *encoded_msg = encode(msg, MANCHESTER);

    insert_preamble(frame_buff);
    insert_start_symbol(frame_buff);
    insert_msg_len(frame_buff, encoded_msg);
    insert_encoded_msg(frame_buff, encoded_msg);

}


/*---------------------------------------------- transmit -----------
| Transmit string of MAX_MSG_LEN max length
*-------------------------------------------------------------------*/
int transmit(char *msg);