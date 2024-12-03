/*
 * stm32f103xx.h
 *
 *  Created on: Nov 21, 2024
 *      Author: gurus
 */

#ifndef INC_STM32F103XX_H_
#define INC_STM32F103XX_H_

#define __vo volatile

#include<stdint.h>

/*
 ************************************{|PROCESOR SPECIFIC DETAILS******************************************
 *
 *ARM CORTEX NVIC ISER REGISTER ADDRESS
 */

#define NVIC_ISER0			    ((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1				((__vo uint32_t*)0xE000E104)
#define NVIC_ICER0				((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1				((__vo uint32_t*)0xE000E184)

//Interrupt Priority Register

#define NVIC_IPR_BASEADDR		((__vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED   4

///********************************************************************************************************

#define IRQ_NO_EXTI0              6
#define IRQ_NO_EXTI1 			  7
#define IRQ_NO_EXTI2 		      8
#define IRQ_NO_EXTI3 			  9
#define IRQ_NO_EXTI4 			  10
#define IRQ_NO_EXTI9_5            23
#define IRQ_NO_EXTI15_10          40

/*
 * MACROS For POSSIBLE PRIORITY LEVELS
 */

#define NVIC_IRQ_PRIO             0
#define NVIC_IRQ_PRI1             1
#define NVIC_IRQ_PRI2             2
#define NVIC_IRQ_PRI3             3
#define NVIC_IRQ_PRI4             4
#define NVIC_IRQ_PRI5             5
#define NVIC_IRQ_PRI6             6
#define NVIC_IRQ_PRI7             7
#define NVIC_IRQ_PRI8             8
#define NVIC_IRQ_PRI9             9
#define NVIC_IRQ_PRI1O            10
#define NVIC_IRQ_PRI11            11
#define NVIC_IRQ_PRI12            12
#define NVIC_IRQ_PRI13            13
#define NVIC_IRQ_PRI14            14
#define NVIC_IRQ_PRI15            15










/*
 *
 * Base address of flash and SRAM
 */
#define FLASH_BASEADDR         	0x08000000U
#define SRAM1_BASEADDR		  	0x20000000U //No sram2 for blue pill
#define ROM				     	0x1FFFF000U //system memory
#define SRAM                  	SRAM1_BASEADD
/*
 * AHB and APB peripheral base
 */
#define PERIPH_BASEADDR			0X40000000U
#define AHBPERIPH_BASEADDR		0X40018000U
#define APB1PERIPH_BASEADDR		0X40000000U
#define APB2PERIPH_BASEADDR 	0X40010000U

/*
 * gpio peripherals base address
 */
#define GPIOA_BASEADDR          0X40010800U
#define GPIOB_BASEADDR			0X40010C00U
#define GPIOC_BASEADDR			0X40011000U
#define GPIOD_BASEADDR			0X40011400U

#define I2C1_BASEADDR			0x40005400U
#define I2C2_BASEADDR			0X40005800U

#define SPI1_BASEADDR 			0X40013000U
#define SPI2_BASEADDR			0X40003800U
#define ADC1_BASEADDR			0X40012400U
#define ADC2_BASEADDR			0X40012800U

/******Peripheral register definition structure ******
 *
 *
 */

typedef struct
{
	__vo uint32_t CRL;
	__vo uint32_t CRH;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSSR;
	__vo uint32_t BRR;
	__vo uint32_t LCKR;
}GPIO_Regdef_t;

#define GPIOA 	((GPIO_Regdef_t*)GPIOA_BASEADDR)
#define GPIOB   ((GPIO_Regdef_t*)GPIOB_BASEADDR)
#define GPIOC	((GPIO_Regdef_t*)GPIOC_BASEADDR)
#define GPIOD	((GPIO_Regdef_t*)GPIOD_BASEADDR)

/*
 ***************** macros to enable and disable RCC peripheral clock********************
 */

#define RCC_BASEADDR    0X40021000U

typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t APB1RSTR;
	__vo uint32_t AHBENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t APB1ENR;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t AHBSTR;
	__vo uint32_t CFRG2;
}RCC_Regdef_t;

