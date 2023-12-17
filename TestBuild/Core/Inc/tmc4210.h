/*
 * tmc4210.h
 *
 *  Created on: Jun 5, 2023
 *      Author: tarun
 */

#ifndef INC_TMC4210_H_
#define INC_TMC4210_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>

class tmc4210
{
private:
	SPI_HandleTypeDef* hspi;
	TIM_HandleTypeDef* htim;

	uint16_t EN = 0;
	uint16_t CS = 0;

	uint8_t en_sd_buf[4] = {0b01101000, 0b00000000, 0b00000000, 0b00100000};	//!enable step/dir on tmc4210
	uint8_t vmax_buf[4] = {0b00000110, 0b00000000, 0b00000000, 0b01111111};		//!set vmin
	uint8_t vmin_buf[4] = {0b00000100, 0b00000000, 0b00000000, 0b00000001};		//!set vmax
	uint8_t prdiv_buf[4] = {0b00011000, 0b00000000, 0b01000100, 0b00000000};	//!clock pre-divders for PULSE_DIV &  RAMP_DIV
	uint8_t amax_buf[4] = {0b00001100, 0b00000000, 0b00000000, 0b1001011};		//!set amax
	uint8_t pmuldiv_buf[4] = {0b00010010, 0b00000000, 0b10010100, 0b00000101};  //!valid pmul and pdiv
	uint8_t ramp_buf[4] = {0b00010100, 0b00000000, 0b00000000, 0b00000000};		//!choose ramp mode

	uint8_t transmit_buf[4] = {0b00000000, 0b00000000, 0b00000000, 0b00000000}; //!generic transmit buffer
	uint8_t recieve_buf[4] = {0b00000000, 0b00000000,0b00000000, 0b00000000};   //!generic recieve buffer
	int8_t pos_buf[4] = {0b00000000, 0b00000000,0b00000000, 0b00000000};       //!position transmit buffer

	uint8_t xPos_addr[1] = {0b00000011};
	uint8_t vmax_addr[1] = {0b00000111};
	uint8_t typeReg_addr[1] = {0b01110011};

public:
	tmc4210(SPI_HandleTypeDef* _hspi, TIM_HandleTypeDef* _htim, uint16_t _CS, uint16_t _EN);
	void send(uint32_t sendMode);
	uint32_t recieve(uint32_t recvMode);
	void setPos(int32_t pos);
	uint32_t getPos();
	void setup();
};




#endif /* INC_TMC4210_H_ */
