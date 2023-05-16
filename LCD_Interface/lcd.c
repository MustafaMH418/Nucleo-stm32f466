#include "lcd.h"
void Lcd_Write(char data, uint8_t rs){
	HAL_GPIO_WritePin(rs_port, rs_pin, rs);

	HAL_GPIO_WritePin(D7_port, D7_pin, (data>>3)&0x01);
	HAL_GPIO_WritePin(D6_port, D6_pin, (data>>2)&0x01);
	HAL_GPIO_WritePin(D5_port, D5_pin, (data>>1)&0x01);
	HAL_GPIO_WritePin(D4_port, D4_pin, (data>>0)&0x01);

	HAL_GPIO_WritePin(en_port, en_pin, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(en_port, en_pin, GPIO_PIN_RESET);
	HAL_Delay(10);

}

void Lcd_Send_Cmd(char cmd){
	char cmd_to_send = 0;
	cmd_to_send = (cmd >> 4) & 0x0f ;
	Lcd_Write(cmd_to_send,0);
	cmd_to_send = cmd & 0x0f ;
	Lcd_Write(cmd_to_send,0);
}

void Lcd_Send_Data(char data){
	char data_to_send = 0;
	data_to_send = (data >> 4) & 0x0f ;
	Lcd_Write(data_to_send,1);
	data_to_send = data & 0x0f ;
	Lcd_Write(data_to_send,1);
}

void Lcd_Send_String(char *str){
	while(*str != '\0')
		Lcd_Send_Data(*str++);
}

void Lcd_Clear(){
	Lcd_Send_Cmd(0x01);
}

void Lcd_Put_Cursor(int row,int col){
	switch(row){
	case 0:
		col |= 0x80;
		break;
	case 1:
		col |= 0xC0;
		break;
	}

	Lcd_Send_Cmd(col);
}


void LCD_Init(){
	HAL_Delay(50);
	Lcd_Write(0x03,0);
	HAL_Delay(5);
	Lcd_Write(0x3, 0);
	HAL_Delay(2);
	Lcd_Write(0x3, 0);
	HAL_Delay(2);

	Lcd_Write(0x02,0);
	HAL_Delay(2);

	Lcd_Send_Cmd(0x28);
	HAL_Delay(2);
	Lcd_Send_Cmd(0x08);
	HAL_Delay(2);
	Lcd_Send_Cmd(0x01);
	HAL_Delay(2);
	Lcd_Send_Cmd(0x06);
	HAL_Delay(2);
	Lcd_Send_Cmd(0x0C);
	HAL_Delay(2);

}
