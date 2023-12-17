/*
 * dcMotorDriver.cpp
 *
 *  Created on: Apr 20, 2023
 *      Author: tarun
 */
# include "dcMotorDriver.h"

/*!
 * Implementation of the enable method for the dcMotor
 * Inputs:
 * 		dcmotor_t dcMotor: struct instance of type dcmotor
 * This method takes an instance of a dcmotor struct and starts the timer channels associated with that instance.
 */
void enable(dcmotor_t dcMotor){
	HAL_TIM_PWM_Start(dcMotor.htim, dcMotor.tim_ch1);
    HAL_TIM_PWM_Start(dcMotor.htim, dcMotor.tim_ch2);
}

/*!
 * Implementation of the disable method for the dcMotor
 * Inputs:
 * 		dcmotor_t dcMotor: struct instance of type dcmotor
 * This method takes an instance of a dcmotor struct and stops the timer channels associated with that instance.
 */
void disable(dcmotor_t dcMotor){
	HAL_TIM_PWM_Stop(dcMotor.htim, dcMotor.tim_ch1);
	HAL_TIM_PWM_Stop(dcMotor.htim, dcMotor.tim_ch2);
}

/*!
 * Implementation of the setDuty method for the dcMotor
 * Inputs:
 * 		dcmotor_t dcMotor: struct instance of type dcmotor
 * 		int32_t duty_in: desired duty of dcmotor
 * This method takes an instance of a dcmotor struct and a signed integer duty and sets that duty to the dcmotor instance
 */
void setDuty(dcmotor_t dcMotor, int32_t duty_in){
	if(duty_in >= 0){
		//dcMotor.duty = duty_in;
		__HAL_TIM_SET_COMPARE(dcMotor.htim, dcMotor.tim_ch1, duty_in);
		__HAL_TIM_SET_COMPARE(dcMotor.htim, dcMotor.tim_ch2, 0);
	}else{
		// dcMotor.duty = -1*duty_in;
		__HAL_TIM_SET_COMPARE(dcMotor.htim, dcMotor.tim_ch1, 0);
		__HAL_TIM_SET_COMPARE(dcMotor.htim, dcMotor.tim_ch2, -duty_in);
	}
}
