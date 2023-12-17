/*
 * bno055.h
 *
 *  Created on: May 18, 2023
 *      Author: tarun
 */

#ifndef INC_BNO055_H_
#define INC_BNO055_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>

class bno055
{
private:
	I2C_HandleTypeDef* hi2c1;

	uint32_t IMU_Dev_addr = 0x28 << 1;     //! IMU device addr

	uint32_t gyrx_reg_addr = 0x14;    //! IMU x-axis gyro data register address
	uint32_t gyry_reg_addr = 0x16;    //! IMU y-axis gyro data register address
	uint32_t gyrz_reg_addr = 0x18;    //! IMU z-axis gyro data register address

    uint32_t eulx_reg_addr = 0x1A;     //! IMU x-axis euler angle data register address
    uint32_t euly_reg_addr = 0x1C;     //! IMU y-axis euler angle data register address
    uint32_t eulz_reg_addr = 0x1E;     //! IMU z-axis euler angle data register address

    uint8_t oneByte_buf[1] = {0};      //! one byte general purpose data buffer used to store one byte of data
    uint8_t twoByte_buf[2] = {0,0};    //! two byte general purpose data buffer used to store two bytes of data
/**
    uint8_t gyrx_buf[2] = {0,0};       //! two byte buffer to store LSB & MSB of x-axis gyro data
	uint8_t gyry_buf[2] = {0,0};       //! two byte buffer to store LSB & MSB of y-axis gyro data
	uint8_t gyrz_buf[2] = {0,0};       //! two byte buffer to store LSB & MSB of z-axis gyro data

	uint8_t eulx_buf[2] = {0,0};       //! two byte buffer to store LSB & MSB of x-axis euler angle data
	uint8_t euly_buf[2] = {0,0};       //! two byte buffer to store LSB & MSB of y-axis euler angle data
	uint8_t eulz_buf[2] = {0,0};       //! two byte buffer to store LSB & MSB of z-axis euler angle data
*/
public:

	bno055(I2C_HandleTypeDef* _hi2c);                                                    	//! IMU Initializer function
	int16_t read_oneByte(uint32_t _IMU_reg_addr);   	                					//! general read from IMU one byte memory register function
	int16_t read_twoByte(uint32_t _IMU_reg_addr);						   	                //! general read from IMU two byte memory register function
	void write(uint32_t _IMU_reg_addr, uint8_t* _pdata_buf, uint32_t _data_buf_size);     	//! general write to IMU memory register function
	int16_t read_gyr_x(); 				      											  	//! read data from gyroscope x-axis register
	int16_t read_gyr_y();					  												//! read data from gyroscope y-axis register
	int16_t read_gyr_z();					  												//! read data from gyroscope z-axis register

	int16_t read_eul_x();                    												//! read data from x-axis euler angle register
	int16_t read_eul_y();					  												//! read data from y-axis euler angle register
	int16_t read_eul_z();					  												//! read data from z-axis euler angle register
	int bound(int value, int start, int end);					                            //! method to bound a value in a given range
};


#endif /* INC_BNO055_H_ */
