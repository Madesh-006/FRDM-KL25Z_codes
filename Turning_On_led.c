// lab Exercise 1 Blink Led from NXP 
# include "MKL25Z4.h" // use only double quotes bro!!

void delay (int32_t i){
	
	int32_t j=0;
	for( j=0;j<i;j++){
	__NOP();
	}
}

int main(void){
	SIM_SCGC5 = 0x000003F00; // System Clock Gating Control Register 
	PORTB_PCR19 = 0x00000100; // Pin Control Register
	GPIOB_PDDR = 0xFFFFFFFF; // Data Direction (decides input or output) all f-outupt, 0-input

	while(1){
		GPIOB_PDOR = 0xffffffff;
		delay(1000000);
		GPIOB_PDOR = 0x00000000;
		delay(1000000);
		
	} // led blinks with some dalay
}


// Find out that table page from datasheet
// U r changing output to input every delay cycle whats the correct approach?