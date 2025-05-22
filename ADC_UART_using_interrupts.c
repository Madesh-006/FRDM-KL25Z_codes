#include "MKL25Z4.h"
#include <stdio.h>
static uint32_t i=0U;
void ADC0_IRQHandler(void);
void UART0_IRQHandler(void);
int main()
{
    SIM_SOPT2 |= (1<<26);
    SIM_SCGC6 |= (1<<27);
	
		SIM_SCGC4 |= (1<<10);
		SIM_SCGC5 |= (1<<9) | (1<<10);
		PORTA_PCR2 |= (0x902 <<8);//TX pin
		uint16_t sbr = 24000000/(16*9600);
		UART0_BDL = sbr & 0xFF;
		UART0_BDH |= (sbr>>8)&0x1F;
		UART0_C2 |= UART_C2_TE_MASK | UART_C2_TIE_MASK;
		PORTB_PCR1 |= 0x0;
		NVIC_EnableIRQ(UART0_IRQn);
		//+NVIC_EnableIRQ(ADC0_IRQn);
		//ADC0_SC1A |= 0x48;
	ADC0_CFG1 = 0x0;
  UART0_D=32;  
	while (1)
    {
			
			
		}
}

void ADC0_IRQHandler(void){			
}

void UART0_IRQHandler(void){
				i=ADC0_RA;
			UART0_D=i;			
				ADC0_SC1A |= 0x49;
				PORTA_ISFR =0xFFFF;
	
}
