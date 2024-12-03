#include <stdint.h>
#include "stm32f103xx.h"
#include "stm32f103xx_gpio_driver.h"

void delay(void)
{
    for (uint32_t i = 0; i < 500000/2 ; i++);
}

int main(void)
{
    // Enable clock for GPIOA and GPIOC
    GPIOB_PCLK_EN();
    GPIOC_PCLK_EN();

    // Initialize PC13 (onboard LED) as output
    GPIO_Handle_t GpioBtn, GpioLed;
    GpioBtn.pGPIOx = GPIOB;
    GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
    GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GpioBtn.GPIO_PinConfig.GPIO_PinCnf = GPIO_IN_PUPD;
    GPIO_Init(&GpioBtn);


    GpioLed.pGPIOx = GPIOC;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_2HZ;
    GpioLed.GPIO_PinConfig.GPIO_PinCnf = GPIO_OUT_GP_PP;
    GPIO_Init(&GpioLed);





    while (1)
    {
    	uint32_t pinStatus = GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_10);

    	if(pinStatus){

    		GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    		delay();
    	}
    }
    return 0;
}
