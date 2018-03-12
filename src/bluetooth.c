/**
    ***************************************************************************
    * @file         bluetooth.c
    * @author       ADI
    * @version      V1.0.0
    * @date         14-May-2014
    * @brief        Bluetooth communication related functions
    *
    ***************************************************************************
    * @attention
    ***************************************************************************
*/
/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2014 Analog Devices Inc.                                      *
* All rights reserved.                                                        *
*                                                                             *
* This source code is intended for the recipient only under the guidelines of *
* the non-disclosure agreement with Analog Devices Inc.                       *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
*                                                                             *
* This software is intended for use with the ADPD142 and derivative parts     *
* only                                                                        *
*                                                                             *
******************************************************************************/

/* Includes -----------------------------------------------------------------*/
#include "stdint.h"
#include "Common.h"
#include "HwIfConfig.h"

/* --------------------------- definitions -------------------------------- */
#define BT_SET_PRODUCT_BAUD_CMD     "SET CONTROL BAUD 921600,8N1\r\n" //Set BT and MCU UART speed to 921600
#define BT_SET_PRODUCT_AUTH_CMD     "SET BT AUTH * 1237\r\n" //Set BT pairing code to 1237
#define BT_SET_PRODUCT_CLASS_CMD    "SET BT CLASS 80704\r\n"
//Major Service Class = Capturing, Major Device Class = Wearable, Minor Device Class = Wrist Watch.

#define SUCCESS     0
#define FAIL        1

/* ------------------------- Function Prototype --------------------------- */
static uint8_t BT_Switch_To_Command_Mode();
static uint8_t BT_Check_Command_Mode();
static uint8_t BT_wait_for_ack(uint8_t*);


/**
    * @brief    Check whether BT module is in command mode.
    * @param    None
    * @retval   Error Code
    * @note     switch_uart_BT() should be called before this function is called
    */
uint8_t BT_Check_Command_Mode() {
    //HAL_Delay(800);                     //A value of 600ms is tested. But set it to 800 to be safe.
    //1st AT\r\n is used to flush out probable residual input from previous run(due to MCU reset without BT module reset).
    consoleSendString("AT\r\nAT\r\n");  
    return BT_wait_for_ack("OK");
}

/**
    * @brief    Switches the BT module to command mode.
    * @param    None
    * @retval   Error Code
    * @note     switch_uart_BT() should be called before this function is called
    */
static uint8_t BT_Switch_To_Command_Mode()
{
      if (BT_Check_Command_Mode() != SUCCESS){
        MCU_HAL_Delay(1100);        //In data mode. Use escape sequence
        consoleSendString("+++");
        MCU_HAL_Delay(1100);
        return BT_Check_Command_Mode();        //Check once more just to sure.  
      }
      return SUCCESS;
}

/**
    * @brief    Check whether BT is connected and select BT I/O if connected
    * @param    None
    * @retval   0 if in command mode. 1 otherwise.
    */
uint8_t BT_Init() {
    switch_uart_BT();           	//redirect UART outputs to BT    
   
    if( BT_Check_Command_Mode() == SUCCESS){//in command mode(BT COM PORT not active)
      switch_uart_FTDI();
      return 0;
    }
    else       //in data mode     
      return 1;
}

/**
    * @brief    Sets the parameters of the BT device. BT class, BT name, passcode for BT pairing and UART Baudrate.
    * @param    None    
    * @retval   Error Code
    * @note     switch_uart_BT() should be called before this function is called
    */
ADI_HAL_STATUS_t BT_Factory_Init(uint8_t *btName)
{
    uint8_t result = ADI_HAL_ERROR ;
    switch_uart_BT();		//redirect UART outputs to BT
 
    do{
      if(BT_Switch_To_Command_Mode() != SUCCESS)
        break;    
      
      consoleSendString(BT_SET_PRODUCT_CLASS_CMD);        
      if(BT_wait_for_ack(BT_SET_PRODUCT_CLASS_CMD) == FAIL)
        break;    
      
      consoleSendString(BT_SET_PRODUCT_AUTH_CMD);          
      if(BT_wait_for_ack(BT_SET_PRODUCT_AUTH_CMD) == FAIL)
        break;    
      
      consoleSendString("SET BT NAME ADI HCR ");
      consoleSendString(btName);
      consoleSendString("\r\n");
      if (BT_wait_for_ack(btName) != SUCCESS)
        break;    
      
      consoleSendString(BT_SET_PRODUCT_BAUD_CMD);        
      BT_wait_for_ack("Dummy_wait");                      //Dummy wait
      
      result = ADI_HAL_OK; 
    }while(0);
    
    switch_uart_FTDI();
    return result;
}

/**
    * @brief    checks factory init is already done
    * @param    None    
    * @retval   Error Code
    * @note     switch_uart_BT() should be called before this function is called
    */
ADI_HAL_STATUS_t BT_Factory_Init_Check()
{
    switch_uart_BT();		//redirect UART outputs to BT
 
    if(BT_Switch_To_Command_Mode() != SUCCESS){
        switch_uart_FTDI();
        return ADI_HAL_ERROR;
    }   
    else {
        switch_uart_FTDI();
        return ADI_HAL_OK;
    }    
}

/**
    * @brief    Checks the acknowledglement from BT module
    * @param    Par1 = expected substring present in Ack string
    * @retval Error Code
    */
static uint8_t rx_str[255];
static uint8_t BT_wait_for_ack(uint8_t* ack_str)
{
    memset((void *)rx_str, 0, sizeof(rx_str));    
    UART_Tx_flush();					                        // Required due to usage of consoleReceiveCh with large timeout
    consoleReceiveCh(&rx_str[0], 255, 200);    

    //printf("%s\r\n", rx_str);
    if (strstr((uint8_t*)&rx_str[0], (uint8_t*)ack_str) != 0)
      return SUCCESS;    
    else
      return FAIL;
 }
