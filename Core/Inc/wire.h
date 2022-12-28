/*
 * wire.h
 *
 *  Created on: Dec 28, 2022
 *      Author: mherc
 */

#ifndef INC_WIRE_H_
#define INC_WIRE_H_

#pragma once

#include "stm32l4xx.h"

/* #############################
 * reset signal
 * Sends reset signal to device
 * #############################*/
HAL_StatusTypeDef wire_reset( void );

/* #############################
 * read data
 * Reads data from device
 * #############################*/
uint8_t wire_read( void );


/* #############################
 * send data
 * Sends data to device -> one byte
 * #############################*/
void wire_write( uint8_t byte );

/* #############################
 * get control sum
 * gets device scratchpad and
 * counts control sum
 * data -> pointer to data array
 * len -> data array length
 * #############################*/
uint8_t wire_crc( const uint8_t* data, int len);


#endif /* INC_WIRE_H_ */
