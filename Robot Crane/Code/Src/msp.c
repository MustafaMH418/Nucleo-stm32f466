/*
 * msp.c
 *
 *  Created on: May 27, 2023
 *      Author: musta
 */

#include "main.h"
uint8_t Claw_Flag;
extern TIM_HandleTypeDef htim2;

 void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim){
	__HAL_RCC_TIM2_CLK_ENABLE();
}


void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc){
	__HAL_RCC_ADC1_CLK_ENABLE();
	GPIO_InitTypeDef sPins;
	sPins.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4;
	sPins.Mode = GPIO_MODE_ANALOG;
	sPins.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &sPins);

	HAL_NVIC_SetPriority(ADC_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(ADC_IRQn);

}

 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(Claw_Flag == 1){
	  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,25); // Closing Claw
	  Claw_Flag = 0;
  }
  else{
	  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,75); // Closing Claw
	  	  Claw_Flag = 1;
  }
}
