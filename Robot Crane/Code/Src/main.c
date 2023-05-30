/*
 * main.c
 *
 *  Created on: May 27, 2023
 *      Author: musta
 */

#include "main.h"

TIM_HandleTypeDef htim2;
ADC_HandleTypeDef sADC;
uint32_t value[3];
uint32_t ADC_value[3];

int main(){
	HAL_Init();
	SystemClock_Config();
	Tim_PWM_Init();
	ADC_Init();
	Button_init();

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK)
			Error_Handler();

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2) != HAL_OK)
			Error_Handler();

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) != HAL_OK)
			Error_Handler();

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4) != HAL_OK)
			Error_Handler();


	while(1){
		ADC_SET_CH0();
		HAL_ADC_Start(&sADC);
		HAL_ADC_PollForConversion(&sADC, 1000);
		ADC_value[0] = HAL_ADC_GetValue(&sADC);
		value[0] = convert_adc_reading(HAL_ADC_GetValue(&sADC));
		HAL_ADC_Stop(&sADC);
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,value[0]);

		ADC_SET_CH1();
		HAL_ADC_Start(&sADC);
		HAL_ADC_PollForConversion(&sADC, 1000);
		ADC_value[1] = HAL_ADC_GetValue(&sADC);
		value[1] = convert_adc_reading(HAL_ADC_GetValue(&sADC));
		HAL_ADC_Stop(&sADC);
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,value[1]);

		ADC_SET_CH4();
		HAL_ADC_Start(&sADC);
		HAL_ADC_PollForConversion(&sADC, 1000);
		ADC_value[2] = HAL_ADC_GetValue(&sADC);
		value[2] = convert_adc_reading(HAL_ADC_GetValue(&sADC));
		HAL_ADC_Stop(&sADC);
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,value[2]);

		HAL_Delay(10);
	}
	return 0;
}

void SystemClock_Config(){
	RCC_OscInitTypeDef osc_config = {0};
	RCC_ClkInitTypeDef clk_config = {0};

	osc_config.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_config.HSEState = RCC_HSE_BYPASS;
	if(HAL_RCC_OscConfig(&osc_config) != HAL_OK)
		Error_Handler();

	clk_config.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clk_config.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_SYSCLK ;
	clk_config.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_config.APB1CLKDivider = RCC_HCLK_DIV1;
	clk_config.APB2CLKDivider = RCC_HCLK_DIV1;
	if(HAL_RCC_ClockConfig(&clk_config, FLASH_LATENCY_0) != HAL_OK)
		Error_Handler();

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

void Error_Handler(){
	while(1);

}

void Tim_PWM_Init(){
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 160;
	htim2.Init.Period = 1000-1;

	if(HAL_TIM_PWM_Init(&htim2) != HAL_OK)
		Error_Handler();

	TIM_OC_InitTypeDef pwm_config = {0};
	pwm_config.Pulse = 25;
	pwm_config.OCMode = TIM_OCMODE_PWM1;
	pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;

	if(HAL_TIM_PWM_ConfigChannel(&htim2, &pwm_config, TIM_CHANNEL_1 ) != HAL_OK)
		Error_Handler();

	if(HAL_TIM_PWM_ConfigChannel(&htim2, &pwm_config, TIM_CHANNEL_2) != HAL_OK)
		Error_Handler();

	if(HAL_TIM_PWM_ConfigChannel(&htim2, &pwm_config, TIM_CHANNEL_3) != HAL_OK)
		Error_Handler();

	if(HAL_TIM_PWM_ConfigChannel(&htim2, &pwm_config, TIM_CHANNEL_4 ) != HAL_OK)
		Error_Handler();

	TIM_MspPostInit();


}

void ADC_Init(){

	sADC.Instance = ADC1;
	sADC.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	sADC.Init.Resolution = ADC_RESOLUTION_12B;
	sADC.Init.ScanConvMode = DISABLE;
	sADC.Init.ContinuousConvMode = DISABLE;
	sADC.Init.DiscontinuousConvMode = DISABLE;
	sADC.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	sADC.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	sADC.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	sADC.Init.NbrOfConversion = 1;
	sADC.Init.DMAContinuousRequests = DISABLE;
	sADC.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	  if (HAL_ADC_Init(&sADC) != HAL_OK)
	  {
	    Error_Handler();
	  }

}

void ADC_SET_CH0(){
	ADC_ChannelConfTypeDef CHConf = {0};
	CHConf.Channel = ADC_CHANNEL_0;
	CHConf.Rank = 1;
	CHConf.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	if(HAL_ADC_ConfigChannel(&sADC, &CHConf) != HAL_OK)
		Error_Handler();

}

void ADC_SET_CH1(){
	ADC_ChannelConfTypeDef CHConf = {0};
	CHConf.Channel = ADC_CHANNEL_1;
	CHConf.Rank = 1;
	CHConf.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	if(HAL_ADC_ConfigChannel(&sADC, &CHConf) != HAL_OK)
		Error_Handler();

}

void ADC_SET_CH4(){
	ADC_ChannelConfTypeDef CHConf = {0};
	CHConf.Channel = ADC_CHANNEL_4;
	CHConf.Rank = 1;
	CHConf.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	if(HAL_ADC_ConfigChannel(&sADC, &CHConf) != HAL_OK)
		Error_Handler();

}

void TIM_MspPostInit(){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef sPins = {0};
	sPins.Pin = GPIO_PIN_2 | GPIO_PIN_9 | GPIO_PIN_10;
	sPins.Mode = GPIO_MODE_AF_PP;
	sPins.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOB, &sPins);

	sPins.Pin = GPIO_PIN_15;
	HAL_GPIO_Init(GPIOA, &sPins);



	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);

}

int convert_adc_reading(int adc_reading) {
    int result = (adc_reading * 100) / 4095;  // Scale the reading to the range of 0-100
    result += 25;  // Shift the reading to the range of 25-125
    return result;
}

void Button_init(){
		GPIO_InitTypeDef Button = {0};
		Button.Pin = GPIO_PIN_13;
		Button.Mode = GPIO_MODE_IT_RISING;
		Button.Pull = GPIO_PULLDOWN;
		HAL_GPIO_Init(GPIOC, &Button);

		HAL_NVIC_SetPriority(EXTI15_10_IRQn, 15, 0);
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
