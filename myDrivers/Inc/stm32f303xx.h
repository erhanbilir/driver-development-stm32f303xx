/*
 * nucleof303xx.h
 *
 *  Created on: Sep 4, 2024
 *      Author: erhan
 */

#ifndef INC_STM32F303XX_H_
#define INC_STM32F303XX_H_

#include <stdint.h>
#include <string.h>

/*
 * Microprocessor Defines
 *
 */
#define NVIC_ISER0					((uint32_t*)(0xE000E100))

#define __IO volatile
#define SET_BIT(REG, BIT)			( (REG) |=  (BIT) )
#define CLEAR_BIT(REG, BIT)			( (REG) &= ~(BIT) )
#define READ_BIT(REG, BIT)			( (REG) &   (BIT) )
#define UNUSED(x)					( (void)x 		  )

typedef enum
{
	DISABLE = 0x0U,
	ENABLE = !DISABLE
}FunctionalState_t;

typedef enum
{
	FLAG_RESET = 0x0U,
	FLAG_SET = !FLAG_RESET
}FlagStatus_t;

/*
 * IRQ Numbers of MCU == Vector Table
 */
typedef enum
{
	EXTI0_IRQNumber = 6,
	EXTI1_IRQNumber = 7,
	EXTI2_IRQNumber = 8,
	EXTI3_IRQNumber = 9,
	EXTI15_10_IRQNumber = 40
}IRQNumber_TypeDef_t;

/*
 * Memory Base Address
 */
#define FLASH_BASE_ADDR				(0x08000000UL)	/* Flash Base Address (up to 512Kb) */
#define SRAM_BASE_ADDR				(0x20000000UL)	/* SRAM Base Address (up to 40Kb) */
#define CCM_SRAM_BASE_ADDR			(0x10000000UL)	/* CCM SRAM Base Address (up to 16Kb) */

/*
 * Peripheral Base Addresses
 */

#define PERIPH_BASE_ADDR			(0x40000000UL)						/* Base Address for All peripherals */

#define APB1_BASE_ADDR				PERIPH_BASE_ADDR					/* APB1 Bus Domain Base Address */
#define APB2_BASE_ADDR				(PERIPH_BASE_ADDR + 0x00010000UL)	/* APB2 Bus Domain Base Address */
#define AHB1_BASE_ADDR				(PERIPH_BASE_ADDR + 0x00020000UL)	/* AHB1 Bus Domain Base Address */
#define AHB2_BASE_ADDR				(PERIPH_BASE_ADDR + 0x08000000UL)	/* AHB2 Bus Domain Base Address */

/*
 * APB1 Peripheral Base Addresses
 */

#define TIM2_BASE_ADDR				(APB1_BASE_ADDR + 0x00000000UL)		/* Timer 2 Base Address */
#define TIM3_BASE_ADDR				(APB1_BASE_ADDR + 0x00000400UL)		/* Timer 3 Base Address */
#define TIM4_BASE_ADDR				(APB1_BASE_ADDR + 0x00000800UL)		/* Timer 4 Base Address */

#define SPI2_BASE_ADDR				(APB1_BASE_ADDR + 0x00003800UL)		/* SPI 2 Base Address */
#define SPI3_BASE_ADDR				(APB1_BASE_ADDR + 0x00003C00UL)		/* SPI 3 Base Address */

#define USART2_BASE_ADDR			(APB1_BASE_ADDR + 0x00004400UL)		/* USART 2 Base Address */
#define USART3_BASE_ADDR			(APB1_BASE_ADDR + 0x00004800UL)		/* USART 3 Base Address */

#define UART4_BASE_ADDR				(APB1_BASE_ADDR + 0x00004C00UL)		/* UART 4 Base Address */
#define UART5_BASE_ADDR				(APB1_BASE_ADDR + 0x00005000UL)		/* UART 5 Base Address */

#define I2C1_BASE_ADDR				(APB1_BASE_ADDR + 0x00005400UL)		/* I2C 1 Base Address */
#define I2C2_BASE_ADDR				(APB1_BASE_ADDR + 0x00005800UL)		/* I2C 2 Base Address */
#define I2C3_BASE_ADDR				(APB1_BASE_ADDR + 0x00007800UL)		/* I2C 3 Base Address */

