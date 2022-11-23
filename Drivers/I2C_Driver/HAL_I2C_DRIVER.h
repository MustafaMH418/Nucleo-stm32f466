#ifndef __HAL_i2c_Driver_H
#define __HAL_i2c_Driver_H

#include <stdint.h>
#include "stm32f446xx.h"


/*=====================================================================================================*/
/*																				   1.Bit Definations 																				 */
/*=====================================================================================================*/
//----------------------------------------CR1------------------------------------------

// Periphral Enable Bit
#define I2C_CR1_PE_Bit																(uint32_t)(1<<0)
	#define I2C_CR1_PE_Disable												 ~(I2C_CR1_PE_Bit)
	#define I2C_CR1_PE_Enable														 I2C_CR1_PE_Bit
	
// NOSTRETCH BIT
#define I2C_CR1_NoStretch_Bit												(uint32_t)(1<<7)
	#define I2C_CR1_NoStretch_Disabled						 ~(I2C_CR1_NoStretch_Bit)					
	#define I2C_CR1_NoStretch_Enabled								 I2C_CR1_NoStretch_Bit	

// START BIT
#define I2C_CR1_Start_Bit														(uint32_t)(1<<8)
	#define I2C_CR1_Start_Clear											~(I2C_CR1_Start_Bit)
	#define I2C_CR1_Start_Set													I2C_CR1_Start_Bit
	
// STOP BIT
#define I2C_CR1_Stop_Bit															(uint32_t)(1<<9)
	#define I2C_CR1_Stop_Clear											~(I2C_CR1_Stop_Bit)
	#define I2C_CR1_Stop_Set													I2C_CR1_Stop_Bit
	
// ACK BIT
#define I2C_CR1_Ack_Bit														  (uint32_t)(1<<10)
	#define I2C_CR1_NAck														 ~(I2C_CR1_Ack_Bit)
	#define I2C_CR1_Ack																 I2C_CR1_Ack_Bit
	
// POS BIT
#define I2C_CR1_POS_BIT														 (uint32_t)(1<<11)
	#define I2C_CR1_Pos_Disable											~(I2C_CR1_POS_BIT)
	#define I2C_CR1_Pos_Enable												I2C_CR1_POS_BIT

//----------------------------------------CR2------------------------------------------

// ERROR INTERRUPT ENABLE BIT
#define I2C_CR2_ITERREN_Bit													(uint32_t)(1<<8)
	#define I2C_CR2_ITERREN_Disable									~(I2C_CR2_ITERREN_Bit)
	#define I2C_CR2_ITERREN_Enable										I2C_CR2_ITERREN_Bit
	
// EVENT INTERRUPT ENABLE BIT
#define I2C_CR2_ITEVTEN_Bit													(uint32_t)(1<<9)
	#define I2C_CR2_ITEVTEN_Disable									~(I2C_CR2_ITEVTEN_Bit)
	#define I2C_CR2_ITEVTEN_Enable										I2C_CR2_ITEVTEN_Bit
	
// BUFFER INTERRUPT ENABLE BIT
#define I2C_CR2_ITBUFEN_Bit													(uint32_t)(1<<10)
	#define I2C_CR2_ITBUFEN_Disable									~(I2C_CR2_ITBUFEN_Bit)
	#define I2C_Cr2_ITBUFEN_Enable										I2C_CR2_ITBUFEN_Bit
	
#define I2C_PERIPHERAL_CLK_FREQ_2MHZ      					((uint32_t)(2) )  
#define I2C_PERIPHERAL_CLK_FREQ_3MHZ      					((uint32_t)(3) )  
#define I2C_PERIPHERAL_CLK_FREQ_4MHZ     						((uint32_t)(4) )  
#define I2C_PERIPHERAL_CLK_FREQ_5MHZ     						((uint32_t)(5) )  
#define I2C_PERIPHERAL_CLK_FREQ_6MHZ     						((uint32_t)(6) )  
#define I2C_PERIPHERAL_CLK_FREQ_7MHZ     						((uint32_t)(7) )  
#define I2C_PERIPHERAL_CLK_FREQ_8MHZ     						((uint32_t)(8) ) 
#define I2C_PERIPHERAL_CLK_FREQ_9MHZ     						((uint32_t)(9) )  
#define I2C_PERIPHERAL_CLK_FREQ_10MHZ     					((uint32_t)(10)) 

//----------------------------------------OAR1------------------------------------------
#define I2C_OAR1_ADDMODE_BIT												(uint32_t)(1<<15)
	#define I2C_OAR1_ADDMODE_7BIT										~(I2C_OAR1_ADDMODE_BIT)
	#define I2C_OAR1_ADDMODE_14BIT										I2C_OAR1_ADDMODE_BIT

