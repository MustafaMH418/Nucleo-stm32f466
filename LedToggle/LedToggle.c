#include <stdint.h>


int main(void)
{
    
    uint32_t *pClKctrlR = (uint32_t*)0x40023830;		//Address of RCC_AHB1ENR
    uint32_t *pPortModeR = (uint32_t*)0x40020000;		//Address of Port Mode Register
    uint32_t *pODR = (uint32_t*)0x40020014;			//Address of Output Data Register

    //Setting RCC_AHB1ENR To Enable CLock for GPioA
    *pClKctrlR |= 1;

    //Setting port Mode Register
    *pPortModeR &= ~(3<<10); 	//Clearing 26&27 bits
    *pPortModeR |= (1<<10);		// Setting 26 = 1 & 27 = 0

    //Blinking
    while(1){
    	for(uint32_t i = 0;i<=400000;i++);
    	*pODR |= (1<<5);
    	for(uint32_t i = 0;i<=400000;i++);
    	*pODR &= ~(1<<5);
    }

	for(;;);
}