/*
 * APB2 Peripheral Base Addresses
 */

#define SYSCFG_BASE_ADDR			(APB2_BASE_ADDR + 0x00000000UL)		/* SYSCFG Base Address */
#define EXTI_BASE_ADDR				(APB2_BASE_ADDR + 0x00000400UL)		/* EXTI Base Address */
#define TIM1_BASE_ADDR				(APB2_BASE_ADDR + 0x00002C00UL)		/* Timer 1 Base Address */
#define SPI1_BASE_ADDR				(APB2_BASE_ADDR + 0x00003000UL)		/* SPI 3 Base Address */
#define TIM8_BASE_ADDR				(APB2_BASE_ADDR + 0x00003400UL)		/* Timer 8 Base Address */
#define USART1_BASE_ADDR			(APB2_BASE_ADDR + 0x00003800UL)		/* USART 1 Base Address */
#define SPI4_BASE_ADDR				(APB2_BASE_ADDR + 0x00003C00UL)		/* SPI 4 Base Address */

/*
 * AHB1 Peripheral Base Addresses
 */

#define DMA1_BASE_ADDR				(AHB1_BASE_ADDR + 0x00000000UL)		/* DMA 1 Base Address */
#define DMA2_BASE_ADDR				(AHB1_BASE_ADDR + 0x00000400UL)		/* DMA 2 Base Address */

#define RCC_BASE_ADDR				(AHB1_BASE_ADDR + 0x00001000UL)		/* RCC Base Address */
#define CRC_BASE_ADDR				(AHB1_BASE_ADDR + 0x00003000UL)		/* CRC Base Address */
#define TSC_BASE_ADDR				(AHB1_BASE_ADDR + 0x00004000UL)		/* TSC Base Address */

/*
 * AHB2 Peripheral Base Addresses
 */

#define GPIOA_BASE_ADDR				(AHB2_BASE_ADDR + 0x00000000UL)		/* GPIOA Base Address */
#define GPIOB_BASE_ADDR				(AHB2_BASE_ADDR + 0x00000400UL)		/* GPIOB Base Address */
#define GPIOC_BASE_ADDR				(AHB2_BASE_ADDR + 0x00000800UL)		/* GPIOC Base Address */
#define GPIOD_BASE_ADDR				(AHB2_BASE_ADDR + 0x00000C00UL)		/* GPIOD Base Address */
#define GPIOE_BASE_ADDR				(AHB2_BASE_ADDR + 0x00001000UL)		/* GPIOE Base Address */
#define GPIOF_BASE_ADDR				(AHB2_BASE_ADDR + 0x00001400UL)		/* GPIOF Base Address */
#define GPIOG_BASE_ADDR				(AHB2_BASE_ADDR + 0x00001800UL)		/* GPIOG Base Address */
#define GPIOH_BASE_ADDR				(AHB2_BASE_ADDR + 0x00001C00UL)		/* GPIOH Base Address */

/*
 * Peripheral Structure Definitions
 */

typedef struct
{
	__IO uint32_t MODER;		/*!< GPIO port mode register  			   		Address offset = 0x00 */
	__IO uint32_t OTYPER;		/*!< GPIO port output type register 	   		Address offset = 0x04 */
	__IO uint32_t OSPEEDR;		/*!< GPIO port output speed register 	   		Address offset = 0x08 */
	__IO uint32_t PUPDR;		/*!< GPIO port pull-up/pull-down register  		Address offset = 0x0C */
	__IO uint32_t IDR;			/*!< GPIO port input data register		   		Address offset = 0x10 */
	__IO uint32_t ODR;			/*!< GPIO port output data register        		Address offset = 0x14 */
	__IO uint32_t BSRR;			/*!< GPIO port bit set/reset register     		Address offset = 0x18 */
	__IO uint32_t LCKR;			/*!< GPIO port configuration lock register 		Address offset = 0x1C */
	__IO uint32_t AFR[2];		/*!< GPIO alternate function low/high register  Address offset = 0x20 */
	__IO uint32_t BRR;			/*!< GPIO port bit reset register        		Address offset = 0x28 */
}GPIO_TypeDef_t;

