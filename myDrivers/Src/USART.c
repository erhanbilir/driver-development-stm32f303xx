/*
 * USART.c
 *
 *  Created on: Dec 10, 2024
 *      Author: erhan
 */
#include "USART.h"

/*
 *  @brief	USART_PeriphCmd, enable or disable USART peripheral
 *
 *  @param	USART_Handle = User config structure
 *
 *	@param  stateOfUSART = ENABLE or DISABLE
 *
 *  @retval None
 */

void USART_PeriphCmd(USART_HandleTypeDef_t *USART_Handle, FunctionalState_t stateOfUSART)
{
	if( stateOfUSART == ENABLE)
	{
		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_ENABLE);
	}
	else
	{
		USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_ENABLE);
	}
}

/*
 *  @brief	USART_Init, configures the USART Peripheral
 *
 *  @param	USART_Handle = User config structure
 *
 *  @retval None
 */

void USART_Init(USART_HandleTypeDef_t *USART_Handle)
{
	uint32_t periphClock = 0;
	uint32_t USART_DIV_VALUE = 0;
	/******** Mode & WordLength & Parity & OverSampling ********/

	uint32_t tempReg = 0;

	tempReg = USART_Handle->Instance->CR1;

	tempReg |= (USART_Handle->Init.Mode) | (USART_Handle->Init.WordLength) | \
			   (USART_Handle->Init.Parity) | (USART_Handle->Init.OverSampling);

	USART_Handle->Instance->CR1 = tempReg;

	/******** StopBits ********/

	tempReg = USART_Handle->Instance->CR2;

	tempReg &= ~(0x3U << USART_CR2_STOP);
	tempReg |= (USART_Handle->Init.StopBits);

	USART_Handle->Instance->CR2 = tempReg;

	/******** HardwareFlowControl ********/

	tempReg = USART_Handle->Instance->CR3;

	tempReg |= (USART_Handle->Init.HardwareFlowControl);

	USART_Handle->Instance->CR3 = tempReg;

	/******** BaudRate Configuration ********/

	if( USART_Handle->Instance == USART1)
	{
		periphClock = RCC_GetP2Clock();
	}
	else
	{
		periphClock = RCC_GetP1Clock();
	}



	if( USART_Handle->Init.OverSampling == USART_OVERSAMPLE_8 )
	{
		USART_DIV_VALUE = __USART_DIV_VALUE_8(periphClock, USART_Handle->Init.BaudRate);
		tempReg = (USART_DIV_VALUE & 0xFFF0);
		tempReg |= ((USART_DIV_VALUE & 0x000FU) >> 1U);
	}
	else
	{
		USART_DIV_VALUE = __USART_DIV_VALUE_16(periphClock, USART_Handle->Init.BaudRate);
		tempReg = USART_DIV_VALUE;
	}

	USART_Handle->Instance->BRR = tempReg;
}

/*
 *  @brief	USART_TransmitData, transmits data
 *
 *  @param	USART_Handle = User config structure
 *
 *	@param  pData = Address of data to send
 *
 *	@param dataSize = Length of your data in bytes
 *
 *  @retval None
 */

void USART_TransmitData(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t dataSize)
{

	uint16_t *data16Bits;
	uint8_t *data8Bits;

	if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{
		data16Bits = (uint16_t *)pData;
		data8Bits = NULL;
	}
	else
	{
		data16Bits = NULL;
		data8Bits = pData;
	}

	while( dataSize > 0 )
	{
		while( !(USART_GetFlagStatus(USART_Handle, USART_TXE_FLAG)) );

		/* 9 bits data no parity is for ELSE condition, for others you will be in IF case */
		if( data16Bits == NULL)
		{
			USART_Handle->Instance->TDR = (uint8_t)(*data8Bits & (0xFFU) );
			data8Bits++;
			dataSize--;
		}
		else
		{
			USART_Handle->Instance->TDR = (uint16_t)(*data16Bits & (0x01FFU) );
			data16Bits++;
			dataSize-=2;
		}
	}
	while( !(USART_GetFlagStatus(USART_Handle, USART_TC_FLAG)) );
}

/*
 *  @brief	USART_ReceiveData, receives data
 *
 *  @param	USART_Handle = User config structure
 *
 *	@param  pBuffer = Address of data to store
 *
 *	@param dataSize = Length of your data in bytes
 *
 *  @retval None
 */

void USART_ReceiveData(USART_HandleTypeDef_t *USART_Handle, uint8_t *pBuffer, uint16_t dataSize)
{
	uint16_t *p16BitsBuffer;
	uint8_t *p8BitsBuffer;

	if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{
		p16BitsBuffer = (uint16_t*)pBuffer;
		p8BitsBuffer = NULL;
	}
	else
	{
		p16BitsBuffer = NULL;
		p8BitsBuffer = pBuffer;
	}


	while(dataSize > 0)
	{
		while( !(USART_GetFlagStatus(USART_Handle, USART_RXNE_FLAG)));

		if( p8BitsBuffer == NULL)
		{
			*p16BitsBuffer = (uint16_t)(USART_Handle->Instance->RDR & 0x01FFU);
			p16BitsBuffer++;
			dataSize+=2;
		}
		else
		{
			if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (USART_Handle->Init.Parity != USART_PARITY_NONE) )
			{
				*p8BitsBuffer = USART_Handle->Instance->RDR & 0x00FFU;
				p8BitsBuffer++;
				dataSize--;
			}
			else if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_8Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
			{
				*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->RDR & 0xFFU);
				p8BitsBuffer++;
				dataSize--;
			}
			else
			{
				*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->RDR & 0x7FU);
				p8BitsBuffer++;
				dataSize--;
			}
		}
	}
}

void USART_TransmitData(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t dataSize);

/*
 *  @brief	USART_GetFlagStatus, return the flag of ISR register
 *
 *  @param	USART_Handle = User config structure
 *
 *	@param  USART_Flag = Flag name of ISR register
 *
 *  @retval FlagStatus_t
 */

FlagStatus_t USART_GetFlagStatus(USART_HandleTypeDef_t *USART_Handle, uint16_t USART_Flag)
{
	return (USART_Handle->Instance->ISR & USART_Flag) ? FLAG_SET : FLAG_RESET;
}
