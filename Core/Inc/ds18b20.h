/*
 * ds18b20.h
 *
 *  Created on: Dec 28, 2022
 *      Author: mherc
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#pragma once

#include "stm32l4xx.h"

#define DS18B20_ROM_CODE_SIZE		8

/*
 * Store address bytes (8) in array
 * rom_code - address array poiner
 * returns HAL_OK/HAL_ERROR
 */
HAL_StatusTypeDef ds18b20_read_address(uint8_t* rom_code);

/*
 * Sends start meassure comand
 * rom_code - device address array pointer or NULL
 * returns HAL_OK/HAL_ERROR
 */
HAL_StatusTypeDef ds18b20_start_measure(const uint8_t* rom_code);

/*
 * Gets temperature from device
 * rom_code - device address array pointer or NULL
 * returns temperature in Celsius degrees
 */
float ds18b20_get_temp(const uint8_t* rom_code);

#endif /* INC_DS18B20_H_ */
