#include "SPI_Driver.h"

void hal_spi_tx_close_interrupt(spi_handle_t *hspi);
/*=======================================================================================================================*/
//																										Helper Functions																									 //
/*=======================================================================================================================*/
// 1. Configure SPI mode
static void hal_spi_conf_mode(SPI_TypeDef *SPIx,uint32_t master){
	if(master)
		SPIx->CR1 |= SPI_MASTER;
	else
		SPIx->CR1 &= SPI_SLAVE;
}

// 1. Configure SPI Phase & Polarity
static void hal_spi_conf_phase_polarity(SPI_TypeDef *SPIx,uint32_t phase,uint32_t polarity){
	if(phase)
		SPIx->CR1 |= SPI_CPHA_SECOND_CLK_TRANS;
	else
		SPIx->CR1 &= SPI_CPHA_FIRST_CLK_TRANS;
	
	if(polarity)
		SPIx->CR1 |= SPI_CPOL_HIGH;
	else
		SPIx->CR1 &= SPI_CPOL_LOW;
}

// 2. Configure SPI Datasize & Edge
static void hal_spi_conf_datasize_edge(SPI_TypeDef *SPIx,uint32_t datasize_16,uint32_t lsbfirst){
	if(datasize_16)
		SPIx->CR1 |= SPI_16_BIT_EN;
	else
		SPIx->CR1 &= SPI_8_BIT_EN;

	if(lsbfirst)
		SPIx->CR1 |= SPI_LSB_FIRST;
	else
		SPIx->CR1 &= SPI_MSB_FIRST;

}
// 3. Configure SPI Direction
static void hal_spi_conf_bidirection(SPI_TypeDef *SPIx,uint32_t bi){
	if(bi)
		SPIx->CR1 |= SPI_EN_1Line_BI;
	else
		SPIx->CR1 &= SPI_EN_2Line_UNI;
}

// 4. Configure SPI Baud Rate with Macros Entries
static void hal_spi_conf_bd_rate(SPI_TypeDef *SPIx,uint32_t prescaler_val){
		SPIx->CR1 |= prescaler_val;
}

	
// 5. Configure SPI NSS for Master
static void hal_spi_conf_nss_master(SPI_TypeDef *SPIx,uint32_t ssm_enabled){
	if(ssm_enabled){
		SPIx->CR1 |= SPI_SSM_ENABLED;
		SPIx->CR1 |= SPI_REG_CR1_SSI;
	}
	else
		SPIx->CR1 &= SPI_SSM_DISABLED;
}

// 6. Configure SPI NSS for Slave
static void hal_spi_conf_nss_slave(SPI_TypeDef *SPIx,uint32_t ssm_enabled){
	if(ssm_enabled)
		SPIx->CR1 |= SPI_SSM_ENABLED;
	else
		SPIx->CR1 &= SPI_SSM_DISABLED;
}

// 7. Configure SPI Enable
static void hal_spi_conf_enable(SPI_TypeDef *SPIx){
	SPIx->CR1 |= SPI_ENABLE;
}

// 8. Configure SPI Disable
static void hal_spi_conf_disable(SPI_TypeDef *SPIx){
	SPIx->CR1 &= SPI_DISABLE;
}


/*=======================================================================================================================*/
//																				 Enable/Disable Tx/Rx Flags 																									 //
/*=======================================================================================================================*/

void hal_spi_enable_txe(SPI_TypeDef *SPIx){
	SPIx->CR2 |= SPI_REG_CR2_TXEIE_ENABLE;
}

void hal_spi_enable_rxne(SPI_TypeDef *SPIx){
	SPIx->CR2 |= SPI_REG_CR2_RXNEIE_ENABLE;
}

void hal_spi_disable_txe(SPI_TypeDef *SPIx){
	SPIx->CR2 &= ~SPI_REG_CR2_TXEIE_ENABLE;
}

void hal_spi_disable_rxne(SPI_TypeDef *SPIx){
	SPIx->CR2 &= ~SPI_REG_CR2_RXNEIE_ENABLE;
}

/*=======================================================================================================================*/
//																									Tx/RX API 																													 //
/*=======================================================================================================================*/

void hal_spi_master_tx(spi_handle_t *spi_handle,uint32_t *buffer,uint32_t len){
	
	spi_handle->pTxBuffPtr = buffer;
	spi_handle->TxCount = len;
	spi_handle->TxSize = len;
	
	spi_handle->State = HAL_SPI_STAT_BUSY_TX;
	
	hal_spi_conf_enable(spi_handle->Instance);
	
	hal_spi_enable_txe(spi_handle->Instance);
}

