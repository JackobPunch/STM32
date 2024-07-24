#include<stdint.h>
#include<stdio.h>

void delay(void)
{
	for(uint32_t i =0 ; i < 3000000 ; i++);

}

int main(void)
{
	printf("Start of initialization\n");
	//peripheral register addresses
	uint32_t volatile *const pGPIOEModeReg  =  (uint32_t*)(0x40021000);
	uint32_t volatile *const pGPIOFModeReg  =  (uint32_t*)(0x40021400);
	uint32_t volatile *const pEInPutDataReg  =  (uint32_t*)(0x40021000 + 0x10);
	uint32_t volatile *const pFInPutDataReg  =  (uint32_t*)(0x40021400 + 0x10);
	uint32_t volatile *const pEOutPutDataReg =  (uint32_t*)(0x40020C00 + 0x14);
	uint32_t volatile *const pClockCtrlReg  =  (uint32_t*)(0x40023800 + 0x30);
	uint32_t volatile *const pEPullupDownReg =  (uint32_t*)(0x40021000 + 0x0C);
	uint32_t volatile *const pFPullupDownReg =  (uint32_t*)(0x40021400 + 0x0C);

     //1.Enable the peripheral clock of GPIOE and GPIOF peripheral
	*pClockCtrlReg |= ( 3 << 4);


    // 2.configure PE2, PE3, PE4, PE5 as output (rows)
	*pGPIOEModeReg &= ~(0xFF<<4); //clear
	*pGPIOEModeReg |= (0x55<<4);   //set


	// 3. configure PE6 , PF7, PF8, PF9 as input (columns)
	*pGPIOEModeReg &= ~(0x3<<12); //clear
	*pGPIOFModeReg &= ~(0x3F<<14); //clear

	// 4.Enable internal pull-up resistors for PE6 , PF7, PF8, PF9
    *pEPullupDownReg &= ~(0x3<<12); //clear
    *pEPullupDownReg |= (0x1<<12); //set
    *pFPullupDownReg &= ~(0x3F<<14); //clear
    *pFPullupDownReg |= (0x15<<14); //set

    printf("End of initialization\n");

while(1)
{
    //make all rows HIGH
    *pEOutPutDataReg |= (0x0F<<2);

    //make R1 LOW(PE2)
    *pEOutPutDataReg &= ~( 1 << 2);

    //scan the columns
    //check C1(PE6) low or high
    if(!(*pEInPutDataReg & ( 1 << 6))){
    	//key is pressed
    	delay();
    	printf("1\n");
    }

    //check C2(PF7) low or high
    if(!(*pFInPutDataReg & ( 1 << 7))){
    	//key is pressed
    	delay();
    	printf("2\n");
    }

    //check C3(PF8) low or high
    if(!(*pFInPutDataReg & ( 1 << 8))){
    	//key is pressed
    	delay();
    	printf("3\n");
    }

    //check C4(PF9) low or high
    if(!(*pFInPutDataReg & ( 1 << 9))){
    	//key is pressed
    	delay();
    	printf("A\n");
    }


    //make all rows HIGH
     *pEOutPutDataReg |= (0x0f<<2);
    //make R2 LOW(PE3)
    *pEOutPutDataReg &= ~( 1 << 3);

    //scan the columns
    //check C1(PE6) low or high
    if(!(*pEInPutDataReg & ( 1 << 6))){
    	//key is pressed
    	delay();
    	printf("4\n");
    }

    //check C2(PF7) low or high
    if(!(*pFInPutDataReg & ( 1 << 7))){
    	//key is pressed
    	delay();
    	printf("5\n");
    }

    //check C3(PF8) low or high
    if(!(*pFInPutDataReg & ( 1 << 8))){
    	//key is pressed
    	delay();
    	printf("6\n");
    }

    //check C4(PF9) low or high
    if(!(*pFInPutDataReg & ( 1 << 9))){
    	//key is pressed
    	delay();
    	printf("B\n");
    }

    //make all rows HIGH
     *pEOutPutDataReg |= (0x0f<<2);
    //make R3 LOW(PE4)
    *pEOutPutDataReg &= ~( 1 << 4);

    //scan the columns
    //check C1(PE6) low or high
    if(!(*pEInPutDataReg & ( 1 << 6))){
    	//key is pressed
    	delay();
    	printf("7\n");
    }

    //check C2(PF7) low or high
    if(!(*pFInPutDataReg & ( 1 << 7))){
    	//key is pressed
    	delay();
    	printf("8\n");
    }

    //check C3(PF8) low or high
    if(!(*pFInPutDataReg & ( 1 << 8))){
    	//key is pressed
    	delay();
    	printf("9\n");
    }

    //check C4(PF9) low or high
    if(!(*pFInPutDataReg & ( 1 << 9))){
    	//key is pressed
    	delay();
    	printf("C\n");
    }

    //make all rows HIGH
     *pEOutPutDataReg |= (0x0f<<2);
    //make R4 LOW(PE5)
    *pEOutPutDataReg &= ~( 1 << 5);

    //scan the columns
    //check C1(PE6) low or high
    if(!(*pEInPutDataReg & ( 1 << 6))){
    	//key is pressed
    	delay();
    	printf("*\n");
    }

    //check C2(PF7) low or high
    if(!(*pFInPutDataReg & ( 1 << 7))){
    	//key is pressed
    	delay();
    	printf("0\n");
    }

    //check C3(PF8) low or high
    if(!(*pFInPutDataReg & ( 1 << 8))){
    	//key is pressed
    	delay();
    	printf("#\n");
    }

    //check C4(PF9) low or high
    if(!(*pFInPutDataReg & ( 1 << 9))){
    	//key is pressed
    	delay();
    	printf("D\n");
    }

}//while end

}

