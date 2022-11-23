/*
 * main.c
 *
 *  Created on: Nov 21, 2022
 *      Author: musta
 */


#include "main.h"


UART_HandleTypeDef huart2;
char *user_data = "App is Running ... \r\n";				// data sent to indicate application states
uint8_t rcvd_data ;
uint8_t data_buff[100];										// receiving data buffer
uint32_t count = 0;

void SystemClock_Config();
void Error_Handler();
void UART2_init();
uint8_t small_to_capital(uint8_t data);

int main(){

	HAL_Init();
	SystemClock_Config();

	UART2_init();

	uint16_t len = strlen(user_data);

	if(HAL_UART_Transmit(&huart2,(uint8_t *) user_data, len, HAL_MAX_DELAY) != HAL_OK)
		Error_Handler();

	while(1){
		HAL_UART_Receive(&huart2, &rcvd_data, 1, HAL_MAX_DELAY);
		if(rcvd_data == '\r')
			break;
		else
			data_buff[count++] = small_to_capital(rcvd_data);
	}
	HAL_UART_Transmit(&huart2, data_buff, count, HAL_MAX_DELAY);
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

uint8_t small_to_capital(uint8_t data){
	if(data >= 'a' && data <= 'z')
		data = data - ('a'-'A');
	return data;
}

void SystemClock_Config(){

}

void Error_Handler(){

}
