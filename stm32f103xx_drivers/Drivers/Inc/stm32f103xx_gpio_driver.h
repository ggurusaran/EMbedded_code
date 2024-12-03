/*
 * stm32f103xx_gpio_driver.h
 *  Created on: Nov 21, 2024
 *      Author: gurus
 */

#ifndef INC_STM32F103XX_GPIO_DRIVER_H_
#define INC_STM32F103XX_GPIO_DRIVER_H_

#include<stdint.h>
#include"stm32f103xx.h"

#endif /* INC_STM32F103XX_GPIO_DRIVER_H_ */

typedef struct
{
	uint8_t GPIO_PinNumber; //pin no. and mode, etc..for all 1 byte is enough, so uint8
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinCnf;

}GPIO_Pinconfig_t;
/*
 * GPIO Handle structure
 */
typedef struct
{
	GPIO_Regdef_t *pGPIOx;//holds the base address of gpio port to which the pin belongs
	GPIO_Pinconfig_t GPIO_PinConfig;//pin configuration structure

}GPIO_Handle_t;

#define GPIO_PIN_0   0
#define GPIO_PIN_1   1
#define GPIO_PIN_2   2
#define GPIO_PIN_3   3
#define GPIO_PIN_4   4
#define GPIO_PIN_5   5
#define GPIO_PIN_6   6
#define GPIO_PIN_7   7
#define GPIO_PIN_8   8
#define GPIO_PIN_9   9
#define GPIO_PIN_10  10
#define GPIO_PIN_11  11
#define GPIO_PIN_12  12
#define GPIO_PIN_13  13
#define GPIO_PIN_14  14
#define GPIO_PIN_15  15


/******************************************************
 * API's Supported by this drivers
 *
 ******************************************************/
/*
 * peripheral clock control
 */
void GPIO_PClkCtrl(GPIO_Regdef_t *pGPIOx, uint8_t EnorDi);

/*
 * Init and De-Init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle); //to initialize the registers of the given GPIO
void GPIO_InterruptEn(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_Regdef_t *pGPIOx);	//to De-initialize the registers of the given GPIO

/*
 * Data Input/output mode of GPIO Pin
 */
uint8_t GPIO_ReadFromInputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_Regdef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_Regdef_t *pGPIOx, uint16_t Value);
void GPIO_TogglePin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber);
/*
 * Interrupt process
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);//to configure the IRQnumber
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);//to set interrupt priority for IRQ number
void GPIO_IRQHandling(uint8_t PinNumber); //IRQ  handler should know from which pin the interrupt is generated

/*
 * GPIO_MODE_REG
 */

/*
 * GPIO_IDR
 */






