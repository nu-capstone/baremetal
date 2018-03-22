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
    uint16_t value = packet.val;
    if(data_type == PPGa) 
    {
        uart_push( &tx_buf, 1 );
    }
    else if(data_type == PPGb) 
    {
        uart_push( &tx_buf, 2 );
    }
    else if(data_type == ECG) 
    {
        uart_push( &tx_buf, 4 );
    }
    else if(data_type == TEMP) 
    {
        uart_push( &tx_buf, 8 );
    }
    else if(data_type == MISC) 
    {
        uart_push( &tx_buf, 16 );
    }

    uart_push( &tx_buf, (uint8_t) ( value >> 8 )); 
    uart_push( &tx_buf, (uint8_t) ( value & 0xff ));
} 

SendPacket_t 
create_packet(uint8_t data_type_int, uint16_t val) 
{
    SendPacket_t packet; 
    packet.val = val;

    if(data_type_int == 1)
        packet.data_type = PPGa;
    else if(data_type_int == 2)
      packet.data_type = PPGb; 
    else if(data_type_int == 4)
      packet.data_type = ECG; 
    else if(data_type_int == 8)
      packet.data_type = TEMP;
    else if(data_type_int == 16)
      packet.data_type = MISC; 
    
    return packet; 
}

/*
 * Pops off three uart messages and turns them into a uint16_t and
 * a reg (uint8_t)
 */
RecvPacket_t
parse_uart(void) 
{
    RecvPacket_t packet; 
    packet.reg = uart_pop( &rx_buf ); 
    packet.val = uart_pop( &rx_buf ) << 8;
    packet.val |= uart_pop( &rx_buf );  
    return packet; 
}

