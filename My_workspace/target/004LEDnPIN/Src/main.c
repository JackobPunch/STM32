#include <stdint.h>

int main(void)
{
    volatile uint32_t *pClkCtrlReg = (uint32_t*)0x40023830;
    volatile uint32_t *pPortBModeReg = (uint32_t*)0x40020400;
    volatile uint32_t *pPortAModeReg = (uint32_t*)0x40020000;
    volatile uint32_t *pPortBOutReg = (uint32_t*)0x40020414;
    volatile uint32_t *pPortAInReg = (uint32_t*)0x40020010;

    // Enable GPIOB clock
    //*pClkCtrlReg |= 0x00000002; // Set 1 and 0 bit to enable GPIOB and A clock
    *pClkCtrlReg |= (3<<0);

    // Configure PB7 as output
    //*pPortBModeReg &= 0xFFFF3FFF; // Clear bits 14 and 15
    *pPortBModeReg &= ~(3<<14);
    //*pPortBModeReg |= 0x00004000; // Set bit 14 to make PB7 an output
    *pPortBModeReg |= (1<<14);

    // Configure PA0 as input
    //*pPortAModeReg &= 0xFFFFFF00; // Clear bits 0 and 1
    *pPortAModeReg &= ~(3<<0);

    uint32_t pinStatus;

    while(1){
    pinStatus = (uint32_t)((*pPortAInReg>>3)&1);
    	if(pinStatus==1){
    		// Set PB7 high
    		//*pPortBOutReg |= 0x00000080; // Set pin 7 high
    		*pPortBOutReg |= (1<<7);
    	}else{
    		*pPortBOutReg &= ~(1<<7);
    	}
    }
}
