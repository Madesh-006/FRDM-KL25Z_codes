
#include "MKL25Z4.h"


void delay1(int32_t i);

void delay1(int32_t i)
{
    int32_t j=0;
    for(j=0;j<i;j++)
    {
        __NOP();
    }
}

int main(void)
{
	SIM_SCGC5 |= 0x00003F00; // Clocks For All Ports
	SIM_SCGC6|=0x08000000; // 27th bit has ADC0's Clock
	PORTB_PCR0|=0x00000000; // Pin disabled (Analog Pin)
	ADC0_SC1A|=0x00000008;  // Status and Control Registers for that ADC // 01000 When DIFF=0, AD8 is selected as input; when DIFF=1, it is reserved. - Check
	ADC0_CFG1|=0x00000000; // Configuration Register 
	PORTC_PCR0 |=0x00000100;
	PORTC_PCR1 |=0x00000100;
	PORTC_PCR2 |=0x00000100;
	PORTC_PCR3 |=0x00000100;
	PORTC_PCR4 |=0x00000100;
	PORTC_PCR5 |=0x00000100;
	PORTC_PCR6 |=0x00000100;
	PORTC_PCR7 |=0x00000100;
	PORTC_PCR10 |=0x00000100;
	PORTC_PCR11 |=0x00000100;
	GPIOC_PDDR |= 0xffffffff;
	GPIOC_PDOR |= 0x000000ff;
	GPIOB_PDDR|= 0xffffffff;
	GPIOB_PDOR |= 0x000000ff;
	
	
	#define 	for0 0x00000c00;
	#define		for1 0x00000CF0;
	#define		for2 0x00000848;
	#define		for3 0x00000B66;
	#define		for4 0x000008B0;
	#define		for5 0x00000821;
	#define		for6 0x00000801;
	#define		for7 0x00000c70;
	#define		for8 0x00000800;
	#define		for9 0x00000820;
	
	GPIOC_PDOR = for0
	
	uint32_t b;
	int a;
				
	while(1)
	{
		ADC0_SC1A=0x00000008;
		
		while(!(ADC0_SC1A & 0x00000080)) // the COCO set to 1 when ADC conversion complete 
		{
			__NOP();
			
		}
		b = ADC0_RA; // Data Result Register
		a = b/25;
		a = (int)a;
		
		if (a==0){
			GPIOC_PDOR = for0
			delay1(2000000);
		}
		else if (a==1){
			GPIOC_PDOR = for1
			delay1(2000000);
		}
		else if (a==2){
			GPIOC_PDOR = for2
			delay1(2000000);
		}
		else if (a==3){
			GPIOC_PDOR = for3
			delay1(2000000);
		}
		else if (a==4){
			GPIOC_PDOR = for4
			delay1(2000000);
		}
		else if (a==5){
			GPIOC_PDOR = for5
			delay1(2000000);
		}
		else if (a==6){
			GPIOC_PDOR = for6
			delay1(2000000);
		}
		else if (a==7){
			GPIOC_PDOR = for7
			delay1(2000000);
		}
		else if (a==8){
			GPIOC_PDOR = for8
			delay1(2000000);
		}
		else{
			GPIOC_PDOR = for9
			delay1(2000000);
		}
}
}

// line 22 ask jake