typedef struct
{
	__IO uint32_t CR;			/*!< Clock control register 			   		Address offset = 0x00 */
	__IO uint32_t CFGR;			/*!< Clock configuration register  			   	Address offset = 0x04 */
	__IO uint32_t CIR;			/*!< Clock interrupt register 			   		Address offset = 0x08 */
	__IO uint32_t APB2RSTR;		/*!< APB2 peripheral reset register 			Address offset = 0x0C */
	__IO uint32_t APB1RSTR;		/*!< APB1 peripheral reset register 			Address offset = 0x10 */
	__IO uint32_t AHBENR;		/*!< AHB peripheral clock enable register  		Address offset = 0x14 */
	__IO uint32_t APB2ENR;		/*!< APB2 peripheral clock enable register   	Address offset = 0x18 */
	__IO uint32_t APB1ENR;		/*!< APB2 peripheral clock enable register   	Address offset = 0x1C */
	__IO uint32_t BDCR;			/*!< RTC domain control register  			   	Address offset = 0x20 */
	__IO uint32_t CSR;			/*!< Control/status register  			   		Address offset = 0x24 */
	__IO uint32_t AHBRSTR;		/*!< AHB peripheral reset register 			   	Address offset = 0x28 */
	__IO uint32_t CFGR2;		/*!< Clock configuration register 2  			Address offset = 0x2C */
	__IO uint32_t CFGR3;		/*!< Clock configuration register 3 			Address offset = 0x30 */

}RCC_TypeDef_t;

typedef struct
{
	__IO uint32_t CFGR1;		/*!< SYSCFG configuration register 1 						Address offset = 0x00 */
	__IO uint32_t RCR;			/*!< SYSCFG CCM SRAM protection register					Address offset = 0x04 */
	__IO uint32_t EXTICR[4]; 	/*!< SYSCFG external interrupt configuration register  		Address offset = 0x08 */
	__IO uint32_t CFGR2;		/*!< SYSCFG configuration register 2 						Address offset = 0x18 */
	__IO uint32_t CFGR3;		/*!< SYSCFG configuration register 3 						Address offset = 0x50 */
	__IO uint32_t CFGR4;		/*!< SYSCFG configuration register 4 						Address offset = 0x48 */
}SYSCFG_TypeDef_t;

typedef struct
{
	__IO uint32_t IMR1;			/*!< Interrupt mask register				Address offset = 0x00 */
	__IO uint32_t EMR1;			/*!< Event mask register					Address offset = 0x04 */
	__IO uint32_t RTSR1;		/*!< Rising trigger selection register		Address offset = 0x08 */
	__IO uint32_t FTSR1;		/*!< Falling trigger selection register		Address offset = 0x0C */
	__IO uint32_t SWIER1;		/*!< Software interrupt event register		Address offset = 0x10 */
	__IO uint32_t PR1;			/*!< Pending register						Address offset = 0x14 */
	__IO uint32_t IMR2;			/*!< Interrupt mask register				Address offset = 0x20 */
	__IO uint32_t EMR2;			/*!< Event mask register					Address offset = 0x24 */
	__IO uint32_t RTSR2;		/*!< Rising trigger selection register		Address offset = 0x28 */
	__IO uint32_t FTSR2;		/*!< Falling trigger selection register		Address offset = 0x2C */
	__IO uint32_t SWIER2;		/*!< Software interrupt event register		Address offset = 0x30 */
	__IO uint32_t PR2;			/*!< Pending register						Address offset = 0x34 */
}EXTI_TypeDef_t;

typedef struct
{
	__IO uint32_t CR1;			/*!< SPI control register 1 				Address offset = 0x00 */
	__IO uint32_t CR2;			/*!< SPI control register 2 				Address offset = 0x04 */
	__IO uint32_t SR;			/*!< SPI status register 	 				Address offset = 0x08 */
	__IO uint32_t DR;			/*!< SPI data register 						Address offset = 0x0C */
	__IO uint32_t CRCPR;		/*!< SPI CRC polynomial register			Address offset = 0x10 */
	__IO uint32_t RXCRCR;		/*!< SPI RX CRC register					Address offset = 0x14 */
	__IO uint32_t TXCRCR;		/*!< SPI TX CRC register					Address offset = 0x18 */
	__IO uint32_t I2SCFGR;		/*!< SPIx_I2S configuration register 		Address offset = 0x1C */
	__IO uint32_t I2SPR;		/*!< SPIx_I2S prescaler register 			Address offset = 0x20 */
}SPI_TypeDef_t;

