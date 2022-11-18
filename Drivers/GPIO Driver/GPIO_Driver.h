
#include "stm32f446xx.h"
#include "stm32f4xx.h"                  // Device header
	
#ifndef GPIO_Driver
#define GPIO_Driver

#define GPIO_BUTTON_PIN 										13

	/*=============================================================================
										1.Macros used for pin Intialization
	===============================================================================*/
	
	// GPIO Mode Setting Values
		#define GPIO_PIN_MODE_INPUT							((uint32_t) 0x00)
		#define GPIO_PIN_MODE_OUTPUT						((uint32_t) 0x01)
		#define GPIO_PIN_MODE_AF								((uint32_t) 0x02)
		#define GPIO_PIN_MODE_ANALOG						((uint32_t) 0x03)
	
	// GPIO OP Type Selection Values
		#define GPIO_PIN_OP_PUSH_PULL						((uint32_t) 0x00)
		#define GPIO_PIN_OP_OPEN_DRAIN					((uint32_t) 0x01)
	
	// GPIO Speed Type Selection Values
		#define GPIO_PIN_SPEED_LOW							((uint32_t) 0x00)
		#define GPIO_PIN_SPEED_MED							((uint32_t) 0x01)
		#define GPIO_PIN_SPEED_HIGH							((uint32_t) 0x02)
		#define GPIO_PIN_SPEED_VHIGH						((uint32_t) 0x03)
		
	// GPIO Pull Up Pull Down Selection Values
		#define GPIO_PIN_NO_PUPD								((uint32_t) 0x00)
		#define GPIO_PIN_PULLUP									((uint32_t) 0x01)
		#define GPIO_PIN_PULLDOWN								((uint32_t) 0x02)
		
	// GPIO Port Base ADD

		#define GPIO_PORT_A											GPIOA
		#define GPIO_PORT_B											GPIOB
		#define GPIO_PORT_C											GPIOC
		#define GPIO_PORT_D											GPIOD
		#define GPIO_PORT_E											GPIOE
		#define GPIO_PORT_F											GPIOF
		#define GPIO_PORT_G											GPIOG
		#define GPIO_PORT_H											GPIOH
		
	// Enable Clock for Different GPIO ports Functions
	
		#define _HAL_RCC_GPIOA_CLK_ENABLE()       (RCC->AHB1ENR |=  (1 << 0) )
		#define _HAL_RCC_GPIOB_CLK_ENABLE()				(RCC->AHB1ENR |=	(1 << 1) )
		#define _HAL_RCC_GPIOC_CLK_ENABLE()				(RCC->AHB1ENR |=	(1 << 2) )
		#define _HAL_RCC_GPIOD_CLK_ENABLE()				(RCC->AHB1ENR |=	(1 << 3) )
		#define _HAL_RCC_GPIOE_CLK_ENABLE()				(RCC->AHB1ENR |=	(1 << 4) )
		#define _HAL_RCC_GPIOF_CLK_ENABLE()				(RCC->AHB1ENR |=	(1 << 5) )
		#define _HAL_RCC_GPIOG_CLK_ENABLE()				(RCC->AHB1ENR |=	(1 << 6) )
		#define _HAL_RCC_GPIOH_CLK_ENABLE()				(RCC->AHB1ENR |=	(1 << 7) )
	
	
	/*=============================================================================
											2.Data Structure For Pin Intialization
	===============================================================================*/
	
	typedef struct{
					uint32_t pin;
					uint32_t mode;
					uint32_t op_type;
					uint32_t pull;
					uint32_t speed;
					uint32_t af;
	}gpio_pin_conf_t;
	

	typedef enum {
				INT_RISING_EDGE,
				INT_FALLING_EDGE,
				INT_RISING_FALLING_EDGE
	}int_edge_sel_t;
	
	/*=============================================================================
												3.Inzilization API
		===============================================================================*/
	
	void hal_gpio_init(GPIO_TypeDef *GPIOx , gpio_pin_conf_t *gpio_pin_conf);
	
	/*=============================================================================
												3.Read/Write API
	===============================================================================*/
	uint8_t hal_gpio_pin_read(GPIO_TypeDef *GPIOx, uint16_t pin_no);
	void hal_gpio_pin_write(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t value);

	/*=============================================================================
												4.Interrupt Handling API
	===============================================================================*/
	void hal_gpio_conf_interrupt(uint16_t pin,int_edge_sel_t edge_sel);
	void hal_gpio_enable_interrupt(uint16_t pin,IRQn_Type irq_no);
	void hal_gpio_clear_interrupt(uint16_t pin);
	
#endif