#define RCC         ((RCC_Regdef_t*)RCC_BASEADDR)


/*
 ************************** EXTI Peripheral of NVIC******************************
 */

#define EXTI_BASEADDR			0x40010400U //external interrupt controller

typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_Regdef_t;

#define EXTI       ((EXTI_Regdef_t*)EXTI_BASEADDR)

/*
 ************************** AFIO Peripheral of NVIC ( ~syscfg) ******************************
 */

#define AFIO_BASEADDR            0x40010000U

typedef struct
{
	__vo uint32_t EVCR;
	__vo uint32_t MAPR1;
	__vo uint32_t EXTICR[3];
	__vo uint32_t MAPR2;
}AFIO_Regdef_t;

#define AFIO        ((AFIO_Regdef_t*)AFIO_BASEADDR)

#define AFIO_PCLK_EN()     RCC->APB2ENR |=  (1<<0)
#define AFIO_PCLK_DIS()    RCC->APB2ENR &= ~(1<<0)



/*
 * Peripheral register definition for *************I2C*************
 */

typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t OAR1;
	__vo uint32_t OAR2;
	__vo uint32_t DR;
	__vo uint32_t SR1;
	__vo uint32_t SR2;
	__vo uint32_t CCR;
	__vo uint32_t TRISE;
}I2C_Regdef_t;

#define I2C1        ((I2C_Regdef_t*)I2C1_BASEADDR)
#define I2C2		((I2C_Regdef_t*)I2C2_BASEADDR)

//clk enable for I2C peripherals
#define I2C1_CLK_EN()      RCC -> APB1ENR |= (1<<21)
#define I2C2_CLK_EN()      RCC -> APB1ENR |= (1<<22)

//clk disable for I2C peripherals
#define I2C1_CLK_DIS()     RCC -> APB1ENR &= ~(1<<21)
#define I2C2_CLK_DIS()     RCC -> APB1ENR &= ~(1<<22)

/*
 ************************************************ USART/UART*********************************************
 */

#define USART1_BASEADDR  0X40013800U
#define USART2_BASEADDR  0X40004400U
#define USART3_BASEADDR  0x40004800U
#define UART4_BASEADDR	 0X40004C00U
#define UART5_BASEADDR 	 0X40005000U


typedef struct
{
	__vo uint32_t SR;   //Status register
	__vo uint32_t DR;   //Data Register
	__vo uint32_t BRR;  // baud rate register-setting baudrate
	__vo uint32_t CR1;  // control register
	__vo uint32_t CR2;
	__vo uint32_t CR3;
	__vo uint32_t GTPR;

}UART_Regdef_t;

#define USART1          ((UART_Regdef_t*)USART1_BASEADDR)
#define USART2 			((UART_Regdef_t*)USART2_BASEADDR)
#define USART3			((UART_Regdef_t*)USART3_BASEADDR)
#define UART4  			((UART_Regdef_t*)UART4_BASEADDR)
#define UART5			((UART_Regdef_t*)UART5_BASEADDR)

/*
 ********************************Functions/operations on peripherals*************************************
 */

//CLK Enable for gpio peripherals
#define GPIOA_PCLK_EN()   RCC -> APB2ENR |= (1<<2)
#define GPIOB_PCLK_EN()   RCC -> APB2ENR |= (1<<3)
#define GPIOC_PCLK_EN()   RCC -> APB2ENR |= (1<<4)
#define GPIOD_PCLK_EN()   RCC -> APB2ENR |= (1<<5)


//CLK ENABLE FOR SPI PERIPHERALS
#define SPI1_CLK_EN()     RCC -> APB2ENR |= (1<<12)
#define SPI2_CLK_EN()     RCC -> APB1ENR |= (1<<14)
#define SPI3_CLK_EN()     RCC -> APB1ENR |= (1<<15)

