/*
 * pwm.c
 *
 *  Created on: May 9, 2024
 *      Author: Arif Mandal
 */

#include "pwm.h"


void pwmChannelStart(TIM_HandleTypeDef *htim, uint32_t channel){

	HAL_TIM_PWM_Start(htim, channel);
}

void pwmChannelStop(TIM_HandleTypeDef *htim, uint32_t channel){

	HAL_TIM_PWM_Stop(htim, channel);
}

void setPWMFreqDuty(float frequency, float dutyCycle){

	TIM4 ->ARR = (int) (1000000.0/frequency);
	TIM4 -> CCR1 = (int) ((TIM4 ->ARR) * (dutyCycle/100.0));
}

