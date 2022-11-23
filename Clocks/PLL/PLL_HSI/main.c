/*
 * main.c
 *
 *  Created on: Nov 21, 2022
 *      Author: musta
 */


#include "main.h"


UART_HandleTypeDef huart2;
char *user_data = "App is Running ... \r\n";


void SystemClock_Config();
void Error_Handler();
void UART2_init();
uint8_t small_to_capital(uint8_t data);

int main(){
	char msg[100];

	HAL_Init();
	SystemClock_Config(SYS_CLK_FREQ_50_MHZ);

	UART2_init();

	uint16_t len = strlen(user_data);

	if(HAL_UART_Transmit(&huart2,(uint8_t *) user_data, len, HAL_MAX_DELAY) != HAL_OK)
		Error_Handler();

	sprintf(msg,"SysClk     : %ld Hz \r\n",HaAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);

	sprintf(msg,"HCLK       : %ld Hz \r\n",HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);

	sprintf(msg,"PCLK1      : %ld Hz \r\n",HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);

	sprintf(msg,"PCLK2      : %ld Hz \r\n",HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);


	return 0;
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


void SystemClock_Config(){

	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI ;
	osc_init.HSIState = RCC_HSI_ON ;
	osc_init.HSICalibrationValue = 16 ;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	uint32_t Flatency = 0;
	uint32_t clock_freq = 0;
	switch(clock_freq){
	case SYS_CLK_FREQ_50_MHZ :
	{
		osc_init.PLL.PLLM = 16;
		osc_init.PLL.PLLN = 100;
		osc_init.PLL.PLLP = 2 ;
		osc_init.PLL.PLLR = 2 ;
		osc_init.PLL.PLLQ = 2 ;

		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSI ;
		clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2 ;
		clk_init.APB1CLKDivider = RCC_HCLK_DIV2 ;
		clk_init.APB2CLKDivider = RCC_HCLK_DIV2 ;

		Flatency = FLASH_ACR_LATENCY_1WS;
		break;
	}

	case SYS_CLK_FREQ_84_MHZ:
	{
		osc_init.PLL.PLLM = 16;
		osc_init.PLL.PLLN = 168;
		osc_init.PLL.PLLP = 2 ;
		osc_init.PLL.PLLR = 2 ;
		osc_init.PLL.PLLQ = 2 ;
		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSI ;
		clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2 ;
		clk_init.APB1CLKDivider = RCC_HCLK_DIV2 ;
		clk_init.APB2CLKDivider = RCC_HCLK_DIV2 ;
		Flatency = FLASH_ACR_LATENCY_2WS;
		break;
	}

	case SYS_CLK_FREQ_120_MHZ:
	{
		osc_init.PLL.PLLM = 16;
		osc_init.PLL.PLLN = 240;
		osc_init.PLL.PLLP = 2 ;
		osc_init.PLL.PLLR = 2 ;
		osc_init.PLL.PLLQ = 2 ;
		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSI ;
		clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2 ;
		clk_init.APB1CLKDivider = RCC_HCLK_DIV4 ;
		clk_init.APB2CLKDivider = RCC_HCLK_DIV2 ;
		Flatency = FLASH_ACR_LATENCY_3WS;
		break;
	}

	default :
		return;

	}


	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
		Error_Handler();

	if(HAL_RCC_ClockConfig(&clk_init, Flatency) != HAL_OK)
		Error_Handler();

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

}

void Error_Handler(){
	while(1);
}
