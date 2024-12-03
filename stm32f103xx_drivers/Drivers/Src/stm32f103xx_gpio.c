/*
 * stm32f103xx_gpio.c
 *
 *  Created on: Nov 21, 2024
 *      Author: gurus
 */


#include"stm32f103xx_gpio_driver.h"
/*
 * Peripheral clock setup
 */

void GPIO_PClkCtrl(GPIO_Regdef_t *pGPIOx, uint8_t EnorDi)//pGPIOX is ptr pointing to base address of GPIO port
{
	if(EnorDi == ENABLE){
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
		}
	}
	else{
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_DIS();
		}
	    else if(pGPIOx == GPIOB){
			GPIOB_PCLK_DIS();
		}
		else if(pGPIOx == GPIOC){
			GPIOC_PCLK_DIS();
		}
		else if(pGPIOx == GPIOD){
			GPIOD_PCLK_DIS();
		}
	}
}
/*
 * Init and De-Init
 */
//1) NORMAL GPIO MODE SET.
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	GPIO_Regdef_t *pGPIOx = pGPIOHandle->pGPIOx;

	if ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) < 8) {
		pGPIOx->CRL &= ~(0xFU << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) * 4));
	    pGPIOx->CRL |= (((pGPIOHandle->GPIO_PinConfig.GPIO_PinCnf) << 2 | (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode)) << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) * 4));
	}else{
		pGPIOx->CRH &= ~(0xFU << (((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) - 8) * 4));
	    pGPIOx->CRH |= (((pGPIOHandle->GPIO_PinConfig.GPIO_PinCnf) << 2 | (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode)) << (((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) - 8) * 4));
	    }
}


//2) INTERRUPT MODE SET
void GPIO_InterruptEn(GPIO_Handle_t *pGPIOHandle)
{
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_FT )
	{
		//configure the FTSR & if rtsr maybe enabled by default/accident, so  disable it
		EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	}
	else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_RT )
	{
		//configure the RTSR & disable FTSR if maybe enabled by accident
		EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}
	else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT )
	{
		//Configure both FTSR AND RTSR
		EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	}

	//2.Configure GPIO_PORT selection in AFIO_EXTICR REGISTERS
	uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
	uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;

	if (pGPIOHandle->pGPIOx == GPIOA) {
		AFIO->EXTICR[temp1] = 0 << (temp2 * 4);
	} else if (pGPIOHandle->pGPIOx == GPIOB) {
	    AFIO->EXTICR[temp1] = 1 << (temp2 * 4);
	} else if (pGPIOHandle->pGPIOx == GPIOC) {
	    AFIO->EXTICR[temp1] = 2 << (temp2 * 4);
	} else {
	    AFIO->EXTICR[temp1] = 3 << (temp2 * 4);
	}

	AFIO_PCLK_EN();

	//3.Enable EXTI Interrupt delivery for the corresponding pin number  using IMR
	EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
}

void GPIO_DeInit(GPIO_Regdef_t *pGPIOx)
{
	if(pGPIOx == GPIOA){
		GPIOA_REG_RESET();
	}
	else if(pGPIOx == GPIOB){
		GPIOB_REG_RESET();
	}
	else if(pGPIOx == GPIOC){
		GPIOC_REG_RESET();
	}
	else if(pGPIOx == GPIOD){
		GPIOD_REG_RESET();
	}
}
/*
 * Data Input/output mode of GPIO Pin
 */
uint8_t GPIO_ReadFromInputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber)//read data from a particular pin of the port
{
	uint8_t value;
	value = (uint8_t)(pGPIOx->IDR >> PinNumber) & 0x00000001;
	return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_Regdef_t *pGPIOx)// read values from entire 32 bit of a port
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;
}

void GPIO_WriteToOutputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value ==  GPIO_PIN_SET){
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

void GPIO_WriteToOutputPort(GPIO_Regdef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}


void GPIO_TogglePin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1<<PinNumber);
}
/*
 * Interrupt process
 */


//processor specific
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(IRQNumber <= 31){
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64){
			*NVIC_ISER1 |= (1 << IRQNumber % 32);
		}
	}
	else{
		if(IRQNumber <= 31){
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64){
			*NVIC_ICER1 |= (1 << IRQNumber % 32);
		}
	}

}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){

	//1. FIND OUT IPR REGISTER
	uint8_t iprx = IRQNumber/4;
	uint8_t iprx_section = IRQNumber%4;

	uint8_t shift_amount = (8*iprx_section)+(8-NO_PR_BITS_IMPLEMENTED);
	*(NVIC_IPR_BASEADDR + iprx) |= (IRQPriority << shift_amount);


}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	//1. clear the EXTI PR Register corresponding to pin number
	if(EXTI->PR & (1<< PinNumber)){

		//Clear the PR, i.e; Writing 1 to the PR
		EXTI->PR |= (1<<PinNumber);
	}

}
