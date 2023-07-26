/*
 * 25lc040a.c
 *
 *  Created on: 2019. 3. 22.
 *      Author: KIKI
 */

#include "25lc040a.h"

SPI_HandleTypeDef* EEPROM_SPI;
GPIO_TypeDef* EEPROM_SS_Port;
uint16_t EEPROM_SS_Pin;

static void SS_Select();
static void SS_Deselect();

void EEPROM_Init(SPI_HandleTypeDef* spi, GPIO_TypeDef* ss_port, uint16_t ss_pin)
{
	EEPROM_SPI = spi;
	EEPROM_SS_Port = ss_port;
	EEPROM_SS_Pin = ss_pin;
}

bool EEPROM_WriteEnable(void)
{
	uint8_t data = EEPROM_CMD_WREN;
	SS_Select();
	if(HAL_SPI_Transmit(EEPROM_SPI, &data, 1, HAL_MAX_DELAY) != HAL_OK) return false;
	SS_Deselect();

	return true;
}

bool EEPROM_ReadByte(uint16_t address, uint8_t* ret)
{
	uint8_t cmd2;
	
	if((address > 255) && (address < 512)) {
		cmd2 = EEPROM_CMD_READ | (1 << 3);
	} else {
			cmd2 = EEPROM_CMD_READ;
	}
	
	uint8_t data[2] = {cmd2, address};

	SS_Select();
	if(HAL_SPI_Transmit(EEPROM_SPI, data, sizeof(data), HAL_MAX_DELAY) != HAL_OK) return false;
	if(HAL_SPI_Receive(EEPROM_SPI, ret, 1, HAL_MAX_DELAY) != HAL_OK) return false;
	SS_Deselect();

	return true;
}

bool EEPROM_WriteByte(uint16_t address, uint8_t data)
{
	uint8_t cmd2;
	
	if((address > 255) && (address < 512)) {
		cmd2 = EEPROM_CMD_WRITE | (1 << 3);
	} else {
			cmd2 = EEPROM_CMD_WRITE;
	}
	
	uint8_t buffer[3] = {cmd2, address, data};

	if(!EEPROM_WriteEnable()) return false;
	SS_Select();
	if(HAL_SPI_Transmit(EEPROM_SPI, buffer, sizeof(buffer), HAL_MAX_DELAY) != HAL_OK) return false;
	SS_Deselect();

	/* Wait write cycle time 5ms */
	HAL_Delay(50);

	return true;
}

bool EEPROM_Write1Page(uint8_t pageNumber, uint8_t* data)
{
	uint8_t cmd2;
	uint16_t address = EEPROM_PAGE_SIZE * pageNumber;
	
	if((address > 255) && (address < 512)) {
		cmd2 = EEPROM_CMD_WRITE | (1 << 3);
	} else {
			cmd2 = EEPROM_CMD_WRITE;
	}
	
	uint8_t buffer[2 + EEPROM_PAGE_SIZE] = {cmd2, address};
	for(uint8_t i = 2; i < 18; i++) {
		buffer[i] = data[i-2];
	}
	
	if(!EEPROM_WriteEnable()) return false;
	SS_Select();
	if(HAL_SPI_Transmit(EEPROM_SPI, buffer, sizeof(buffer), HAL_MAX_DELAY) != HAL_OK) return false;
	SS_Deselect();
	
	HAL_Delay(50);
	
	return true;
}

bool EEPROM_EraseAll(void)
{
	uint8_t pageNumber = 0;
	uint8_t clrArr[16] = {0};	
		
	while(pageNumber < EEPROM_NUMBER_OF_PAGES)
	{
		EEPROM_Write1Page(pageNumber, (uint8_t*)clrArr);
		pageNumber += 1;
	}

	return true;
}

static void SS_Select()
{
	HAL_GPIO_WritePin(EEPROM_SS_Port, EEPROM_SS_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
}

static void SS_Deselect()
{
	HAL_GPIO_WritePin(EEPROM_SS_Port, EEPROM_SS_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
}
