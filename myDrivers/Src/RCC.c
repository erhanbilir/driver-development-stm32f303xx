/*
 * RCC.c
 *
 *  Created on: Sep 5, 2024
 *      Author: erhan
 */
#include "RCC.h"

const uint8_t AHB_Prescalers[] = { 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APB_Prescalers[] = { 0, 0 ,0 , 1, 2, 3, 4};

uint32_t RCC_GetSystemClock(void)
{
	uint32_t SystemCoreClock = 0;
	uint8_t clkSource = 0;

	clkSource = ( (RCC->CFGR >> 2U) & 0x3U );

	switch(clkSource)
	{
		case 0 : SystemCoreClock = 8000000; break; // HSI
		case 1 : SystemCoreClock = 32000000; break;  // HSE

		default : SystemCoreClock = 8000000;
	}

	return SystemCoreClock;
}

uint32_t RCC_GetHClock(void)
{
	uint32_t AHB_PeriphClock = 0;
	uint32_t SystemCoreClock = 0;
	uint8_t HPRE_Value = 0;
	uint8_t tempValue = 0;

	SystemCoreClock = RCC_GetSystemClock();

	HPRE_Value = ( (RCC->CFGR >> 4U) & 0xFU );
	tempValue = AHB_Prescalers[HPRE_Value];

	AHB_PeriphClock = SystemCoreClock >> tempValue;

	return AHB_PeriphClock;
}

uint32_t RCC_GetP1Clock(void)
{
	uint32_t APB1_PeriphClock = 0;
	uint32_t AHB_PeriphClock = 0;
	uint8_t PPRE1_Value = 0;
	uint8_t tempValue = 0;

	AHB_PeriphClock = RCC_GetHClock();

	PPRE1_Value = ( (RCC->CFGR >> 8U) & 0x7U );
	tempValue = APB_Prescalers[PPRE1_Value];

	APB1_PeriphClock = AHB_PeriphClock >> tempValue;

	return APB1_PeriphClock;
}

uint32_t RCC_GetP2Clock(void)
{
	uint32_t APB2_PeriphClock = 0;
	uint32_t AHB_PeriphClock = 0;
	uint8_t PPRE2_Value = 0;
	uint8_t tempValue = 0;

	AHB_PeriphClock = RCC_GetHClock();

	PPRE2_Value = ( (RCC->CFGR >> 11U) & 0x7U);
	tempValue = APB_Prescalers[PPRE2_Value];

	APB2_PeriphClock = AHB_PeriphClock >> tempValue;

	return APB2_PeriphClock;
}
