#include "I2C.h"

/*
 *  @brief	I2C_PeriphCmd, enable or disable I2C peripheral
 *
 *  @param	I2Cx = I2C Peripheral
 *
 *	@param  stateOfI2C = ENABLE or DISABLE
 *
 *  @retval None
 */
void I2C_PeriphCmd(I2C_TypeDef_t *I2Cx, FunctionalState_t stateOfI2C)
{
	if(stateOfI2C == ENABLE)
	{
		I2Cx->CR1 |= (0x1U << I2C_CR1_ENABLE);
	}
	else
	{
		I2Cx->CR1 &= ~(0x1U << I2C_CR1_ENABLE);
	}
}
