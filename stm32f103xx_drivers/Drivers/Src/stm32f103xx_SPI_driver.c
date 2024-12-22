/*
 * stm32f103xx_SPI_Driver.c
 *
 *  Created on: Dec 11, 2024
 *      Author: gurus
 */
#include "stm32f103xx_SPI_driver.h"


void SPI_PClkCtrl(SPI_Regdef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE){
		if(pSPIx == SPI1){
			SPI1_CLK_EN();
		}
		else if(pSPIx == SPI2){
			SPI2_CLK_EN();
		}
	}
	else{
		if(pSPIx == SPI1){
			SPI1_CLK_DIS();
		}
		else if(pSPIx == SPI2){
			SPI2_CLK_DIS();
		}
	}
}

void SPI_Init(SPI_Handle_t *pSPIHandle){

	uint32_t tempReg = 0;//so that we don't need to clear bits first for every bit configuration

	//1.set mode
	tempReg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;

	//2.busconfig
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUSCONFIG_FD){
		//bidi mode should be cleared- BIDI MODE = bit 15 of SR1
		tempReg |= ~(1<<15);

	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUSCONFIG_HD){

		//bidi mode should be set, BIDI MODE = bit 15 of SR1
		tempReg |= (1<<15);

	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUSCONFIG_S_RX){
		//bidi mode should be cleared
		//RxOnly bit must be set, RXONLY MODE = bit 10 of SR1
		tempReg |= ~(1<<15);
		tempReg |= (1<<10);
	}

	//3.Configure spi serial clkspeed
	tempReg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << 3;

	//4.config DFF
	tempReg |= pSPIHandle->SPIConfig.SPI_DFF << 11;

	//5. config CPOL
	tempReg |= pSPIHandle->SPIConfig.SPI_CPOL << 1;

	//6.CONFIG CPHA
	tempReg |= pSPIHandle->SPIConfig.SPI_CPOL << 0;

	pSPIHandle->pSPIx->CR1 = tempReg;//used assignment operator because freshly initialized the cr1 register

}

void SPI_DeInit(SPI_Regdef_t *pSPIx)
{
	if(pSPIx==SPI1){
		SPI1_CLK_DIS();
	}else if(pSPIx==SPI2){
		SPI2_CLK_DIS();
	}
}


uint8_t SPI_GetFlagStatus(SPI_Regdef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}




void SPI_SendData(SPI_Regdef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len)
{
	while(len <0){
		//1.wait until TXE=1
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);//if flag is not reset, the program stays in this while loop

		//2.CHECK DFF BIT IN CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF)){

			//16bit dff format
			//load the data to DR
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			len--;
			len--;
			(uint16_t*)pTxBuffer++;


		}else{
			//8 bit dff format
			pSPIx->DR = *pTxBuffer;//buffer temporarily stores the data to be sent, but can't accessed directly by firmware
			len--;
			pTxBuffer++;
		}

	}
}






