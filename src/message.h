#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>

// "Only requirement is that it is bytewise"
// Messaging format between microcontroller and display tools
// What can be sent from the microcontroller to the display tools?
// 1. PPG (a)           1
// 2. PPG (b)           2
// 3. ECG               3
// 4. Temperature       4
// Format
// [0:7]       | [8:15]         | [16:23]
// [data type] | [lower data]   | [upper data]
//
// What can be sent from the display tools to the micro?
// 1. Register configurations
// Format
// [0:31]       | [32:63]
// [register]   | [value]
//
// rx_buf, tx_buf are queues that can be accessed with pop/push functions


typedef enum {
    PPGa = 1, PPGb = 2, ECG = 4, TEMP = 8, MISC = 16
} SendType_t;

typedef struct {
    SendType_t  data_type;
    uint16_t    val;     
} SendPacket_t;

typedef struct {
    uint8_t reg; 
    uint16_t val; 
} RecvPacket_t;

void           push_packet(SendPacket_t packet);
SendPacket_t   create_packet(SendType_t data_type, uint16_t value); 
RecvPacket_t   parse_uart(void);


#endif // MESSAGE_H 
