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
	uint32_t mantissaPart = 0;
	uint32_t fractionPart = 0;
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
		USART_Handle->Instance->BRR = __USART_BRR_OVERSAMPLING_8(periphClock, USART_Handle->Init.BaudRate);
		USART_DIV_VALUE = __USART_DIV_VALUE_16(periphClock, USART_Handle->Init.BaudRate);
	}
	else
	{
		USART_Handle->Instance->BRR = __USART_BRR_OVERSAMPLING_16(periphClock,  USART_Handle->Init.BaudRate);
	}
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
	// 9 bit = frame no parity // 9 bit = frame yes parity
	// 8 bit = frame no parity // 8 bit = frame yes parity
	// 7 bit = frame no parity // 7 bit = frame yes parity

	uint16_t *data9Bits;
	uint8_t *data6Bits;

	if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{
		data9Bits = (uint16_t *)pData;
	}
	else if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_7Bits) && (USART_Handle->Init.Parity != USART_PARITY_NONE) )
	{
		data9Bits = NULL;
		data6Bits = pData;
	}
	else
	{
		data9Bits = NULL;
		data6Bits = NULL;
	}

	while( dataSize > 0 )
	{
		while( !(USART_GetFlagStatus(USART_Handle, USART_TXE_FLAG)) );

		/* 9 bits data no parity is for ELSE condition,
		 * 6 bits data with parity is for ELSE IF condition,
		 * for other you will be in IF case */
		if( data9Bits == NULL && data6Bits == NULL)
		{
			USART_Handle->Instance->TDR = (uint8_t)(*pData & (0xFFU) );
			pData++;
			dataSize--;
		}
		else if( data6Bits != NULL)
		{
			USART_Handle->Instance->TDR = (uint8_t)(*data6Bits & (0x3FU) );
			data6Bits++;
			dataSize--;
		}
		else
		{
			USART_Handle->Instance->TDR = (uint16_t)(*data9Bits & (0x01FFU) );
			data9Bits++;
			dataSize -=2;
		}
	}
	while( !(USART_GetFlagStatus(USART_Handle, USART_TC_FLAG)) );
}

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
