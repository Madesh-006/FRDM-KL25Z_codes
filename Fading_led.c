// Fading Led

#include "MKL25Z4.h"
void delay(int32_t i);
	
void delay(int32_t i){
    for(int32_t j=0; j<i; j++){
        __NOP();
    }
}

int main(void){
    SIM_SCGC5 = 0x000003F00; // All PORT A-E clocks enabled
    PORTD_PCR1 = 0x00000100; // Port D pin controller register 1 configures Pin 1 of Port D as a GPIO.
    GPIOD_PDDR = 0xFFFFFFFF; // Port D Data Direction Register. as all are one all are output
    int32_t t=5000;
    
    while(1){
        for (int32_t i=t; i>0; i-=5){
            GPIOD_PDOR = 0xFFFFFFFF; // Port data output register
            delay(i);
            GPIOD_PDOR = 0x00000000;
            delay(t-i);
        }
        
        for (int32_t i=t; i>0; i-=5){
            GPIOD_PDOR = 0xFFFFFFFF;
            delay(t-i);
            GPIOD_PDOR = 0x00000000;
            delay(i);
        }
        
        // 50 percent
        // GPIOD_PDOR = 0xFFFFFFFF;
        // delay(100000/2);
        // GPIOD_PDOR = 0x00000000;
        // delay(100000);
        
        // 75 percent
        // GPIOD_PDOR = 0xFFFFFFFF;
        // delay((100000*3)/4);
        // GPIOD_PDOR = 0x00000000;
        // delay(100000);
    }
} 