void hal_spi_master_rx(spi_handle_t *spi_handle,uint32_t *buffer,uint32_t len){
	uint32_t val;
	spi_handle->pTxBuffPtr = buffer;
	spi_handle->TxCount = len;
	spi_handle->TxSize = len;
	
	spi_handle->pRxBuffPtr = buffer;
	spi_handle->RxCount = len;
	spi_handle->RxSize = len;
	
	spi_handle->State = HAL_SPI_STAT_BUSY_RX;
	hal_spi_conf_enable(spi_handle->Instance);
	val = spi_handle->Instance->DR;
	
	hal_spi_enable_rxne(spi_handle->Instance);
	hal_spi_enable_txe(spi_handle->Instance);
}

void hal_spi_slave_tx(spi_handle_t *spi_handle,uint32_t *buffer,uint32_t len){
	spi_handle->pTxBuffPtr = buffer;
	spi_handle->TxCount = len;
	spi_handle->TxSize = len;
	
	spi_handle->pRxBuffPtr = buffer;
	spi_handle->RxCount = len;
	spi_handle->RxSize = len;
	
	spi_handle->State = HAL_SPI_STAT_BUSY_TX;
	
	hal_spi_conf_enable(spi_handle->Instance);
	
	hal_spi_enable_rxne(spi_handle->Instance);
	hal_spi_enable_txe(spi_handle->Instance);
	
}

void hal_spi_slave_rx(spi_handle_t *spi_handle,uint32_t *buffer,uint32_t len){
	spi_handle->pRxBuffPtr = buffer;
	spi_handle->RxCount = len;
	spi_handle->RxSize = len;
	
	spi_handle->State = HAL_SPI_STAT_BUSY_RX;
	
	hal_spi_conf_enable(spi_handle->Instance);
	
	hal_spi_enable_rxne(spi_handle->Instance);
}
/*=======================================================================================================================*/
//																						 TX/RX Handler 																									  				 //
/*=======================================================================================================================*/

void hal_spi_handle_tx_interrupt(spi_handle_t *hspi){
	if(hspi->Init.DataSize == SPI_8_BIT_EN){
		hspi->Instance->DR = (*hspi->pTxBuffPtr);
		hspi->TxCount --;
	}
	else{
		hspi->Instance->DR = *((uint16_t*)hspi->pTxBuffPtr);
		hspi->pTxBuffPtr += 2;
		hspi->TxCount -= 2;
	}
	if(hspi->TxCount == 0)
		hal_spi_tx_close_interrupt(hspi);
}
		
void hal_spi_handle_rx_interrupt(spi_handle_t *hspi){
	if(hspi->Init.DataSize == SPI_8_BIT_EN){
		if(hspi->pRxBuffPtr)
			(*hspi->pRxBuffPtr) = hspi->Instance->DR;
		hspi->RxCount --;
	}
	else{
		if(hspi->pRxBuffPtr)
			*((uint32_t *)hspi->pRxBuffPtr )= hspi->Instance->DR;
		hspi->RxCount -= 2;
	}
	
	if(hspi->RxCount == 0)
		hal_spi_close_rx_interrupt(hspi->Instance);
	
}

void hal_spi_tx_close_interrupt(spi_handle_t *hspi){
	hal_spi_disable_txe(hspi->Instance);
	
	if(hspi->Init.Mode && (hspi->State != HAL_SPI_STAT_BUSY))
		hspi->State = HAL_SPI_STAT_READY;
}

void hal_spi_rx_close_interrupt(spi_handle_t *hspi){
	while(hal_spi_is_bus_busy(hspi->Instance));
	
	hal_spi_disable_rxne(hspi->Instance);
	hspi->State = HAL_SPI_STAT_READY;
}

uint8_t hal_spi_is_NOT_bus_busy(SPI_TypeDef *SPIx){
	if(SPIx->SR & SPI_REG_SR_BSY_FLAG)
		return SPI_IS_BUSY;
	else
		return SPI_IS_NOT_BUSY;
}
			





	
/*=======================================================================================================================*/
//																					 	SPI IRQ Handler 																													 //
/*=======================================================================================================================*/
void hal_spi_i2c_irq_handler(spi_handle_t *hspi){
	uint32_t temp1 = 0, temp2 = 0;
	
	temp1 = (hspi->Instance->SR && SPI_REG_SR_RXNE_FLAG);
	temp2 = (hspi->Instance->CR2 && SPI_REG_CR2_RXNEIE_ENABLE);
	
	if(temp1 && temp2){
		hal_spi_handle_rx_interrupt(hspi);
		return;
	}
	
	temp1 = (hspi->Instance->SR && SPI_REG_SR_TXE_FLAG);
	temp2 = (hspi->Instance->CR2 && SPI_REG_CR2_TXEIE_ENABLE);
	
	if(temp1 && temp2){
		hal_spi_handle_tx_interrupt(hspi);
		return;
	}
}

