/*
 * GPIO.c
 *
 *  Created on: Sep 5, 2024
 *      Author: erhan
 */

#include "GPIO.h"
/*
 *  @brief	GPIO_Init, configures the port and pin
 *
 *  @param	GPIOx = GPIO Port Base Address
 *
 *  param	GPIO_ConfigStruct = User Config Structures
 *
 *  @retval None
 */

void GPIO_Init(GPIO_TypeDef_t *GPIOx, GPIO_InitTypeDef_t *GPIO_ConfigStruct)
{
	uint32_t position;
	uint32_t fakePosition = 0;
	uint32_t lastPosition = 0;
	for(position = 0; position < GPIO_MAX_PIN_POSITION; position++)
	{
		fakePosition = (0x1U << position);
		lastPosition = (uint32_t)(GPIO_ConfigStruct->Pin) & fakePosition;
		if(fakePosition == lastPosition)
		{
			/* MODE Config */
			uint32_t tempValue = GPIOx->MODER;
			tempValue &= ~(0x3U << (position * 2));
			tempValue |= GPIO_ConfigStruct->Mode << (position * 2);
			GPIOx->MODER = tempValue;

			if(GPIO_ConfigStruct->Mode == GPIO_MODE_OUTPUT || GPIO_ConfigStruct->Mode == GPIO_MODE_AF)
			{
				/* OTYPE Config */
				tempValue = GPIOx->OTYPER;
				tempValue &= ~(0x1U << position);
				tempValue |= GPIO_ConfigStruct->Otype << position;
				GPIOx->OTYPER = tempValue;

				/* OSPEED Config */
				tempValue = GPIOx->OSPEEDR;
				tempValue &= ~(0x3U << (position * 2));
				tempValue |= GPIO_ConfigStruct->Speed << (position * 2);
				GPIOx->OSPEEDR = tempValue;

			}
			/* Push Pull Config */
			tempValue = GPIOx->PUPDR;
			tempValue &= ~(0x3U << (position * 2));
			tempValue |= GPIO_ConfigStruct->PuPd << (position * 2);
			GPIOx->PUPDR = tempValue;

			if(GPIO_ConfigStruct->Mode == GPIO_MODE_AF)
			{
				tempValue = GPIOx->AFR[position >> 3U]; //8'e bölme
				tempValue &= ~(0xFU << ( (position & 0x7U) * 4 ) ); //8'e mod alma
				tempValue |= (GPIO_ConfigStruct->Alternate << ( (position & 0x7U) * 4 ) );
				GPIOx->AFR[position >> 3U] = tempValue;
			}
		}
	}
}

/**
  * @brief  GPIO_WritePin, makes pin High or Low
  * @param  GPIOx = GPIO Port Base Address
  * @param  pinNumber = GPIO Pin Numbers 0 - 15 or All
  * @param  pinState can be GPIO_Pin_Set (HIGH) or GPIO_Pin_Reset (LOW)
  * @retval None
  */
void GPIO_WritePin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber, GPIO_PinState_t pinState)
{
	if(pinState == GPIO_Pin_Set)
	{
		GPIOx->BSRR = pinNumber;
	}
	else
	{
		GPIOx->BSRR = (pinNumber << 16U );
	}
}

/**
  * @brief  Reads the pin of GPIOx Port
  * @param  GPIOx = GPIO Port Base Address
  * @param  pinNumber = GPIO Pin Numbers 0 - 15 or All
  *
  * @retval GPIO_ReadPin return pin state as GPIO_PinState_t type (0 or 1)
  */
GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	GPIO_PinState_t bitStatus = GPIO_Pin_Reset;
	if((GPIOx->IDR & pinNumber) != GPIO_Pin_Reset)
	{
		bitStatus = GPIO_Pin_Set;
	}
	else
	{
		bitStatus = GPIO_Pin_Reset;
	}

	return bitStatus;
}

/*
 *  @brief	GPIO_LockPim, locks the pin of GPIOx Port
 *  @param	GPIOx = GPIO Port Base Address
 *
 *  @param	pinNumber = GPIO Pin Numbers 0 - 15
 *
 *  @retval None
 */
void GPIO_LockPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	uint32_t tempValue = (0x1U << 16U) | pinNumber;
	GPIOx->LCKR = tempValue;
	GPIOx->LCKR = pinNumber;
	GPIOx->LCKR = tempValue;
	tempValue = GPIOx->LCKR;
}

/*
 *  @brief	GPIO_TogglePin, toggles the pin of GPIOx Port
 *  @param	GPIOx = GPIO Port Base Address
 *
 *  @param	pinNumber = GPIO Pin Numbers 0 - 15
 *
 *  @retval None
 */
void GPIO_TogglePin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	uint16_t odr = (uint16_t)GPIOx->ODR;

	GPIOx->BSRR = (( odr & pinNumber ) << 16U )| (~odr & pinNumber);
}
