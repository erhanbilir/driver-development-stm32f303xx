#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "stm32f303xx.h"

/*
 * @def_group I2C_ClockSpeeds
 *
 */
#define I2C_SPEED_STANDART	(100000U)
#define I2C_SPEED_FAST		(400000U)

/*
 * @def_group I2C_ACK_State
 *
 */

/*
 * @def_group I2C_Strech_State
 *
 */
#define I2C_STRETCH_ENABLE		(0x00000000U)
#define I2C_STRETCH_DISABLE		(0x00020000U)

typedef struct
{
	uint32_t ClockSpeed;		/*!< I2C Clock Speed Choice @def_group I2C_ClockSpeeds */
	//uint32_t ACK_State:  	   	/*!< I2C ACK State Choice @def_group I2C_ACK_State 	*/
	uint32_t ClockStretch;		/*!< I2C Stretch State Choice @def_group I2C_Strech_State */

}I2C_InitTypeDef_t;

typedef struct
{
	I2C_TypeDef_t *Instance;
	I2C_InitTypeDef_t Init;

}I2C_HandleTypeDef_t;

void I2C_PeriphCmd(I2C_TypeDef_t *I2Cx, FunctionalState_t stateOfI2C);

#endif /* INC_I2C_H_ */
