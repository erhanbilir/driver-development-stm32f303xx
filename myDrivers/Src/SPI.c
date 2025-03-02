#include "SPI.h"

/*
 *  @brief	SPI_CloseISR_TX, Disables the interrupt for transmission
 *
 *  @param	SPI_Handle = User config structure
 *
 *  @retval None
 */
static void SPI_CloseISR_TX(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_TXEIE);
	SPI_Handle->TxDataSize = 0;
	SPI_Handle->pTxDataAddr = NULL;
	SPI_Handle->busStateTx = SPI_BUS_FREE;
}


/*
 *  @brief	SPI_CloseISR_RX, Disables the interrupt for reception
 *
 *  @param	SPI_Handle = User config structure
 *
 *  @retval None
 */
static void SPI_CloseISR_RX(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_RXNEIE);
	SPI_Handle->RxDataSize = 0;
	SPI_Handle->pRxDataAddr = NULL;
	SPI_Handle->busStateRx = SPI_BUS_FREE;
}


/*
 *  @brief	SPI_TransmitHelper_16Bits, Stores the user data into the DR register for 16 bits format
 *
 *  @param	SPI_Handle = User config structure
 *
 *  @retval None
 */
static void SPI_TransmitHelper_16Bits(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->DR = *( (uint16_t*)(SPI_Handle->pTxDataAddr) );
	SPI_Handle->pTxDataAddr += sizeof(uint16_t);
	SPI_Handle->TxDataSize -= 2;

	if(SPI_Handle->TxDataSize == 0)
	{
		SPI_CloseISR_TX(SPI_Handle);
	}
}


/*
 *  @brief	SPI_TransmitHelper_8Bits, Stores the user data into the DR register for 8 bits format
 *
 *  @param	SPI_Handle = User config structure
 *
 *  @retval None
 */
static void SPI_TransmitHelper_8Bits(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->DR = *(uint8_t*)(SPI_Handle->pTxDataAddr );
	SPI_Handle->pTxDataAddr += sizeof(uint8_t);
	SPI_Handle->TxDataSize--;

	if(SPI_Handle->TxDataSize == 0)
	{
		SPI_CloseISR_TX(SPI_Handle);
	}
}


/*
 *  @brief	SPI_ReceiveHelper_16Bits, Receives the data from DR register
 *  		and stores into buffer the user variable for 16 bits format
 *
 *  @param	SPI_Handle = User config structure
 *
 *  @retval None
 */
static void SPI_ReceiveHelper_16Bits(SPI_HandleTypeDef_t *SPI_Handle)
{
	*( (uint16_t*)SPI_Handle->pRxDataAddr) = *( (__IO uint16_t*)SPI_Handle->Instance->DR);
	SPI_Handle->pTxDataAddr += sizeof(uint16_t);
	SPI_Handle->RxDataSize -= 2;

	if(SPI_Handle->RxDataSize == 0)
	{
		SPI_CloseISR_RX(SPI_Handle);
	}
}


/*
 *  @brief	SPI_ReceiveHelper_8Bits, Receives the data from DR register
 *  		and stores into buffer the user variable for 8 bits format
 *
 *  @param	SPI_Handle = User config structure
 *
 *  @retval None
 */
static void SPI_ReceiveHelper_8Bits(SPI_HandleTypeDef_t *SPI_Handle)
{
	*( (uint8_t*)SPI_Handle->pRxDataAddr) = *( (__IO uint8_t*)&SPI_Handle->Instance->DR);
	SPI_Handle->pRxDataAddr += sizeof(uint8_t);
	SPI_Handle->RxDataSize --;

	if(SPI_Handle->RxDataSize == 0)
	{
		SPI_CloseISR_RX(SPI_Handle);
	}
}


/*
 *  @brief	SPI_Init, configures the SPI Peripheral
 *
 *  @param	SPI_Handle = User config structure
 *
 *  @retval None
 */
void SPI_Init(SPI_HandleTypeDef_t *SPI_Handle)
{
	uint32_t tempValue = 0;

	tempValue = SPI_Handle->Instance->CR1;
	tempValue |= (SPI_Handle->Init.BaudRate) | (SPI_Handle->Init.CPHA) | (SPI_Handle->Init.CPOL) | \
				 (SPI_Handle->Init.Mode) | (SPI_Handle->Init.FrameFormat) | (SPI_Handle->Init.BusConfig) | (SPI_Handle->Init.SSM_Cmd);

	SPI_Handle->Instance->CR1 = tempValue;

	tempValue = 0;
	tempValue = SPI_Handle->Instance->CR2;
	tempValue |= SPI_Handle->Init.DataSize;
	SPI_Handle->Instance->CR2 = tempValue;
}


/*
 *  @brief	SPI_PeriphCmd, enable or disable SPI peripheral
 *
 *  @param	SPI_Handle = User config structure
 *
 *	@param  stateOfSPI = ENABLE or DISABLE
 *
 *  @retval None
 */
void SPI_PeriphCmd(SPI_HandleTypeDef_t *SPI_Handle, FunctionalState_t stateOfSPI)
{
	if(stateOfSPI == ENABLE)
	{
		SPI_Handle->Instance->CR1 |= (0x1U << SPI_CR1_SPE);
	}
	else
	{
		SPI_Handle->Instance->CR1 &= ~(0x1U << SPI_CR1_SPE);
	}

}


