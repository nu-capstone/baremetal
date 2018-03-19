#include "message.h"
#include "uart.h"

/*
 * Parses the buffer and returns a RecvPacket_t. All 
 * elements in the recv_message_buf[256] array are shifted
 * towards the start based on the number of elements read 
 * off the buffer.
 */

void
push_packet(SendPacket_t packet) 
{
    SendType_t data_type = packet.data_type;
    uint16_t value = packet.value;
    if(data_type == PPGa) 
    {
        tx_buf.push((uint8_t) 1);
    }
    else if(data_type == PPGb) 
    {
        tx_buf.push((uint8_t) 2);
    }
    else if(data_type == ECG) 
    {
        tx_buf.push((uint8_t) 4);
    }
    else if(data_type == TEMP) 
    {
        tx_buf.push((uint8_t) 8);
    }
    else if(data_type == MISC) 
    {
        tx_buf.push((uint8_t) 16);
    }
    tx_buf.push((uint8_t) value >> 8); 
    tx_buf.push((uint8_t) value);
} 

SendPacket_t 
create_packet(uint8_t data_type_int, uint16_t val) 
{
    struct SendPacket_t packet; 
    packet.val = val;
    if(data_type_int == 1) {
        packet.data_type = PPGa;
    } else if(data_type_int == 2) {
        packet.data_type = PPGb; 
    } else if(data_type_int == 4) {
        packet.data_type = ECG; 
    } else if(data_type_int == 8) {
        packet.data_type = TEMP;
    } else if(data_type == 16) {
        packet.data_type = MISC; 
    }
    return packet; 
}

/*
 * Pops off three uart messages and turns them into a uint16_t and
 * a reg (uint8_t)
 */
RecvType_t
parse_uart(void) 
{
    RecvType_t packet; 
    packet.reg = rx_buf.pop(); 
    packet.val = rx_buf.pop() << 8;
    packet.val = rx_buf.pop();  
    return packet; 
}

