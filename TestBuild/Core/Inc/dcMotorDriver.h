/*
 * dcMotorDriver.h
 *
 *  Created on: Apr 20, 2023
 *      Author: tarun
 */

#ifndef INC_DCMOTORDRIVER_H_
#define INC_DCMOTORDRIVER_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct dcmotor{
	uint32_t tim_ch1;
	uint32_t tim_ch2;
	int32_t duty;
	TIM_HandleTypeDef*  htim;
}dcmotor_t;

void setDuty(dcmotor_t dcMotor, int32_t duty);
void enable(dcmotor_t dcMotor);
void disable(dcmotor_t dcMotor);


#endif /* INC_DCMOTORDRIVER_H_ */
