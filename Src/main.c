/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stm32f303xx.h>

static void GPIO_LedConfig();
static void GPIO_ButtonConfig();
//static void GPIO_LockControl();
static void GPIO_ButtonInterruptConfig();
static void SPI_Config();
static void SPI_GPIO_Config();

SPI_HandleTypeDef_t SPI_HandleStructure;
USART_HandleTypeDef_t USART_Handle;

void EXTI15_10_IRQHandler()
{
	char msgToSend[] = "Hello World!\n";
	if(EXTI->PR1 & (0x1 << 0xDU))
	{
		EXTI->PR1 |= (0x0U << 0xDU);
		SPI_TransmitData(&SPI_HandleStructure, (uint8_t*)msgToSend, strlen(msgToSend));
	}

	//GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

int main(void)
{
	GPIO_LedConfig();
	//GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_Pin_Reset);

	GPIO_ButtonConfig();
	//GPIO_LockPin(GPIOC, GPIO_PIN_13);
	//GPIO_LockControl();
	GPIO_ButtonInterruptConfig();

	SPI_GPIO_Config();

	SPI_Config();

	USART_Handle.Instance = USART2;
	USART_Handle.Init.BaudRate = 115200;

//	while(1)
//	{
//		if(GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_Pin_Reset)
//		{
//
//			while(GPIO_ReadPin(GPIOC, GPIO_PIN_13) != GPIO_Pin_Set);
//		}
//	}
	for(;;);
}

static void GPIO_LedConfig()
{
	RCC_GPIOA_CLK_EN();

	GPIO_InitTypeDef_t GPIO_Config = {0};
	GPIO_Config.Pin = GPIO_PIN_5;
	GPIO_Config.Mode = GPIO_MODE_OUTPUT;
	GPIO_Config.Speed = GPIO_OSPEED_LOW;
	GPIO_Config.Otype = GPIO_OTYPE_PP;
	GPIO_Config.PuPd = GPIO_PUPD_NOPULL;

	GPIO_Init(GPIOA, &GPIO_Config);
	memset(&GPIO_Config, 0, sizeof(GPIO_Config));


	EXTI_LineConfig(EXTI_PortSource_GPIOC, EXTI_LineSource_13);
}

static void GPIO_ButtonConfig()
{
	RCC_GPIOC_CLK_EN();

	GPIO_InitTypeDef_t GPIO_Config = {0};
	GPIO_Config.Pin = GPIO_PIN_13;
	GPIO_Config.Mode = GPIO_MODE_INPUT;
	GPIO_Config.PuPd = GPIO_PUPD_PULLUP;

	GPIO_Init(GPIOC, &GPIO_Config);
	memset(&GPIO_Config, 0, sizeof(GPIO_Config));
}

/*static void GPIO_LockControl()
{
	GPIO_InitTypeDef_t GPIO_Config = {0};
	GPIO_Config.Pin = GPIO_PIN_13;
	GPIO_Config.Mode = GPIO_MODE_OUTPUT;
	GPIO_Config.PuPd = GPIO_PUPD_NOPULL;

	GPIO_Init(GPIOC, &GPIO_Config);
	memset(&GPIO_Config, 0, sizeof(GPIO_Config));
}*/

static void GPIO_ButtonInterruptConfig()
{
	//RCC_GPIOA_CLK_EN();
	RCC_SYSCFG_CLK_EN();
	EXTI_InitTypeDef_t EXTI_InitStruct = {0};

	EXTI_LineConfig(EXTI_PortSource_GPIOC, EXTI_LineSource_13);

	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_LineNumber = EXTI_LineSource_13;
	EXTI_InitStruct.EXTI_Mode = EXTI_MODE_Interrupt;
	EXTI_InitStruct.TriggerSelection = EXTI_Trigger_Falling;

	EXTI_Init(&EXTI_InitStruct);

	NVIC_EnableInterrupt(EXTI15_10_IRQNumber);
}

static void SPI_Config()
{
	RCC_SPI1_CLK_EN();
	SPI_HandleStructure.Instance = SPI1; /* Tek tek registerları eşitlemektense böyle verilebilir */
	SPI_HandleStructure.Init.BaudRate = SPI_BAUDRATE_DIV8;
	SPI_HandleStructure.Init.BusConfig = SPI_BUS_FullDuplex;
	SPI_HandleStructure.Init.CPHA = SPI_CPHA_FIRST;
	SPI_HandleStructure.Init.CPOL = SPI_CPOL_LOW;
	SPI_HandleStructure.Init.FrameFormat = SPI_FRAMEFORMAT_MSB;
	SPI_HandleStructure.Init.Mode = SPI_MODE_MASTER;
	SPI_HandleStructure.Init.SSM_Cmd = SPI_SSM_ENABLE;

	SPI_PeriphCmd(&SPI_HandleStructure, ENABLE);

	SPI_Init(&SPI_HandleStructure);

}

static void SPI_GPIO_Config()
{
	RCC_GPIOA_CLK_EN();
	GPIO_InitTypeDef_t GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;
	GPIO_InitStruct.Speed = GPIO_OSPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
