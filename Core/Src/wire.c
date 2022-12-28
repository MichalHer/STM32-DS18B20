/*
 * wire.c
 *
 *  Created on: Dec 28, 2022
 *      Author: mherc
 */


#include "wire.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"

// sets STM baudrate
static void set_boudrate( uint32_t baudrate ){
  huart3.Init.BaudRate = baudrate;
  if (HAL_HalfDuplex_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
}

// sends reset signal to device
HAL_StatusTypeDef wire_reset(void){
	uint8_t data_out = 0xF0;
	uint8_t data_in = 0;

	set_boudrate(9600);
	HAL_UART_Transmit(&huart3, &data_out, 1, HAL_MAX_DELAY);
	HAL_UART_Receive(&huart3, &data_in, 1, HAL_MAX_DELAY);
	set_boudrate(115200);

	if( data_in != 0xF0 )
		return HAL_OK;
	else
		return HAL_ERROR;
}

// wtites one bit of data
// 0 or 1
static void write_bit(int value)
{
  if (value) {
      uint8_t data_out = 0xff;
      HAL_UART_Transmit(&huart3, &data_out, 1, HAL_MAX_DELAY);
  } else {
      uint8_t data_out = 0x0;
      HAL_UART_Transmit(&huart3, &data_out, 1, HAL_MAX_DELAY);
  }
}

// reads one bit of data
static int read_bit(void)
{
  uint8_t data_out = 0xFF;
  uint8_t data_in = 0;
  HAL_UART_Transmit(&huart3, &data_out, 1, HAL_MAX_DELAY);
  HAL_UART_Receive(&huart3, &data_in, 1, HAL_MAX_DELAY);

  return data_in & 0x01;
}

// sends byte of data
void wire_write( uint8_t byte ){
	for( int i=0; i<8; i++){
		write_bit(byte & 0x01);
		byte >>= 1;
	}
}

// reads byte of data
uint8_t wire_read( void ){
	uint8_t result = 0;
	for( int i=0; i<8; i++){
		result >>= 1;
		if( read_bit() ){
			result |= 0x80;
		}
	}
	return result;
}


static uint8_t byte_crc(uint8_t crc, uint8_t byte)
{
  int i;
  for (i = 0; i < 8; i++) {
    uint8_t b = crc ^ byte;
    crc >>= 1;
    if (b & 0x01)
      crc ^= 0x8c;
    byte >>= 1;
  }
  return crc;
}

// counts control sum
uint8_t wire_crc(const uint8_t* data, int len)
{
    uint8_t crc = 0;
    for (int i = 0; i < len; i++)
      crc = byte_crc(crc, data[i]);
    return crc;
}
