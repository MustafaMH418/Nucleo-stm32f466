/*
 * main.h
 *
 *  Created on: May 27, 2023
 *      Author: musta
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "stm32f4xx_hal.h"
#include "stm32f446xx.h"



void SystemClock_Config();
void Error_Handler();
void ADC_SET_CH0();
void ADC_SET_CH1();
void ADC_SET_CH4();

void TIM_MspPostInit();
void Tim_PWM_Init();
void ADC_Init();
int convert_adc_reading(int adc_reading);
void Button_init();

#endif /* INC_MAIN_H_ */