//----------------------------------------SR1------------------------------------------
#define I2C_SR1_SB_FLAG															(uint32_t)(1<<0)			// Start Generated
#define I2C_SR1_ADDR_FLAG														(uint32_t)(1<<1)			// Address Matched/sent
#define I2C_SR1_BTF_FLAG														(uint32_t)(1<<2)			// Bit Transmiting Finished
#define I2C_SR1_STOP_FLAG														(uint32_t)(1<<4)			// Stop Detected
#define I2C_SR1_RXNE_FLAG														(uint32_t)(1<<6)			// Rx Not Empty
#define I2C_SR1_TXE_FLAG														(uint32_t)(1<<7)			// Tx Empty
#define I2C_SR1_BERR_FLAG														(uint32_t)(1<<8)			// Bus Error
#define I2C_SR1_AF_FLAG															(uint32_t)(1<<10)			// Acknowledge failure
#define I2C_SR1_OVR_FLAG														(uint32_t)(1<<11)			// Overrun/Underrun
#define I2C_SR1_PECERR_FLAG													(uint32_t)(1<<12)			// Pec Error
#define I2C_SR1_TIMEOUT_FLAG												(uint32_t)(1<<14)			// Timeout


//----------------------------------------SR2------------------------------------------
#define I2C_SR2_BUSY_BIT														(uint32_t)(1<<1)
	#define I2C_BUS_IS_BUSY																	1
	#define I2C_BUS_IS_NOT_BUSY															0

#define I2C_SR2_MSL_BIT															(uint32_t)(1<<0)
	#define I2C_SLAVE																				0
	#define I2C_MASTER																			1
	
#define I2C_SR2_TRA_BIT															(uint32_t)(1<<2)
	#define I2C_RX																					0
	#define I2C_TX																					1
	
//----------------------------------------CCR------------------------------------------
#define I2C_CCR_FS_MODE_BIT													(uint32_t)(1<<15)
	#define I2C_SM_MODE																				0
	#define I2C_FM_MODE																				1

#define I2C_CCR_DUTY_BIT														(uint32_t)(1<<14)
	#define I2C_DUTY_FM_16_9																	1
	#define I2C_DUTY_FM_2																			0

/*=====================================================================================================*/
/*																				   2.Data Structure 																				 */
/*=====================================================================================================*/

typedef enum{
	HAL_I2C_STATE_RESET														=0x00,
	HAL_I2C_STATE_READY														=0x01,
	HAL_I2C_STATE_BUSY														=0x02,
	HAL_I2C_STATE_BUSY_TX													=0x03,
	HAL_I2C_STATE_BUSY_RX													=0x04,
	HAL_I2C_STATE_MEM_BUSY_TX											=0x05,
	HAL_I2C_STATE_MEM_BUSY_RX											=0x06,
	HAL_I2C_STATE_TIMEOUT													=0x07,
	HAL_I2C_STATE_ERROR														=0x08
}hal_i2c_state_t;

typedef struct{
	uint32_t ClockSpeed;
	uint32_t DutyCycle;
	uint32_t OwnAddress1;
	uint32_t AddressingMode;
	uint32_t DualAddressMode;
	uint32_t OwnAddress2;
	uint32_t GeneralCallMode;
	uint32_t NoStretchMode;
	uint32_t Ack_Enable;
	uint8_t  Master;
}i2c_init_t;

typedef struct{
	I2C_TypeDef					*Instance;
	i2c_init_t					Init;
	uint8_t							*pBuffPtr;
	uint32_t						XferSize;
	__IO uint32_t				XferCount;
	hal_i2c_state_t 		State;
	uint32_t						ErrorCode;
}i2c_handle_t;


/*=====================================================================================================*/
/*																				   3.Clock Enable Macros																		 */
/*=====================================================================================================*/
#define _HAL_RCC_I2C1_CLK_ENABLE()				(RCC->APB1ENR |= (1<<21)
#define _HAL_RCC_I2C2_CLK_ENABLE()				(RCC->APB1ENR |= (1<<22)
#define _HAL_RCC_I2C3_CLK_ENABLE()				(RCC->APB1ENR |= (1<<23)

/*=====================================================================================================*/
/*																				   4.Base Addresses																					 */
/*=====================================================================================================*/
#define I2C_1																				I2C1
#define I2C_2																				I2C2
#define I2C_3																				I2C3


#define  RESET  																			0 
#define  SET  																		 a!RESET

#endif
