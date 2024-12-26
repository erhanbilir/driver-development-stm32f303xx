/*
 * GPIO.h
 *
 *  Created on: Sep 5, 2024
 *      Author: erhan
 */
#ifndef INC_GPIO_H
#define INC_GPIO_H

#include <stm32f303xx.h>

/*
 * @def_group	GPIO_Pin_Modes
 */
#define GPIO_MODE_INPUT				(0x0U)
#define GPIO_MODE_OUTPUT			(0x1U)
#define GPIO_MODE_AF				(0x2U)
#define GPIO_MODE_ANALOG			(0x3U)

/*
 * @def_group	GPIO_OTYPE_Modes
 */
#define GPIO_OTYPE_PP				(0x0U)
#define GPIO_OTYPE_OD				(0x1U)

/*
 * @def_group	GPIO_OSPEED_Modes
 */
#define GPIO_OSPEED_LOW				(0x0U)
#define GPIO_OSPEED_MED				(0x1U)
#define GPIO_OSPEED_HIGH			(0x3U)

/*
 * @def_group	GPIO_PUPD_Modes
 */
#define GPIO_PUPD_NOPULL			(0x0U)
#define GPIO_PUPD_PULLUP			(0x1U)
#define GPIO_PUPD_PULLDOWN			(0x2U)

/*
 * @def_group GPIO_AF_Modes
 */
#define GPIO_AF0					(0x0U)
#define GPIO_AF1					(0x1U)
#define GPIO_AF2					(0x2U)
#define GPIO_AF3					(0x3U)
#define GPIO_AF4					(0x4U)
#define GPIO_AF5					(0x5U)
#define GPIO_AF6					(0x6U)
#define GPIO_AF7					(0x7U)
#define GPIO_AF8					(0x8U)
#define GPIO_AF9					(0x9U)
#define GPIO_AF10					(0xAU)
#define GPIO_AF11					(0xBU)
#define GPIO_AF12					(0xCU)
#define GPIO_AF13					(0xDU)
#define GPIO_AF14					(0xEU)
#define GPIO_AF15					(0xFU)


/*
 * @def_group GPIO_Pins
 */
#define GPIO_PIN_0			(uint16_t)(0x0001) 		/*!< GPIO Pin 0 Selected*/
#define GPIO_PIN_1			(uint16_t)(0x0002) 		/*!< GPIO Pin 1 Selected*/
#define GPIO_PIN_2			(uint16_t)(0x0004) 		/*!< GPIO Pin 2 Selected*/
#define GPIO_PIN_3			(uint16_t)(0x0008) 		/*!< GPIO Pin 3 Selected*/
#define GPIO_PIN_4			(uint16_t)(0x0010) 		/*!< GPIO Pin 4 Selected*/
#define GPIO_PIN_5			(uint16_t)(0x0020) 		/*!< GPIO Pin 5 Selected*/
#define GPIO_PIN_6			(uint16_t)(0x0040) 		/*!< GPIO Pin 6 Selected*/
#define GPIO_PIN_7			(uint16_t)(0x0080) 		/*!< GPIO Pin 7 Selected*/
#define GPIO_PIN_8			(uint16_t)(0x0100) 		/*!< GPIO Pin 8 Selected*/
#define GPIO_PIN_9			(uint16_t)(0x0200) 		/*!< GPIO Pin 9 Selected*/
#define GPIO_PIN_10			(uint16_t)(0x0400) 		/*!< GPIO Pin 10 Selected*/
#define GPIO_PIN_11			(uint16_t)(0x0800) 		/*!< GPIO Pin 11 Selected*/
#define GPIO_PIN_12			(uint16_t)(0x1000) 		/*!< GPIO Pin 12 Selected*/
#define GPIO_PIN_13			(uint16_t)(0x2000) 		/*!< GPIO Pin 13 Selected*/
#define GPIO_PIN_14			(uint16_t)(0x4000) 		/*!< GPIO Pin 14 Selected*/
#define GPIO_PIN_15		 	(uint16_t)(0x8000)		/*!< GPIO Pin 15 Selected*/
#define GPIO_PIN_ALL		(uint16_t)(0xFFFF)		/*!< GPIO All Pin Selected*/

#define GPIO_MAX_PIN_POSITION 16U

typedef enum
{
	GPIO_Pin_Reset = 0x0U,
	GPIO_Pin_Set = !GPIO_Pin_Reset
}GPIO_PinState_t;

typedef struct
{
	uint32_t Pin;		/* GPIO Pin Numbers		@def_group GPIO_Pins*/
	uint32_t Mode;		/* GPIO Pin Modes		@def_group GPIO_PinModes*/
	uint32_t Otype;		/* GPIO OType Modes 	@def_group GPIO_OTYPE_Modes */
	uint32_t Speed;		/* GPIO OSpeed Modes 	@def_group GPIO_OSPEED_Modes*/
	uint32_t PuPd;		/* GPIO PuPd Modes 		@def_group GPIO_PUPD_Modes*/
	uint32_t Alternate; /* GPIO Pin Numbers		@def_group GPIO_AF_Modes*/
}GPIO_InitTypeDef_t;

void GPIO_Init(GPIO_TypeDef_t *GPIOx, GPIO_InitTypeDef_t *GPIOInitData);

void GPIO_WritePin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber, GPIO_PinState_t pinState);

void GPIO_LockPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber);

void GPIO_TogglePin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber);

uint16_t GPIO_PinGetPosition(uint16_t pinNumber);

GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber);

#endif /* INC_GPIO_H */
