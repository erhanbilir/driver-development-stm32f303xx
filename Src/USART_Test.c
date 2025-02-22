/*
 * USART_Test.c
 *
 *  Created on: Feb 1, 2025
 *      Author: erhan
 */
#include "stm32f303xx.h"

USART_HandleTypeDef_t USART_Handle;

static void GPIO_Config();
static void UART_Config(void);

int main(void)
{
	char msg[] = "Hello World!\n\r";

	GPIO_Config();
	UART_Config();

	USART_TransmitData(&USART_Handle, (uint8_t*)msg, strlen(msg));
	while(1);
}

static void UART_Config(void)
{
	RCC_USART2_CLK_EN();

	USART_Handle.Instance = USART2;
	USART_Handle.Init.BaudRate = 9600;
	USART_Handle.Init.HardwareFlowControl = USART_HW_NONE;
	USART_Handle.Init.Mode = USART_MODE_TX;
	USART_Handle.Init.OverSampling = USART_OVERSAMPLE_16;
	USART_Handle.Init.Parity = USART_PARITY_NONE;
	USART_Handle.Init.StopBits = USART_STOPBITS_1;
	USART_Handle.Init.WordLength = USART_WORDLENGTH_8Bits;

	USART_Init(&USART_Handle);
	USART_PeriphCmd(&USART_Handle, ENABLE);
}

static void GPIO_Config(void)
{
	GPIO_InitTypeDef_t GPIO_InitStruct = {0};

	RCC_GPIOA_CLK_EN();

	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;
	GPIO_InitStruct.Speed = GPIO_OSPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
