
#include<stdint.h>

int main(void)
{
	uint32_t  *pclkctrlreg   = (uint32_t*)0x40021018;
	uint32_t  *pportcmodereg = (uint32_t*)0x40011004;
	uint32_t  *pportcoutreg  = (uint32_t*)0x4001100C;

	*pclkctrlreg |= (1<<4);


    *pportcmodereg &= ~(0xF << 20);  // Clear bits 20-23 for PC13
	*pportcmodereg |= (0x2 << 20);   // Set PC13 as output, push-pull, max speed 2 MHz

	*pportcoutreg &= ~(1<<13);

	while(1)
	{
	        *pportcoutreg ^= (1 << 13);  // Toggle PC13
	        for (volatile int i = 0; i < 100000; i++);  // Simple delay

	}
}
