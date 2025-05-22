// Seven segment display - my code

#include "MKL25Z4.h"
 
void delay(int32_t i){
	
	int32_t j=0;
	for( j=0;j<i;j++){
	__NOP();
	}
}

int main(void){
	SIM_SCGC5=0x00000800;
	//Setting portC as GPIO; First display
	PORTC_PCR7=0x00000100;
	PORTC_PCR0=0x00000100;
	PORTC_PCR3=0x00000100;
	PORTC_PCR4=0x00000100;
	PORTC_PCR5=0x00000100;
	PORTC_PCR6=0x00000100;
	PORTC_PCR10=0x00000100;
	PORTC_PCR11=0x00000100;
	

	
	//SETTING PINS AS OUTPUT PINS;

	GPIOC_PDDR=0xFFFFFFFF;
	GPIOA_PDDR=0xFFFFFFFF;
	GPIOD_PDDR=0xFFFFFFFF;
	
	while(1){
		
		// Ones place
		
		GPIOC_PDOR=0x00000c00;
		delay(2000000);
		GPIOC_PDOR=0x00000CF0;
		delay(2000000);
		GPIOC_PDOR=0x00000848;
		delay(2000000);
		GPIOC_PDOR=0x00000B66;
		delay(2000000);
		GPIOC_PDOR=0x000008B0;
		delay(2000000);
		GPIOC_PDOR=0x00000821;
		delay(2000000);
		GPIOC_PDOR=0x00000801;
		delay(2000000);
		GPIOC_PDOR=0x00000c70;
		delay(2000000);
		GPIOC_PDOR=0x00000800;
		delay(2000000);
		GPIOC_PDOR=0x00000820;
		delay(2000000);
		
		
	}
}



// jake code - (as it contains double display)

#include "MKL25Z4.h"

#define SEG0  0x1A000;
#define SEG1  0x1AA82;
#define SEG2  0x18820;
#define SEG3  0x10A00;
#define SEG4  0x10282;
#define SEG5  0x18208;
#define SEG6  0x18008;
#define SEG7  0x1AA80;
#define SEG8  0x18000;
#define SEG9  0x18280;


void print_no(int no);
void delay(int32_t t);
void set1st(void);
void set2nd(void);
void clear(void);
void print_doubledigit(int no);
//static int32_t duration = 50000;
static int32_t switchtime =100;
int main(){
SIM_SCGC5=0x0F80;
	SIM_SCGC6 =0x08000000;
	ADC0_SC1A = 0x0008;
	ADC0_CFG1 = 0x0000;
	//ADC
	
	
	
GPIOC_PDDR=0xFFFFFFFF;
GPIOA_PDDR= 0xFFFFFFFF;
PORTA_PCR1 |= 0x00100;
		PORTB_PCR0 = 0x0;
	PORTA_PCR2 |= 0x00100;
PORTC_PCR1 |=0x00100;
PORTC_PCR3 |=0x00100;
PORTC_PCR5 |=0x00100;
PORTC_PCR7 |=0x00100;
PORTC_PCR9 |=0x00100;
PORTC_PCR11 |=0x00100;
PORTC_PCR13 |=0x00100;
PORTC_PCR15 |=0x00100;
PORTC_PCR16 |= 0x00100;
	PORTA_PCR1 |=0x00100;
	PORTA_PCR2 |= 0x00100;

	uint32_t a;
	int value;
	
	
while (1){
		ADC0_SC1A=0x008;
		while ( !(ADC0_SC1A & 0x000080)){
		 __NOP();
		}
		a= ADC0_RA;
		value = a/3;
		print_doubledigit(value);

}	
}

void delay(int32_t t){
for (int32_t j=0;j<t;j++){
__NOP();
}
}

void clear(void){
GPIOC_PDOR =0xFFFFFF;
}

void print_doubledigit(int no){
		set1st();
		clear();
		print_no(no/10);
		delay(switchtime);
		set2nd();
		clear();
		print_no(no%10);
		delay(switchtime);
}

void print_no(int no){
	switch (no){
		case 0:
			GPIOC_PDOR = SEG0
			break;
		case 1:
			GPIOC_PDOR =SEG1
			break;
		case 2:
			GPIOC_PDOR =SEG2
		break;
				case 3:
			GPIOC_PDOR = SEG3
			break;
		case 4:
			GPIOC_PDOR =SEG4
			break;
		case 5:
			GPIOC_PDOR =SEG5
		break;
				case 6:
			GPIOC_PDOR = SEG6
			break;
		case 7:
			GPIOC_PDOR =SEG7
			break;
		case 8:
			GPIOC_PDOR =SEG8
		break;
			case 9:
			GPIOC_PDOR =SEG9
		break;
			
	}
}

void set1st(void){
GPIOA_PDOR = 0x2;
}
void set2nd(void){
GPIOA_PDOR =0x4;
}


