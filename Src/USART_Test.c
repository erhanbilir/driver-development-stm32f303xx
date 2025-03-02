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

void USART3_EXTI28_IRQHandler()
{
	USART_InterruptHandler(&USART_Handle);
}

int main(void)
{
	char msgToSend[] = "Hey bro how are you?\n\r";

	GPIO_Config();
	UART_Config();

	USART_TransmitData_IT(&USART_Handle, (uint8_t*)msgToSend, strlen(msgToSend));

	//USART_ReceiveData(&USART_Handle, (uint8_t*)msgToSend, 12);
	//USART_TransmitData(&USART_Handle, (uint8_t*)msgToSend, strlen(msgToSend));

	while(1);
}

static void UART_Config(void)
{
	RCC_USART3_CLK_EN();

	USART_Handle.Instance = USART3;
	USART_Handle.Init.BaudRate = 115200;
	USART_Handle.Init.HardwareFlowControl = USART_HW_NONE;
	USART_Handle.Init.Mode = USART_MODE_TX_RX;
	USART_Handle.Init.OverSampling = USART_OVERSAMPLE_16;
	USART_Handle.Init.Parity = USART_PARITY_NONE;
	USART_Handle.Init.StopBits = USART_STOPBITS_1;
	USART_Handle.Init.WordLength = USART_WORDLENGTH_8Bits;

	USART_Init(&USART_Handle);
	NVIC_EnableInterrupt(USART3_IRQNumber);
	USART_PeriphCmd(&USART_Handle, ENABLE);
}

static void GPIO_Config(void)
{
	GPIO_InitTypeDef_t GPIO_InitStructB = {0};

	RCC_GPIOB_CLK_EN();

	GPIO_InitStructB.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	GPIO_InitStructB.Mode = GPIO_MODE_AF;
	GPIO_InitStructB.Otype = GPIO_OTYPE_PP;
	GPIO_InitStructB.PuPd = GPIO_PUPD_NOPULL;
	GPIO_InitStructB.Speed = GPIO_OSPEED_HIGH;
	GPIO_InitStructB.Alternate = GPIO_AF7;

	GPIO_Init(GPIOB, &GPIO_InitStructB);
}
