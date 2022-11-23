/*
 * msp.c
 *
 *  Created on: Nov 21, 2022
 *      Author: musta
 */
#include "main.h"

 void HAL_MspInit(void){
    // low level Processor Initilizing
	 HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);      // Setting Priority Grouping to (no subpriority"default")
	 SCB->SHCSR |= 0x7 <<16;                                  // Enabling Usage Fault, Bus Fault, Memory Mangment Fault
	 HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);       // Setting Priority to Highest Priority
	 HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);             // Setting Priority to Highest Priority
	 HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);               // Setting Priority to Highest Priority

}

 void HAL_UART_MspInit(UART_HandleTypeDef *huart)
 {
    //  Low Level Peripheral Initilizing 
   __HAL_RCC_USART2_CLK_ENABLE();                          // Enabling UART2 Clock
   __HAL_RCC_GPIOA_CLK_ENABLE();                           // Enabling GPIOA Clock

   GPIO_InitTypeDef gpio_uart;
   gpio_uart.Pin = GPIO_PIN_2;
   gpio_uart.Mode = GPIO_MODE_AF_PP;
   gpio_uart.Pull = GPIO_PULLUP;
   gpio_uart.Speed = GPIO_SPEED_LOW;
   gpio_uart.Alternate = GPIO_AF7_USART2;                 // AF7 = UART2 (Tx on PA2, Rx on PA3)
   HAL_GPIO_Init(GPIOA, &gpio_uart);

   gpio_uart.Pin = GPIO_PIN_3;
   HAL_GPIO_Init(GPIOA,&gpio_uart);

   HAL_NVIC_EnableIRQ(USART2_IRQn);                      // Enabling IRQHAndler
   HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);            



 }
