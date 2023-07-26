/*
 * 25lc040a.h
 *
 *  Created on: 2019. 3. 22.
 *      Author: KIKI
 */

#ifndef _25LC040A_H_
#define _25LC040A_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define EEPROM_CMD_WRITE	0x02
#define EEPROM_CMD_READ		0x03
#define EEPROM_CMD_RDSR		0x05
#define EEPROM_CMD_WREN		0x06

#define EEPROM_PAGE_SIZE	16
#define EEPROM_TOTAL_SIZE	128
#define EEPROM_NUMBER_OF_PAGES	32

void EEPROM_Init(SPI_HandleTypeDef* spi, GPIO_TypeDef* ss_port, uint16_t ss_pin);
bool EEPROM_WriteEnable(void);
bool EEPROM_ReadByte(uint16_t address, uint8_t *ret);
bool EEPROM_WriteByte(uint16_t address, uint8_t data);
bool EEPROM_EraseAll(void);
bool EEPROM_Write1Page(uint8_t pageNumber, uint8_t* data);

#endif /* _25LC040A_H_ */
