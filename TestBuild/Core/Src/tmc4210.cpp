/*
 * tmc4210.cpp
 *
 *  Created on: Jun 5, 2023
 *      Author: tarun
 */
#include "tmc4210.h"
#include "stm32f4xx_hal.h"

/*!
 * Implementation of the TMC4210 intializer method
 *
 * Inputs:
 * 		SPI_HandleTypeDef* _hspi: Pointer to SPI instance
 * 		TIM_HandleType* _htim: Pointer to timer
 * 		uint16_t _CS: Chip select pin
 * 		uint16_t _EN: Enable pin
 * Initializes new TMC4210 object with the given inputs
 */
tmc4210::tmc4210(SPI_HandleTypeDef* _hspi, TIM_HandleTypeDef* _htim, uint16_t _CS, uint16_t _EN){
	hspi = _hspi;
	htim = _htim;
	CS = _CS;
	EN = _EN;
	HAL_GPIO_WritePin(GPIOA, EN, GPIO_PIN_RESET);
}

/*!
 * Implementation of the send method
 * Inputs:
 * 		uint8_t* _tdata_buf: Pointer to data buffer with info to be transmitted
 * 		uint16_t size: Size of the above data buffer
 * 		uint32_t timeout: Timeout (milliseconds)
 * A general send method that sends a specified data buffer of a specified size to the tmc4210 object
 */
void tmc4210::send(uint32_t sendMode){
	if(sendMode == 0){
		transmit_buf[0] = pos_buf[0];
		transmit_buf[1] = pos_buf[1];
		transmit_buf[2] = pos_buf[2];
		transmit_buf[3] = pos_buf[3];
	}else if(sendMode == 1){
		transmit_buf[0] = en_sd_buf[0];
		transmit_buf[1] = en_sd_buf[1];
		transmit_buf[2] = en_sd_buf[2];
		transmit_buf[3] = en_sd_buf[3];
	}else if(sendMode == 2){
		transmit_buf[0] = vmax_buf[0];
		transmit_buf[1] = vmax_buf[1];
		transmit_buf[2] = vmax_buf[2];
		transmit_buf[3] = vmax_buf[3];
	}else if(sendMode == 3){
		transmit_buf[0] = vmin_buf[0];
		transmit_buf[1] = vmin_buf[1];
		transmit_buf[2] = vmin_buf[2];
		transmit_buf[3] = vmin_buf[3];
	}else if(sendMode == 4){
		transmit_buf[0] = prdiv_buf[0];
		transmit_buf[1] = prdiv_buf[1];
		transmit_buf[2] = prdiv_buf[2];
		transmit_buf[3] = prdiv_buf[3];
	}else if(sendMode == 5){
		transmit_buf[0] = amax_buf[0];
		transmit_buf[1] = amax_buf[1];
		transmit_buf[2] = amax_buf[2];
		transmit_buf[3] = amax_buf[3];
	}else if(sendMode == 6){
		transmit_buf[0] = pmuldiv_buf[0];
		transmit_buf[1] = pmuldiv_buf[1];
		transmit_buf[2] = pmuldiv_buf[2];
		transmit_buf[3] = pmuldiv_buf[3];
	}else if(sendMode == 7){
		transmit_buf[0] = ramp_buf[0];
		transmit_buf[1] = ramp_buf[1];
		transmit_buf[2] = ramp_buf[2];
		transmit_buf[3] = ramp_buf[3];
	}

	HAL_GPIO_WritePin(GPIOB, CS, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, transmit_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, CS, GPIO_PIN_SET);
}

/*!
 * Implementation of the send method
 * Inputs:
 * 		uint32_t timeout: Timeout (milliseconds)
 * Outputs:
 * 		uint32_t value: value of the register that was read
 * A general receive method that reads from the tmc4210 and returns that value
 */
uint32_t tmc4210::recieve(uint32_t recvMode){
	if(recvMode == 1){
		transmit_buf[0] = xPos_addr[0];
		transmit_buf[1] = 0x00;
		transmit_buf[2] = 0x00;
		transmit_buf[3] = 0x00;
	}else if(recvMode == 2){
		transmit_buf[0] = vmax_addr[0];
		transmit_buf[1] = 0x00;
		transmit_buf[2] = 0x00;
		transmit_buf[3] = 0x00;
	}else if(recvMode == 3){
		transmit_buf[0] = typeReg_addr[0];
		transmit_buf[1] = 0x00;
		transmit_buf[2] = 0x00;
		transmit_buf[3] = 0x00;
	}
	HAL_GPIO_WritePin(GPIOB, CS, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, transmit_buf, recieve_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, CS, GPIO_PIN_SET);
	/*
	recieve_buf[3] = recieve_buf[2];
	recieve_buf[2] = recieve_buf[1];
	recieve_buf[1] = recieve_buf[0];
	recieve_buf[0] = 0x00;
	*/

	uint32_t value = (uint32_t)(recieve_buf[1] << 16 | recieve_buf[2] << 8 | recieve_buf[3]);
	return value;
}

/*!
 * Implementation of the set_pos method
 * Inputs:
 * 		uint32_t pos: Desired set position in degrees
 * The setPos method takes in a desired position in degrees and converts that to microsteps. The microsteps are
 * converted to a 3-byte buffer and transmitted to the tmc4210 object via SPI.
 */
void tmc4210::setPos(int32_t pos){
	int32_t microsteps = (0.5556)*8*pos;
	pos_buf[0] = 0x00;
	pos_buf[1] = (microsteps >> 16);
	pos_buf[2] = (microsteps >> 8);
	pos_buf[3] = (microsteps >> 0);
	this->send(0);
}

/*!
 * Implementation of the getPos method
 * Outputs:
 * 		uint32_t currentPos: current postion that the tmc4210 object is at
 * The getPos method returns the current postion of the stepper motor that the tmc4210 object has access to.
 * The returned value is in degrees.
 */
uint32_t tmc4210::getPos(){
	int32_t microsteps = this->recieve(1);
	int32_t currentPos = microsteps*(0.125)*(1.8);
	return currentPos;
}

/*!
 * Implementation of the setup method
 * This method sends the appropriate data to the appropriate registers to configure/setup the tmc4210
 */
void tmc4210::setup(){
	this->send(1);		//! Set en_sd to 1 to enable the Step/Dir interface to the driver IC
	this->send(2);		//! Set the velocity parameter V_MAX
	this->send(3);		//! Set the velocity parameter V_MIN
	this->send(4);  	//! Set the clock pre-dividers PULSE_DIV and RAMP_DIV
	this->send(5);   	//! Set A_MAX with a valid pair of PMUL and PDIV
	this->send(6);		//! Valid pair of PMUL and PDIV
	this->send(7);      //! Choose the ramp mode with RAMP_MODE register
}

