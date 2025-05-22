# FRDM-KL25Z Embedded C Projects

This repository contains a collection of embedded C programs developed for the [FRDM-KL25Z](https://www.nxp.com/design/development-boards/freedom-development-boards/freedom-development-platform-for-kinetis-kl2x-mcus:FRDM-KL25Z) microcontroller board. These programs demonstrate the use of core features such as ADC (Analog-to-Digital Conversion), UART communication, GPIO control, PWM generation, timers, and interrupt handling. Each file name indicates its core functionality.

## File Descriptions

- **ADC_UART_using_interrupts.c**  
  Reads analog input using ADC and sends the result over UART using interrupts for asynchronous communication.

- **ADC_output_in_SSD.c**  
  Displays the analog input value (from ADC) on a 7-segment display.

- **ADC_to_UART.c**  
  Converts analog input values using ADC and transmits them over UART in a polling-based implementation.

- **Fading_led.c**  
  Implements PWM to gradually fade an LED in and out.

- **LED_PWM_using-Timer-Interrupts.c**  
  Controls LED brightness using PWM, generated through timer interrupts for better timing precision.

- **Seven_segment_display.c**  
  Demonstrates control of a 7-segment display to show digits or characters.

- **Turning_On_led.c**  
  A basic GPIO program to turn an LED on or off using a microcontroller pin.

- **UART_ADC_using_Timer.c**  
  Integrates UART and ADC functionality using a timer to trigger ADC sampling at regular intervals.

- **UART_in_oscilloscope.c**  
  Sends waveform or sample values through UART to be visualized on an oscilloscope or serial plotter
  
- **exp.c**  
  A comprehensive elevator controller program handling floor requests, direction logic, and emergency states. Integrates interrupts and GPIO interactions.

## How to Use

Each file is self-contained and can be compiled and flashed using standard ARM development tools such as:
- MCUXpresso IDE
- Keil µVision
-Make sure to configure the clock, port pins, and interrupts according to your hardware setup.

## Requirements

- FRDM-KL25Z Board  
- USB Debug Probe (OpenSDA interface or external debugger)   

## License

This project is open-source under the MIT License.

---
