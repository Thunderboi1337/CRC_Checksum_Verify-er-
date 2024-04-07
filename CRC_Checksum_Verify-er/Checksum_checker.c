/**
 * @file Assignment.c
 * @author Marcus Robertsson (Marcus.asberg.98@gmail.com)
 * @brief Made with amazing team work!
 * @version 1.0
 * @date 2022-11-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MSB_ONE (1 << 15)
#define POLY 0xC599
#define N 14

// Generates a checksum
uint16_t CRC_15(uint8_t *message, uint16_t array_len);

// Appends the checksum to the message
void checksum_append(uint8_t *message, int array_len, uint16_t checksum);

int main(void)
{
    // the message
    uint8_t message[N] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', 0, 0};

    uint16_t Checksum = CRC_15(message, sizeof(message));

    (void)printf("0x%X\n", Checksum);

    checksum_append(message, sizeof(message), Checksum);

    if (0 == CRC_15(message, sizeof(message)))
    {
        (void)printf("\nData is okay");
    }
    else
    {
        (void)printf("\nData has been tainted!");
    }

    message[2] = 'L';

    if (0 == CRC_15(message, sizeof(message)))
    {
        (void)printf("\nData is okay");
    }
    else
    {
        (void)printf("\nData has been tainted!");
    }

    return 0;
}

// generates checksum based on massage
uint16_t CRC_15(uint8_t *message, uint16_t array_len)
{

    uint16_t remainder = 0;

    for (int i = 0; i < array_len; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            remainder <<= 1;
            remainder |= (((message[i]) >> j) & 1);

            if ((remainder & MSB_ONE) != 0)
            {
                remainder ^= POLY;
            }
        }
    }

    return remainder;
}

// Appends checksum to message
void checksum_append(uint8_t *message, int array_len, uint16_t checksum)
{
    for (int i = 0; i < 8; i++)
    {
        message[array_len - 1] |= (((checksum >> i) & 1) << (8 - 1 - i));
        message[array_len - 2] |= ((((checksum >> 8) >> i) & 1) << (8 - 1 - i));
    }
}
