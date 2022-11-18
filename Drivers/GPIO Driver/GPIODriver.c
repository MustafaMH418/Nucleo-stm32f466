
#include "GPIO_Driver.h"
#include<stdint.h>

/*=======================================================================================================================*/
//																						Intilization Parameters 																									 //
/*=======================================================================================================================*/

//PIN Mode Set Function
static void hal_gpio_conf_pin_mode(GPIO_TypeDef *GPIOx, uint16_t pin_no , uint32_t mode){
	
	GPIOx->MODER |= (mode << (pin_no *2));
	
}

//PIN Speed Set Function
static void hal_gpio_conf_pin_speed(GPIO_TypeDef *GPIOx, uint16_t pin_no , uint32_t speed){
	
	GPIOx->OSPEEDR |= ( speed << (pin_no *2 ));
	
}

//PIN Output Type Set Function
static void hal_gpio_conf_pin_OpType(GPIO_TypeDef *GPIOx, uint16_t pin_no , uint32_t type){
	
	GPIOx->OTYPER |= ( type << (pin_no));
	
}

//PIN Pull Up Pull Down Set Function
static void hal_gpio_conf_pin_pupd(GPIO_TypeDef *GPIOx, uint16_t pin_no , uint32_t pupd){
	
	GPIOx->PUPDR |= (pupd << (pin_no *2));
	
}

//PIN Alternate Function Set Function
static void hal_gpio_conf_pin_AF(GPIO_TypeDef *GPIOx, uint16_t pin_no , uint32_t AF){
	
	if(pin_no <= 7)
		GPIOx->AFR[0] |= (AF << (pin_no *4));
	else
		GPIOx->AFR[1] |= (AF << ((pin_no *4)-32));
}
/*=======================================================================================================================*/
//																						Intilization API 																									 //
/*=======================================================================================================================*/
void hal_gpio_init(GPIO_TypeDef *GPIOx , gpio_pin_conf_t *gpio_pin_conf){
	hal_gpio_conf_pin_mode(GPIOx,gpio_pin_conf->pin,gpio_pin_conf->mode);
	hal_gpio_conf_pin_speed(GPIOx,gpio_pin_conf->pin,gpio_pin_conf->speed);
	hal_gpio_conf_pin_OpType(GPIOx,gpio_pin_conf->pin,gpio_pin_conf->op_type);
	hal_gpio_conf_pin_pupd(GPIOx,gpio_pin_conf->pin,gpio_pin_conf->pull);
}

/*=======================================================================================================================*/
//																						  Read/Write APis 																												 //
/*=======================================================================================================================*/

uint8_t hal_gpio_pin_read(GPIO_TypeDef *GPIOx, uint16_t pin_no){
	uint32_t value;
	value = ((GPIOx->IDR >> pin_no) & 0x00000001);
	return (uint8_t)value;
}

void hal_gpio_pin_write(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t value){
	if(value)
		GPIOx->ODR |= ( 1 << pin_no);
	else
		GPIOx->ODR &= ~(1 << pin_no);
}

/*=======================================================================================================================*/
//																						  Interrupt Handling API																									 //
/*=======================================================================================================================*/

void hal_gpio_conf_interrupt(uint16_t pin,int_edge_sel_t edge_sel){
	if(edge_sel == INT_FALLING_EDGE)
		EXTI->FTSR |= 1 << pin;
	else if (edge_sel == INT_RISING_EDGE)
		EXTI->RTSR |= 1<< pin;
	else if (edge_sel == INT_RISING_FALLING_EDGE){
		EXTI->FTSR |= 1 << pin;
		EXTI->RTSR |= 1<< pin;
  }
}

void hal_gpio_enable_interrupt(uint16_t pin,IRQn_Type irq_no){
	EXTI->IMR |= 1 << pin;
	NVIC_EnableIRQ(irq_no);
}

void hal_gpio_clear_interrupt(uint16_t pin){
	if(EXTI->PR & (1 << pin))
		EXTI->PR |= 1 << pin;
}


