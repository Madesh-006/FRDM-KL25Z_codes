

// ADC to uart using timer interrupts

#include <stdio.h>  // Include stdio for sprintf()
#include "MKL25Z4.h"

void UART0_SendChar(char c) {
    while(!(UART0->S1 & 0x80));  // Wait for transmit buffer empty
    UART0->D = c;
}

void UART0_SendString(char *str) {
    while (*str) {
        UART0_SendChar(*str++);
    }
}

// *Timer Interrupt Handler (Triggers Every 20ms)*
void TPM0_IRQHandler(void) {
    TPM0->SC |= 0x80;  // Clear Interrupt Flag
    
}

void Timer_Init(void) {
    SIM->SCGC6 |= 0x01000000;  // Enable TPM0 clock
    SIM->SOPT2 |= 0x01000000;  // Select MCGFLLCLK (48MHz)

    TPM0->SC = 0;  // Disable timer during setup
    TPM0->MOD = 960000 - 1;  // *20ms delay (48MHz / 50Hz)*

    TPM0->SC = 0x80 | 0x08;  // Enable Timer Overflow Interrupt + Clock
    
    NVIC_EnableIRQ(TPM0_IRQn);  // Enable Timer Interrupt
}

int main(void) 
{
    int i = 0;
    SIM->SOPT2 = 0x04000000;
    SIM->SOPT5 = 0x00000000;
    SIM->SCGC4 |= 0x00000400;
    SIM->SCGC5 |= 0x00003f00;
    SIM->SCGC6 |= 0x08000000;

    PORTB->PCR[0] |= 0x00000000;
    ADC0->SC1[0] |= 0x00000008;
    ADC0->CFG1 |= 0x00000000;
    PORTA->PCR[1] |= 0x00000200;
    PORTA->PCR[2] |= 0x00000200;

    GPIOB->PDDR |= 0xffffffff;
    GPIOB->PDOR |= 0x000000ff;

    uint32_t b;
    char buffer[10];

    // Configure UART0
    UART0->BDL = 0x89;
    UART0->C2 = 0x0C;
    UART0->BDH = 0x00;

    __enable_irq();  // Enable global interrupts
    Timer_Init();  // Initialize Timer Interrupt

    while(1) 
    { 
        ADC0->SC1[0] = 0x00000008;  // Start ADC conversion
        
        while(!(ADC0->SC1[0] & 0x80))  // Wait for conversion to complete
        {
            __NOP();
        }
        
        b = ADC0->R[0];  // Read ADC result

        // Convert ADC value to string
        sprintf(buffer, "%d\n", b);

        // Send the string via UART
        UART0_SendString(buffer);
    }
}