//clk enable for usart peripheral
#define USART1_CLK_EN()     RCC -> APB2ENR |= (1<<14)
#define USART2_CLK_EN()     RCC -> APB1ENR |= (1<<17)
#define USART3_CLK_EN()     RCC -> APB1ENR |= (1<<18)
/********************************************************************************************************************
 * MACROS TO DISABLE CLOCK
 */

//CLK Disable for gpio peripherals
#define GPIOA_PCLK_DIS()   RCC -> APB2ENR &= ~(1<<2)
#define GPIOB_PCLK_DIS()   RCC -> APB2ENR &= ~(1<<3)
#define GPIOC_PCLK_DIS()   RCC -> APB2ENR &= ~(1<<4)
#define GPIOD_PCLK_DIS()   RCC -> APB2ENR &= ~(1<<5)

//clk disable for I2C peripherals
#define I2C1_CLK_DIS()     RCC -> APB1ENR &= ~(1<<21)
#define I2C2_CLK_DIS()     RCC -> APB1ENR &= ~(1<<22)

//CLK DISABLE FOR SPI PERIPHERALS
#define SPI1_CLK_DIS()     RCC -> APB2ENR &= ~(1<<12)
#define SPI2_CLK_DIS()     RCC -> APB1ENR &= ~(1<<14)
#define SPI3_CLK_DIS()     RCC -> APB1ENR &= ~(1<<15)

//clk disable for usart peripheral
#define USART1_CLK_DIS()     RCC -> APB2ENR &= ~(1<<14)
#define USART2_CLK_DIS()     RCC -> APB1ENR &= ~(1<<17)
#define USART3_CLK_DIS()     RCC -> APB1ENR &= ~(1<<18)


/******************************************************************************************************************
 * some generic macros
 */

#define ENABLE     		1
#define DISABLE    		0
#define SET		   		ENABLE
#define RESET 	   		DISABLE
#define GPIO_PIN_SET 	SET
#define GPIO_PIN_RESET  RESET

/*
 * Macros to reset peripherals
 */
#define GPIOA_REG_RESET()   do{ (RCC -> APB2RSTR |= (1<<2)); (RCC -> APB2RSTR &= ~(1<<2));}while(0)
#define GPIOB_REG_RESET()   do{(RCC -> APB2RSTR |= (1<<3)); (RCC -> APB2RSTR &= ~(1<<3));}while(0)
#define GPIOC_REG_RESET()   do{(RCC -> APB2RSTR |= (1<<4)); (RCC -> APB2RSTR &= ~(1<<4));}while(0)
#define GPIOD_REG_RESET()   do{(RCC -> APB2RSTR |= (1<<5)); (RCC -> APB2RSTR &= ~(1<<5));}while(0)

/* GPIO possible output modes
 *
 *
 *
 *00: Input mode (reset state)
 *01: Output mode, max speed 10 MHz.
 *10: Output mode, max speed 2 MHz.
 *11: Output mode, max speed 50 MHz
 */
#define GPIO_MODE_IN         0
#define GPIO_MODE_OUT_10MHZ  1
#define GPIO_MODE_OUT_2HZ    2
#define GPIO_MODE_OUT_50MHZ  3

#define GPIO_MODE_IT_FT		 4
#define GPIO_MODE_IT_RT		 5
#define GPIO_MODE_IT_RFT 	 6
/*
 *In output mode (MODE[1:0] >00):
 00: General purpose output push-pull
 01: General purpose output Open-drain
 10: Alternate function output Push-pull
 11: Alternate function output Open-drain
 */

#define GPIO_OUT_GP_PP    	 0
#define GPIO_OUT_GP_OD		 1
#define GPIO_OUT_ALTFUN_PP	 2
#define GPIO_OUT_ALTFUN_OD	 3

/*
 * In input mode (MODE[1:0]=00):
 00: Analog mode
 01: Floating input (reset state)
 10: Input with pull-up / pull-down
 11: Reserved
 */

#define GPIO_IN_ANALOG 		 0
#define GPIO_IN_FLOAT		 1 //RESET STAGE
#define GPIO_IN_PUPD		 2
#define GPIO_IN_RES			 3



#endif /* INC_STM32F103XX_H_ */
