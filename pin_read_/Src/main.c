
#include <stdint.h>

int main(void)
{
	uint32_t  *pclkctrlreg   = (uint32_t*)0x40021018;
	uint32_t  *pportcmodereg = (uint32_t*)0x40011004;
	uint32_t  *pportcoutreg  = (uint32_t*)0x4001100C;

	uint32_t  *pportAmodereg = (uint32_t*)0x40010800;
	uint32_t  *pportAInreg  = (uint32_t*)0x40010808;

    //RCC CLOCK (RCC_APB2ENR)
	*pclkctrlreg |= (1<<4);//enable clock for PortC output
	*pclkctrlreg |= (1<<2);//enable clock for PortA input

    //GPIO MODE REG.
	*pportcmodereg &= ~(0xF << 20);  // Clear bits 20-23 for PC13
	*pportcmodereg |= (0x2 << 20);   // Set PC13 as output, push-pull, max speed 2 MHz
	//for portA input
	*pportAmodereg &= ~(0xF << 0);
	*pportAmodereg |= ~(0x8 << 0);

	//read pin status of pin PA0 (GPIO IDR REG.)
	while(1){
		uint8_t pinStatus = (uint32_t)(*pportAInreg & 0x1);

		if(pinStatus){
			//turn on led
			*pportcoutreg &= ~(1<<13);
		}
		else{
			*pportcoutreg |= (1<<13);
		}
	}





}
