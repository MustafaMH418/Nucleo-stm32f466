/*
 * main.c
 *
 *  Created on: Nov 21, 2022
 *      Author: musta
 */


#include "main.h"


UART_HandleTypeDef huart2;
char *user_data = "App is Running ... \r\n";
uint8_t rcvd_data ;
uint8_t data_buff[100];
uint32_t count = 0;

void SystemClock_Config();
void Error_Handler();
void UART2_init();
uint8_t small_to_capital(uint8_t data);

int main(){
	char msg[100];
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;


	memset(msg,0,sizeof(msg));

	HAL_Init();
	UART2_init();

	uint16_t len = strlen(user_data);
	if(HAL_UART_Transmit(&huart2,(uint8_t *) user_data, len, HAL_MAX_DELAY) != HAL_OK)
		Error_Handler();

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_BYPASS;

	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
		Error_Handler();

	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE ;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2 ;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV2 ;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV2 ;

	if(HAL_RCC_ClockConfig(&clk_init, FLASH_ACR_LATENCY_0WS)!= HAL_OK)
		Error_Handler;

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	UART2_init();

	sprintf(msg,"SysClk     : %ld Hz \r\n",HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);

	sprintf(msg,"HCLK       : %ld Hz \r\n",HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);

	sprintf(msg,"PCLK1      : %ld Hz \r\n",HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);

	sprintf(msg,"PCLK2      : %ld Hz \r\n",HAL_RCC_GetPCLK2Freq());
		HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);


	return 0 ;
}

void UART2_init(){
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1 ;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;

	if(HAL_UART_Init(&huart2)!= HAL_OK )
		Error_Handler();

}





void Error_Handler(){
	while(1);
}
