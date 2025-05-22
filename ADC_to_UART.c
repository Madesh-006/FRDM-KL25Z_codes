#include "MKL25Z4.h"

void delay(int32_t t);

int main(){
SIM_SCGC5 |=0x600; // clocks for port A and B
SIM_SCGC6 =0x08000000; // Clock For ADC
ADC0_SC1A = 0x0008; //ADC0_SE8 pg 163 (AD8)
ADC0_CFG1 = 0x0000; // Configuring the ADC and selecting internal clock + clock divide
PORTB_PCR0 = 0x0; // Setting Port B0 as input

uint32_t a; // Creating a variable to store the value
	
PORTA_PCR2|=0x200; //For setting a to alt2 (transmiiter pin for UART) which is PTA2 to uart0tx pg 162 line 28
SIM_SCGC4 |= 0x400; //For enabling clock on UART0
SIM_SOPT2 = 0x04000000;// picking clock pg 195 - 01 MCGFLLCLK clock or MCGPLLCLK/2 clock
SIM_SOPT5 =0x0; //Set TX pin for transmit data in uart0TX =00 so all set to 0	 -00 UART0_TX pin pg 200 (enables)

	UART0_C2=0x00; //disable tx 
	uint16_t baud_rate = (20971000/(16*9600)); //formula for sbr from data sheet
	UART0_BDL = baud_rate & 0x00FF;
	UART0_BDH = (baud_rate>>8) & 0x1F; // sbr needs to set 13 bits the 5 higher bits in BDL and 8 in lower
	UART0_C2 =0x08; //enable our transmitter
	
while (1){
	
ADC0_SC1A=0x008;
		while ( !(ADC0_SC1A & 0x000080)){
		 __NOP();
		}
		a= ADC0_RA;
		while (!(UART0_S1 & 0x80)){
			__NOP();
		}
		UART0_D = a;
		delay(100000);
		while (!(UART0_S1 & 0x80)){
			__NOP();
		}
	}
}




void delay(int32_t t){
	for (int32_t j=0;j<t;j++){
	__NOP();
	}
}