typedef struct
{
	__IO uint32_t CR1;			/*!< USART control register 1					Address offset = 0x00 */
	__IO uint32_t CR2;			/*!< USART control register 2					Address offset = 0x04 */
	__IO uint32_t CR3;			/*!< USART control register 3					Address offset = 0x08 */
	__IO uint32_t BRR;			/*!< USART baud rate register					Address offset = 0x0C */
	__IO uint32_t GTPR;			/*!< USART guard time and prescaler register	Address offset = 0x10 */
	__IO uint32_t RTOR;			/*!< USART receiver timeout register			Address offset = 0x14 */
	__IO uint32_t RQR;			/*!< USART request register						Address offset = 0x18 */
	__IO uint32_t ISR;			/*!< USART interrupt and status register		Address offset = 0x1C */
	__IO uint32_t ICR;			/*!< USART interrupt flag clear register		Address offset = 0x20 */
	__IO uint32_t RDR;			/*!< USART receive data register				Address offset = 0x24 */
	__IO uint32_t TDR;			/*!< USART transmit data register				Address offset = 0x28 */
}USART_TypeDef_t;

/* Bases address definitions of ports */

#define GPIOA						( (GPIO_TypeDef_t *)  (GPIOA_BASE_ADDR) )
#define GPIOB						( (GPIO_TypeDef_t *)  (GPIOB_BASE_ADDR) )
#define GPIOC						( (GPIO_TypeDef_t *)  (GPIOC_BASE_ADDR) )
#define GPIOD						( (GPIO_TypeDef_t *)  (GPIOD_BASE_ADDR) )
#define GPIOE						( (GP O_TypeDef_t *)  (GPIOE_BASE_ADDR) )
#define GPIOF						( (GPIO_TypeDef_t *)  (GPIOF_BASE_ADDR) )
#define GPIOG						( (GPIO_TypeDef_t *)  (GPIOG_BASE_ADDR) )
#define GPIOH						( (GPIO_TypeDef_t *)  (GPIOH_BASE_ADDR) )

#define RCC							( (RCC_TypeDef_t *)   (RCC_BASE_ADDR)	)

#define SYSCFG						( (SYSCFG_TypeDef_t *)(SYSCFG_BASE_ADDR))

#define EXTI						( (EXTI_TypeDef_t *)(EXTI_BASE_ADDR)	)

#define SPI1						( (SPI_TypeDef_t *)	   (SPI1_BASE_ADDR) )
#define SPI2						( (SPI_TypeDef_t *)    (SPI2_BASE_ADDR) )
#define SPI3						( (SPI_TypeDef_t *)	   (SPI3_BASE_ADDR) )
#define SPI4						( (SPI_TypeDef_t *)	   (SPI4_BASE_ADDR) )

#define USART1						( (USART_TypeDef_t *)  (USART1_BASE_ADDR))
#define USART2						( (USART_TypeDef_t *)  (USART2_BASE_ADDR))
#define USART3						( (USART_TypeDef_t *)  (USART3_BASE_ADDR))

#define UART4						( (USART_TypeDef_t *)  (UART4_BASE_ADDR))
#define UART5						( (USART_TypeDef_t *)  (UART5_BASE_ADDR))

/*
 * SPI Flag Definitions
 */
#define SPI_CR1_SPE					(6U)

#define SPI_SR_TXE					(1U)
#define SPI_SR_BSY					(7U)

#define SPI_TXE_FLAG				(0x1U << SPI_SR_TXE)
#define SPI_BSY_FLAG				(0x1U << SPI_SR_BSY)

/*
 * UART/USART Bit Definitions
 */
#define USART_CR1_ENABLE			(0U)
#define USART_CR2_STOP 				(12U)

#define USART_ISR_TXE				(7U)
#define USART_ISR_TC				(6U)

#define USART_TXE_FLAG				(0x1U << USART_ISR_TXE)
#define USART_TC_FLAG				(0x1U << USART_ISR_TC)

/*
 * Bit Definitions
 */