/*
 *  @brief	SPI_TransmitData, transmits data to the slave
 *
 *  @param	SPI_Handle = User config structure
 *
 *	@param  pData = Address of data to send
 *
 *	@param sizeOfData = Length of your data in bytes
 *
 *  @retval None
 */
void SPI_TransmitData(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	while(sizeOfData > 0)
	{
		if( SPI_GetFlagStatus(SPI_Handle, SPI_TXE_FLAG) )
		{
			SPI_Handle->Instance->DR = *pData;
			pData++;
			sizeOfData--;
		}
	}
	while( SPI_GetFlagStatus(SPI_Handle, SPI_BSY_FLAG) & 1); //Wait for busy flag
}


/*
 *  @brief	SPI_TransmitData_IT, transmits data to the external world with Interrupt method
 *
 *  @param	SPI_Handle = User config structure
 *
 *	@param  pData = Address of data to send
 *
 *	@param sizeOfData = Length of your data in bytes
 *
 *  @retval None
 */
void SPI_TransmitData_IT(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	SPI_BusStatus_t busState = SPI_Handle->busStateTx;

	if(busState != SPI_BUS_BUSY_TX)
	{
		SPI_Handle->pTxDataAddr = (uint8_t*)pData;
		SPI_Handle->TxDataSize = (uint16_t)sizeOfData;
		SPI_Handle->busStateTx = SPI_BUS_BUSY_TX;

		if( ((SPI_Handle->Instance->CR2 >> SPI_CR2_DS)  & 0xFU) == SPI_DATASIZE_16BIT)
		{
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_16Bits;
		}
		else
		{
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_8Bits;
		}

		SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_TXEIE);
	}
}


/*
 *  @brief	SPI_InterruptHandler, Provides control for interrupts
 *
 *  @param	SPI_Handle = User config structure
 *
 *  @retval None
 */
void SPI_InterruptHandler(SPI_HandleTypeDef_t *SPI_Handle)
{
	uint8_t interruptSource = 0;
	uint8_t interruptFlag = 0;

	interruptSource = (SPI_Handle->Instance->CR2 >> SPI_CR2_RXNEIE) & 0x1U;
	interruptFlag = (SPI_Handle->Instance->SR >> SPI_SR_RXNE) & 0x1U;

	if( (interruptSource != 0) && (interruptFlag != 0) )
	{
		SPI_Handle->RxISRFunction(SPI_Handle);
	}

	interruptSource = (SPI_Handle->Instance->CR2 >> SPI_CR2_TXEIE) & 0x1U;
	interruptFlag = (SPI_Handle->Instance->SR >> SPI_SR_TXE) & 0x1U;

	if( (interruptSource != 0) && (interruptFlag != 0) )
	{
		SPI_Handle->TxISRFunction(SPI_Handle);
	}
}


/*
 *  @brief	SPI_ReceiveData, receive data from the slave
 *
 *  @param	SPI_Handle = User config structure
 *
 *	@param  pBuffer = Address of data to store the values that I get
 *
 *	@param sizeOfData = Length of your data in bytes
 *
 *  @retval None
 */
void SPI_ReceiveData(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pBuffer, uint16_t sizeOfData)
{
	while(sizeOfData > 0)
	{
		if(SPI_GetFlagStatus(SPI_Handle, SPI_RXNE_FLAG))
		{
			*pBuffer = *( (__IO uint8_t*)&SPI_Handle->Instance->DR );
			pBuffer += sizeof(uint8_t);
			sizeOfData--;
		}
	}
	while( SPI_GetFlagStatus(SPI_Handle, SPI_RXNE_FLAG) & 0);
}


/*
 *  @brief	SPI_ReceiveData_IT, receive data from external world with Interrupt method
 *
 *  @param	SPI_Handle = User config structure
 *
 *	@param  pBuffer = Address of data to store the values that I get
 *
 *	@param sizeOfData = Length of your data in bytes
 *
 *  @retval None
 */
void SPI_ReceiveData_IT(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pBuffer, uint16_t sizeOfData)
{
	SPI_BusStatus_t busState = SPI_Handle->busStateRx;

	if(busState != SPI_BUS_BUSY_RX)
	{
		SPI_Handle->pRxDataAddr = (uint8_t*)pBuffer;
		SPI_Handle->RxDataSize = (uint16_t)sizeOfData;
		SPI_Handle->busStateRx = SPI_BUS_BUSY_RX;

		if( ((SPI_Handle->Instance->CR2 >> SPI_CR2_DS) & 0xFU) == SPI_DATASIZE_16BIT)
		{
			SPI_Handle->RxISRFunction = SPI_ReceiveHelper_16Bits;
		}
		else
		{
			SPI_Handle->RxISRFunction = SPI_ReceiveHelper_8Bits;
		}

		SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_RXNEIE);
	}
}


/*
 *  @brief	SPI_GetFlagStatus, return the flag of SR register
 *
 *  @param	SPI_Handle = User config structure
 *
 *	@param  SPI_FLag = Flag name of SR register
 *
 *  @retval FlagStatus_t
 */
FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypeDef_t *SPI_Handle, uint16_t SPI_Flag)
{
	return (SPI_Handle->Instance->SR & SPI_Flag) ? FLAG_SET : FLAG_RESET;
}

