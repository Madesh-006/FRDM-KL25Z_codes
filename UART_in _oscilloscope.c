
// uARt in oscilloscope
// SOPT - System options Register 
#include "MKL25Z4.h"

int main(void)
{
int i=10;
char j[2] = "he";

    SIM_SOPT5 = 0x000000; // UART0 TX pin is the IO pin (no modulation)
    SIM_SOPT2 |= 0x04000000; // UART0 clock source is master clk

    SIM_SCGC5 |= 0x00000600; // Port A & B clock enabled (Port B = ADC, Port A = TX pin)
	
    SIM_SCGC4 |= 0x00000400; // UART0 clock enabled

    // Port A2 as UART0 TX (Alternative 2)
    PORTA_PCR2 = 0x00000200; // A2 as UART0_TX
    PORTA_PCR1 = 0x00000200; // A1 as UART0_RX

    UART0_BDH = 0x00; // One stop bit, no interrupts
    UART0_BDL = 0x89; // BDH:BDL gives 16bit clock divide, 0x1A = 130 (20971520/16/130 baud)
    UART0_C2 = 0x0C; // Interrupts disabled, TX and RX pins enabled

    while(1) {
			
				for(int k=0;k<2;k++)
					{
						UART0_D = j[k];
					}
        
        

        while(!(UART0_S1 & 0x80))  
					{
					// Wait while transmission is happening
						__NOP();
					}
    }
}
