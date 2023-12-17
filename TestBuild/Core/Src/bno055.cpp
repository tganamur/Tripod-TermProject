/*!
 * IMU.cpp
 *
 *  Created on: May 24, 2023
 *      Author: tarun
 */

#include <bno055.h>
#include "stm32f4xx_hal.h"

/*!
 * Implementation of the IMU initializer method
 *
 * Inputs:
 * 		I2C_HandleTypeDef* _hi2c: Pointer to i2c instance
 *
 * Initializes a new IMU object with the given inputs
 */
bno055::bno055(I2C_HandleTypeDef* _hi2c){
	hi2c1 = _hi2c;
}

/*!
 * Implementation of the read_oneByte method
 *
 * Inputs:
 * 		uint32_t _IMU_Dev_addr: IMU device address
 * Output:
 * 		int16_t data1: the byte of data from the specified register
 *
 * A general read method that reads one byte data from a specified register and returns that data (one byte of data)
 */
int16_t bno055::read_oneByte(uint32_t _IMU_reg_addr){
	HAL_I2C_Mem_Read(hi2c1, IMU_Dev_addr, _IMU_reg_addr, I2C_MEMADD_SIZE_8BIT, oneByte_buf, 1, 100);
	int16_t data1 = oneByte_buf[0];
	if(data1 > 0x7FFF){
		data1 |= 0xF0000;
	}
	return data1;
}

/*!
 * Implementation of the read_twoByte method
 *
 * Inputs:
 * 		uint32_t _IMU_Dev_addr: IMU device address
 *
 * Output:
 * 		int16_t data2: the combined two bytes of data from the specified two consecutive registers
 *
 * A general purpose read method that two bytes reads data from a specified registers (consecutive registers) and returns that data (two bytes of data)
 */
int16_t bno055::read_twoByte(uint32_t _IMU_reg_addr){
	HAL_I2C_Mem_Read(hi2c1, IMU_Dev_addr, _IMU_reg_addr, I2C_MEMADD_SIZE_8BIT, twoByte_buf, 2, 100);
/*
	int32_t data2 = (twoByte_buf[1] << 8) | twoByte_buf[0];
	if(data2 > 0x7FFF){
			data2 |= 0xF0000;
	}
	return data2;
*/

	int16_t data2 = 0;
	if(twoByte_buf[1] > 0x7F){
		data2 =  ((twoByte_buf[1] << 8 | twoByte_buf[0]) | 0xF0000);
	}else{
		data2 = ((twoByte_buf[1] << 8) | twoByte_buf[0]);
	}
	return data2;

}
/*!
 * Implementation of the write method
 *
 * Inputs:
 * 		uint32_t _IMU_Dev_addr: IMU device address
 * 		uint8_t* _pdata_buf: Pointer to the data buffer which has data to be written into specified register
 * 		uint32_t _data_buf_size: Size of data buffer
 *
 * A general writes method that write data to a specified register from a specified data buffer
 */
void bno055::write(uint32_t _IMU_reg_addr, uint8_t* _pdata_buf, uint32_t _data_buf_size){
	HAL_I2C_Mem_Write(hi2c1, IMU_Dev_addr, _IMU_reg_addr, I2C_MEMADD_SIZE_8BIT, _pdata_buf, _data_buf_size, 100);
}


/*!
 * Get x-axis gyro data
 *
 * Output:
 * 		int16_t gyrx_data: combined MSB & LSB of x-axis gyro data
 */
int16_t bno055::read_gyr_x(){
	//HAL_I2C_Mem_Read(hi2c1, IMU_Dev_addr, gyrx_reg_addr, I2C_MEMADD_SIZE_8BIT, gyrx_buf, 2, 100);
	uint16_t gyrx_data = read_twoByte(gyrx_reg_addr);
	return bound(gyrx_data, 0, 360);
}

/*!
 * Get y-axis gyro data
 * Output:
 * 		int16_t gyry_data: combined MSB & LSB of y-axis gyro data
 */
int16_t bno055::read_gyr_y(){
	//HAL_I2C_Mem_Read(hi2c1, IMU_Dev_addr, gyry_reg_addr, I2C_MEMADD_SIZE_8BIT, gyry_buf, 2, 100);
	uint16_t gyry_data = read_twoByte(gyry_reg_addr);
	return bound(gyry_data, 0, 360);
}

/*!
 * Get z-axis gyro data
 * Output:
 * 		int16_t gyrz_data: combined MSB & LSB of z-axis gyro data
 */
int16_t bno055::read_gyr_z(){
	//HAL_I2C_Mem_Read(hi2c1, IMU_Dev_addr, gyrz_reg_addr, I2C_MEMADD_SIZE_8BIT, gyrz_buf, 2, 100);
	uint16_t gyrz_data = read_twoByte(gyrz_reg_addr);
	return bound(gyrz_data, 0, 360);
}

/*!
 * Get x-axis euler angle data
 * Output:
 * 		int16_t eulx_data: combined MSB & LSB of x-axis euler angle data (heading)
 */
int16_t bno055::read_eul_x(){
	//HAL_I2C_Mem_Read(hi2c1, IMU_Dev_addr, eulx_reg_addr, I2C_MEMADD_SIZE_8BIT, eulx_buf, 2, 100);
	int16_t eulx_data = read_twoByte(eulx_reg_addr);
	//return bound(eulx_data, 0, 360);
	return eulx_data/16;
}

/*!
 * Get y-axis euler angle data
 * Output:
 * 		int16_t euly_data: combined MSB & LSB of y-axis euler angle data (roll)
 */
int16_t bno055::read_eul_y(){
	//HAL_I2C_Mem_Read(hi2c1, IMU_Dev_addr, euly_reg_addr, I2C_MEMADD_SIZE_8BIT, euly_buf, 2, 100);
	int16_t euly_data = read_twoByte(euly_reg_addr);
	//return bound(euly_data, 0, 360);
	return euly_data/16;
}

/*!
 * Get z-axis euler angle data
 * Output:
 * 		int16_t eulz_data: combined MSB & LSB of z-axis euler angle data (pitch)
 */
int16_t bno055::read_eul_z(){
	//HAL_I2C_Mem_Read(hi2c1, IMU_Dev_addr, eulz_reg_addr, I2C_MEMADD_SIZE_8BIT, eulz_buf, 2, 100);
	int16_t eulz_data = read_twoByte(eulz_reg_addr);
	//return bound(eulz_data, 0, 360);
	return eulz_data/16;
}
/*!
 * Bound a value in a specified range
 * Inputs:
 * 		int16_t value: value to be bounded
 * 		int16_t start: start value of bounding range
 * 		int16_t end: end value of bounding range
 * Outputs:
 * 		int16_t bounded value: the bounded value bounded by the specified min and max
 */
int bno055::bound(int value, int start, int end){
  int width = end - start;
  int offsetValue = value - start;
  return (offsetValue - ((offsetValue/width) * width)) + start;
}