#define RCC_AHBENR_GPIOAEN_Pos		(0x11U)										/* RCC AHBENR register GPIOAEN Bit Position */
#define RCC_AHBENR_GPIOAEN_Mask		(0x1 << RCC_AHBENR_GPIOAEN_Pos)				/* RCC AHBENR register GPIOAEN Bit Mask */
#define RCC_AHBENR_GPIOAEN			RCC_AHBENR_GPIOAEN_Mask						/* RCC AHBENR register GPIOAEN macro */

#define RCC_AHBENR_GPIOBEN_Pos		(0x12U)										/* RCC AHBENR register GPIOBEN Bit Position */
#define RCC_AHBENR_GPIOBEN_Mask		(0x1 << RCC_AHBENR_GPIOBEN_Pos)				/* RCC AHBENR register GPIOBEN Bit Mask */
#define RCC_AHBENR_GPIOBEN			RCC_AHBENR_GPIOBEN_Mask						/* RCC AHBENR register GPIOBEN macro */

#define RCC_AHBENR_GPIOCEN_Pos		(0x13U)										/* RCC AHBENR register GPIOCEN Bit Position */
#define RCC_AHBENR_GPIOCEN_Mask		(0x1 << RCC_AHBENR_GPIOCEN_Pos)				/* RCC AHBENR register GPIOCEN Bit Mask */
#define RCC_AHBENR_GPIOCEN			RCC_AHBENR_GPIOCEN_Mask						/* RCC AHBENR register GPIOCEN macro */

#define RCC_AHBENR_GPIODEN_Pos		(0x14U)										/* RCC AHBENR register GPIODEN Bit Position */
#define RCC_AHBENR_GPIODEN_Mask		(0x1 << RCC_AHBENR_GPIODEN_Pos)				/* RCC AHBENR register GPIODEN Bit Mask */
#define RCC_AHBENR_GPIODEN			RCC_AHBENR_GPIODEN_Mask						/* RCC AHBENR register GPIODEN macro */

#define RCC_AHBENR_GPIOFEN_Pos		(0x16U)										/* RCC AHBENR register GPIOFEN Bit Position */
#define RCC_AHBENR_GPIOFEN_Mask		(0x1 << RCC_AHBENR_GPIOFEN_Pos)				/* RCC AHBENR register GPIOFEN Bit Mask */
#define RCC_AHBENR_GPIOFEN			RCC_AHBENR_GPIOFEN_Mask						/* RCC AHBENR register GPIOFEN macro */

#define RCC_AHBENR_GPIOGEN_Pos		(0x17U)										/* RCC AHBENR register GPIOGEN Bit Position */
#define RCC_AHBENR_GPIOGEN_Mask		(0x1 << RCC_AHBENR_GPIOGEN_Pos)				/* RCC AHBENR register GPIOEN Bit Mask */
#define RCC_AHBENR_GPIOGEN			RCC_AHBENR_GPIOGEN_Mask						/* RCC AHBENR register GPIOGAEN macro */

#define RCC_AHBENR_GPIOHEN_Pos		(0x10U)										/* RCC AHBENR register GPIOHEN Bit Position */
#define RCC_AHBENR_GPIOHEN_Mask		(0x1 << RCC_AHBENR_GPIOHEN_Pos)				/* RCC AHBENR register GPIOHEN Bit Mask */
#define RCC_AHBENR_GPIOHEN			RCC_AHBENR_GPIOHEN_Mask						/* RCC AHBENR register GPIOHEN macro */


#define RCC_APB2ENR_SYSCFG_Pos		(0x0U)										/* RCC APB2ENR register SYSCFG Bit Position */
#define RCC_APB2ENR_SYSCFG_Mask		(0x1 << RCC_APB2ENR_SYSCFG_Pos)				/* RCC APB2ENR register SYSCFG Bit Mask */
#define RCC_ABP2ENR_SYSCFG			RCC_APB2ENR_SYSCFG_Mask						/* RCC APB2ENR register SYSCFG Macro */

#define RCC_APB2ENR_SPI1EN_Pos		(0x0CU)										/* RCC APB2ENR register SPI1EN Bit Position */
#define RCC_APB2ENR_SPI1EN_Mask		(0x1 << RCC_APB2ENR_SPI1EN_Pos)				/* RCC APB2ENR register SPI1EN Bit Mask */
#define RCC_APB2ENR_SPI1EN			RCC_APB2ENR_SPI1EN_Mask						/* RCC APB2ENR register SPI1EN Macro */

