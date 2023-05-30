/*
 * it.c
 *
 *  Created on: May 27, 2023
 *      Author: musta
 */
#include"main.h"
extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef sADC;

void SysTick_Handler(){
	HAL_IncTick();
}

void TIM2_IRQHandler(){
	HAL_TIM_IRQHandler(&htim2);
}

void ADC_IRQHandler(){
	HAL_ADC_IRQHandler(&sADC);

}

void EXTI15_10_IRQHandler(){
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13)!= RESET) {
				HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
			}
		else{
			Error_Handler();
		}
}

