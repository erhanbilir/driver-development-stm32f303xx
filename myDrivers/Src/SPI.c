#include "SPI.h"

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

