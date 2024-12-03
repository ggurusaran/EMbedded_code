/*
 * button_toggle.c
 *
 *  Created on: Nov 29, 2024
 *      Author: gurus
 */
#include<stdint.h>
#include<string.h>

#include"stm32f103xx.h"
#include"stm32f103xx_gpio_driver.h"

void delay(void)
{
	for (uint32_t i=0 ; i<500000; i++);
}

int main(){
	GPIO_Handle_t GPIOBtn, GPIOLed;

	GPIOB_PCLK_EN();
	memset(&GPIOLed,0,sizeof(GPIOLed));
	memset(&GPIOBtn,0,sizeof(GPIOBtn));

	GPIOBtn.pGPIOx = GPIOB;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinCnf = GPIO_IN_PUPD;


	GPIOA_PCLK_EN();
	GPIO_Init(&GPIOBtn);
	GPIO_InterruptEn(&GPIOBtn);

	GPIOLed.pGPIOx = GPIOC;
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_0;
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_2HZ;
	GPIOLed.GPIO_PinConfig.GPIO_PinCnf = GPIO_OUT_GP_PP;

	GPIO_Init(&GPIOLed);


	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);//off the led first

	//IRQ CONFIG FOR BUTTON PIN
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
	//ISR Implementation

    while(1);

}



void EXTI15_10_IRQHandler(void){
	delay();

	GPIO_IRQHandling(GPIO_PIN_10);//clear the pending event from exti line
	GPIO_TogglePin(GPIOA, GPIO_PIN_0);
}
