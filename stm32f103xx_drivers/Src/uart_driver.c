/*
 * uart_driver.c
 *
 *  Created on: Nov 25, 2024
 *      Author: gurus
 */

#include<stdint.h>
#include<stdio.h>

#include"stm32f103xx_gpio_driver.h"

char mymsg = 'C';

int uart_driver(void){

	//enable the alternate function pin
	RCC->APB2ENR |= (1<<0);
	//ENABLE UART_2
	RCC->APB1ENR |= (1<<17);
	//enable the related pins(mode,etc..)
	GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_50MHZ, GPIO_OUT_ALTFUN_PP); //TX
	GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_IN, GPIO_IN_PUPD);              //RX

	//set the UART baud rate FOR 9600BPS
	USART2->BRR |= 0x01A0;		           //Set BaudRate to hexadecimal number EA6
    //ENABLE Uart transmit and receive
	USART2->CR1 |= (1<<3);
	USART2->CR1 |= (1<<2);
	//uart enable(UE) in CR1
	USART2->CR1 |= (1<<13);


	while(1)
	{
        while (!(USART2->SR & (1 << 7)))// Wait until TXE (Transmit Data Register Empty) is set
        {};
		USART2->DR = mymsg;
	}
}

/

 */