#define RCC_APB2ENR_SPI4EN_Pos		(0x0FU)										/* RCC APB2ENR register SPI4EN Bit Position */
#define RCC_APB2ENR_SPI4EN_Mask		(0x1 << RCC_APB2ENR_SPI4EN_Pos)				/* RCC APB2ENR register SPI4EN Bit Mask */
#define RCC_APB2ENR_SPI4EN			RCC_APB2ENR_SPI4EN_Mask						/* RCC APB2ENR register SPI4EN Macro */

#define RCC_APB1ENR_SPI2EN_Pos		(0x0EU)										/* RCC APB1ENR register SPI2EN Bit Position */
#define RCC_APB1ENR_SPI2EN_Mask		(0x1 << RCC_APB1ENR_SPI2EN_Pos)				/* RCC APB1ENR register SPI2EN Bit Mask */
#define RCC_APB1ENR_SPI2EN			RCC_APB1ENR_SPI2EN_Mask						/* RCC APB1ENR register SPI2EN Macro */

#define RCC_APB1ENR_SPI3EN_Pos		(0x0FU)										/* RCC APB1ENR register SPI3EN Bit Position */
#define RCC_APB1ENR_SPI3EN_Mask		(0x1 << RCC_APB1ENR_SPI3EN_Pos)				/* RCC APB1ENR register SPI3EN Bit Mask */
#define RCC_APB1ENR_SPI3EN			RCC_APB1ENR_SPI3EN_Mask						/* RCC APB1ENR register SPI3EN Macro */

#define RCC_APB2ENR_USART1EN_Pos	(0x0EU)										/* RCC APB2ENR register USART1EN Bit Position */
#define RCC_APB2ENR_USART1EN_Mask	(0x1 << RCC_APB2ENR_USART1EN_Pos)			/* RCC APB2ENR register USART1EN Bit Mask */
#define RCC_APB2ENR_USART1EN		RCC_APB2ENR_USART1EN_Mask					/* RCC APB2ENR register USART1EN Macro */

#define RCC_APB1ENR_USART2EN_Pos	(0x11U)										/* RCC APB1ENR register USART2EN Bit Position */
#define RCC_APB1ENR_USART2EN_Mask	(0x1 << RCC_APB1ENR_USART2EN_Pos)			/* RCC APB1ENR register USART2EN Bit Mask */
#define RCC_APB1ENR_USART2EN		RCC_APB1ENR_USART2EN_Mask					/* RCC APB1ENR register USART2EN Macro */

#define RCC_APB1ENR_USART3EN_Pos	(0x12U)										/* RCC APB1ENR register USART3EN Bit Position */
#define RCC_APB1ENR_USART3EN_Mask	(0x1 << RCC_APB1ENR_USART3EN_Pos)			/* RCC APB1ENR register USART3EN Bit Mask */
#define RCC_APB1ENR_USART3EN		RCC_APB1ENR_USART3EN_Mask					/* RCC APB1ENR register USART3EN Macro */

#define RCC_APB1ENR_UART4EN_Pos		(0x13U)										/* RCC APB1ENR register UART4EN Bit Position */
#define RCC_APB1ENR_UART4EN_Mask	(0x1 << RCC_APB1ENR_UART4EN_Pos)			/* RCC APB1ENR register UART4EN Bit Mask */
#define RCC_APB1ENR_UART4EN			RCC_APB1ENR_UART4EN_Mask					/* RCC APB1ENR register UART4EN Macro */

#define RCC_APB1ENR_UART5EN_Pos		(0x14U)										/* RCC APB1ENR register UART5EN Bit Position */
#define RCC_APB1ENR_UART5EN_Mask	(0x1 << RCC_APB1ENR_UART5EN_Pos)			/* RCC APB1ENR register UART5EN Bit Mask */
#define RCC_APB1ENR_UART5EN			RCC_APB1ENR_UART5EN_Mask					/* RCC APB1ENR register UART5EN Macro */

#include "RCC.h"
#include "GPIO.h"
#include "EXTI.h"
#include "SPI.h"
#include "USART.h"

#endif /* INC_STM32F303XX_H_ */
