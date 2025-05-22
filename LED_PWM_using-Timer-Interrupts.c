
#include "MKL25Z4.h"// (LED PWM using Timer interrupts, working)

  

volatile int brightness = 0; //brightness intensity variable
volatile int direction = 1;  //to indicate brightening or dimming

void init_PWM(void); 
void init_Timer(void);

int main(void) {
    SIM_SCGC5 |= 0x0400;  //enabling clocks and ports
    SIM_SCGC6 |= 0x04000000;  // TPM2
    SIM_SOPT2 |= 0x01000000;  // 01 MCGFLLCLK clock or MCGPLLCLK/2
    init_PWM();   
    init_Timer(); 

    while (1) {
        
    }
}


void init_PWM(void) {
    PORTB_PCR18 = 0x00000300; // 011 Alternative 3 (chip-specific).

    TPM2_SC = 0; //status and control register
    TPM2_MOD = 255; //upper limit
    TPM2_C0SC = 0x28;  // 5 - Channel Mode Select    3 - Edge or Level Select 
    TPM2_C0V = 255; //comparing value 

    TPM2_SC = 0x08;
}


void init_Timer(void) {
    SIM_SCGC6 |= 0x01000000; // TPM0 clock enable

    TPM0_SC = 0x0D; //led dim slower
    TPM0_MOD = 3750; 

    TPM0_SC |= 0x40; //interrupt enable
    NVIC_EnableIRQ(TPM0_IRQn); //interrupt enable
}


void TPM0_IRQHandler(void) {
    TPM0_SC |= 0x80; //clears interrupt flag to keep running

    brightness += direction; 
    if (brightness >= 255 || brightness <= 0) {
        direction = -direction; //controlling brightness and reversing direction
    }

    TPM2_C0V = 255 - brightness; 
}

