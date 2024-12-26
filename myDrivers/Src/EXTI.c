/*
 * EXTI.c
 *
 *  Created on: Sep 10, 2024
 *      Author: erhan
 */
#include "EXTI.h"


/**
  * @brief  EXTI_LineConfig, configures the port and pin for SYSCFG
  *
  * @param  PortSource = Port Value A - G @def_group EXTI_PORT_Values
  * @param  EXTI_LineSource = Pin Numbers & Line Numbers @def_group EXTI_LINE_Values
  *
  * @retval None
  */
void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource)
{
	uint32_t tempValue;

	tempValue = SYSCFG->EXTICR[EXTI_LineSource >> 2U]; 		//Register'ı bulma
	tempValue &= ~(0xFU << (EXTI_LineSource & 0x3U) * 4);	//Registerdaki bitleri sıfırlama
	tempValue = (PortSource << (EXTI_LineSource & 0x3U) * 4);
	SYSCFG->EXTICR[EXTI_LineSource >> 2U] = tempValue;
}

/**
  * @brief  EXTI_Init for valit GPIO port and Line number
  *
  * @param  EXTI_InitStruct = User Config structure
  *
  * @retval None
  */
void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStruct)
{
	uint32_t tempValue = 0;
	tempValue = (uint32_t)EXTI_BASE_ADDR;

	EXTI->IMR1 &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	EXTI->EMR1 &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);

	if(EXTI_InitStruct->EXTI_LineCmd != DISABLE)
	{
		tempValue += EXTI_InitStruct->EXTI_Mode;

		*((__IO uint32_t*)tempValue ) |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);

		tempValue = (uint32_t)EXTI_BASE_ADDR;

		EXTI->RTSR1 &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
		EXTI->FTSR1 &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);

		if(EXTI_InitStruct->TriggerSelection == EXTI_Trigger_RF)
		{
			EXTI->RTSR1 |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
			EXTI->FTSR1 |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}
		else
		{
			tempValue += EXTI_InitStruct->TriggerSelection;
			*((__IO uint32_t*)tempValue) |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}
	}
	else
	{
		tempValue += EXTI_InitStruct->EXTI_Mode;
		*((__IO uint32_t*)tempValue ) &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	}
}

/**
  * @brief  NVIC_EnableInterrupt
  *
  * @param  IRQNumber = IRQ Number of line
  *
  * @retval None
  */
void NVIC_EnableInterrupt(IRQNumber_TypeDef_t IRQNumber)
{
	uint32_t tempValue = 0;

	tempValue = *( (IRQNumber >> 5U ) + NVIC_ISER0 );
	tempValue &= ~(0x1U << (IRQNumber & 0x1FU) );
	tempValue |=  (0x1U << (IRQNumber & 0x1FU) );
	*( (IRQNumber >> 5U ) + NVIC_ISER0 ) = tempValue;
}
