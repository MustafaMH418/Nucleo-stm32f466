/*
 * lcd.h
 *
 *  Created on: Mar 18, 2023
 *      Author: musta
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"
#define rs_pin			GPIO_PIN_8
#define rs_port			GPIOB

#define en_pin			GPIO_PIN_9
#define en_port			GPIOB

#define D7_pin			GPIO_PIN_6
#define D7_port			GPIOB

#define D6_pin			GPIO_PIN_7
#define D6_port			GPIOA

#define D5_pin			GPIO_PIN_6
#define D5_port			GPIOA

#define D4_pin			GPIO_PIN_5
#define D4_port			GPIOA


void Lcd_Write(char data, uint8_t rs);
void Lcd_Send_Cmd(char cmd);
void Lcd_Send_Data(char data);
void Lcd_Send_String(char *str);
void Lcd_Clear();
void Lcd_Put_Cursor(int row,int col);
void LCD_Init();

#endif /* INC_LCD_H_ */
