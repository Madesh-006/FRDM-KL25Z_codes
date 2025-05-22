//#include "max_heap.h"
//#include "min_heap.h"
//#include "system_MKL25Z4.h"
//#include "MKL25Z4.h"


//int min_heap[15];
//int max_heap[15];
//int flag_moving=0;
//int blink_state=0;
//int active_digit=0;
//int curr_floor =0;
//int destination_floor =0;
//int emergency =0;
//enum Flag { Up,Down,Waiting};
//enum Flag state=Up;
//enum Flag prev_state=Waiting;

//void display(int32_t x) {
//    static const uint32_t patterns[] = {
//        0x00000C00, // 0
//        0x00000CF0, // 1
//        0x00000848, // 2
//        0x00000B66, // 3
//        0x000008B0, // 4
//        0x00000821  // 5
//    };

//    flag_moving = 0;
//    if (x >= 0 && x < 6)
//        GPIOC_PDOR = patterns[x];
//    else
//        GPIOC_PDOR = 0xFFFFFFFF;
//}
//////////////////////////////////////////display with blinking 

////void display_moving(int floor) {
////    
////    active_digit = floor;
////}
/////////////////////////////////////// turning on/off leds 


//void turn_on(int floor) {
//	 GPIOB_PDOR |= (1 << floor);
//	
//		if((floor== 0) |(floor== 1) |(floor== 2 )|(floor== 3 )){
//			GPIOB_PDOR |= (1 << floor);
//	  }		
//		else {GPIOB_PDOR |= (1 << (floor+4));}
//}



//void turn_off(int floor) {
//		
//   if((floor== 0) |(floor== 1) |(floor== 2 )|(floor== 3 )){
//			GPIOB_PTOR |= (1<<floor);
//	}		
//	else {GPIOB_PTOR |= (1 << (floor+4));}
//}

///////////////////////////////////////////////////dealys for t seconds

//void delay(int t) {//
//    for (volatile int i = 0; i < t*1000000; i++) __NOP();
//}

////verified turn_on, turn_off,delay and interupts 
/////////////////////////////////////////////////function that i never used --no point of its existence just like YOU 
//void idle(void) {
//    while (state==Waiting) {
//        __NOP();
//    }
//}
///////////////////////////////////////////////all the initialisations


//void init_timer(void) {
//    SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
//    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);

//    TPM0_SC = 0;
//    TPM0_MOD = 30000;
//    TPM0_SC = TPM_SC_PS(7) | TPM_SC_TOIE_MASK | TPM_SC_CMOD(1);

//    NVIC_EnableIRQ(TPM0_IRQn);
//}



//void init_PORTC(void) {
//    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

//    PORTC_PCR0 = 0x00000100;
//    PORTC_PCR3 = 0x00000100;
//    PORTC_PCR4 = 0x00000100;
//    PORTC_PCR5 = 0x00000100;
//    PORTC_PCR6 = 0x00000100;
//    PORTC_PCR7 = 0x00000100;
//    PORTC_PCR10 = 0x00000100;
//    PORTC_PCR11 = 0x00000100;

//    GPIOC_PDDR = 0xFFFFFFFF;
//}

//void init_pins(void) {
//		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
//    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

//		PORTA_PCR1 |= (0xA01 <<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
//		GPIOA_PDDR |= (0<<1);
//	
//    for (int i = 0; i <= 6; i++) {
//        PORTD->PCR[i] = 0xA0103;
//    }

//    GPIOD_PDDR &= ~0x7F; // Set D0-D6 as input
//}

//void init_PORTB(void) {
//		
//    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

//    PORTB_PCR0 = 0x100;
//    PORTB_PCR1 = 0x100;
//    PORTB_PCR2 = 0x100;
//    PORTB_PCR3 = 0x100;
//    PORTB_PCR8 = 0x100;
//    PORTB_PCR9 = 0x100;
//    PORTB_PCR10 = 0x100;

//    GPIOB_PDDR |= 0x070F; // Set pins as output
//}

////////////////////////////////////////////////////////////////////////////Interupt handlers 
//void add_floor(int floor){
//	if(state==Up){
//		if(floor>curr_floor){
//			insert_min(min_heap,floor);
//		}
//		else {insert_max(max_heap,floor);}
//	}
//	if(state==Down){
//		if(floor<curr_floor){
//			insert_max(max_heap,floor);
//		}
//		else{insert_min(min_heap,floor);}
//	}	

//}

//void PORTA_IRQHandler(){
//	
//	if (!(GPIOA_PDIR & (1<<1))){
//			if (PORTA_ISFR & 0x2) {
//			if (emergency ==1){
//				emergency=0;
//				state=prev_state;
//				
//			}
//			else{
//				emergency=1;
//				prev_state=state;
//				state=Waiting;
//				display(curr_floor);
//			}
//		}
//		PORTA_ISFR |= 0x2;
//		
//	}
//}
//void PORTD_IRQHandler(){
//	
//	if (!(GPIOD_PDIR & (1<<0))){
//		add_floor(0);
//		turn_on(0);
//		PORTD_ISFR |= (1<<0);
//	}
//	else if (!(GPIOD_PDIR & (1<<1))){
//		add_floor(1);
//		turn_on(1);
//		PORTD_ISFR |= (1<<1);
//	}
//	else if (!(GPIOD_PDIR & (1<<2))){
//		add_floor(2);		
//		turn_on(2);
//		PORTD_ISFR |= (1<<2);
//	}
//	else if (!(GPIOD_PDIR & (1<<3))){
//		add_floor(3);	
//		turn_on(3);
//		PORTD_ISFR |= (1<<3);
//	}
//	else if (!(GPIOD_PDIR & (1<<4))){
//		add_floor(4);	
//		turn_on(4);
//		PORTD_ISFR |= (1<<4);
//	}
//	
//	else if (!(GPIOD_PDIR & (1<<5))){
//		add_floor(5);	
//		turn_on(5);
//		PORTD_ISFR |= (1<<5);
//	}
//	
//}

////void TPM0_IRQHandler(void) {
////    TPM0_SC |= TPM_SC_TOF_MASK;
////    if (state!=Waiting) {
////        if (blink_state == 0) {
////            GPIOC_PDOR = 0xFFFFFFFF;
////            blink_state = 1;
////        } else {
////            display(active_digit);
////            blink_state = 0;
////        }
////    }
////}


/////////////////////////////////////////////////////////////

//int main(void) {


//    init_PORTC();
//    init_timer();
//    init_PORTB();
//    init_pins();
//    NVIC_EnableIRQ(PORTD_IRQn);
//		NVIC_EnableIRQ(PORTA_IRQn);
//		NVIC_EnableIRQ(TPM0_IRQn);





//    while (1) {
//        if (curr_floor == 5) state = Down;
//        if (curr_floor == 0) state = Up;
//				if(state==Up){destination_floor=min_heap[0];}
//				if(state==Down){destination_floor=max_heap[0];}
//				if(state==Waiting){idle();}
//				//display_moving(curr_floor);
//        if (state==Up) {
//					if(curr_floor==destination_floor){
//						display(curr_floor);
//						turn_off(curr_floor);
//						int del=pop_min(min_heap);
//						delay(5);
//						if (size_min==0){
//							if(size_max!=0){
//								state=Down;
//								
//							}else {
//										state=Waiting;}
//						}
//						
//						delay(5);
//						curr_floor+=1;
//					}
//				if(state==Down){
//					if(curr_floor==destination_floor){
//						display(curr_floor);
//						turn_off(curr_floor);
//						int del2=pop_max(max_heap);
//						delay(5);
//						if(size_max==0){
//							if(size_min!=0){
//								state=Up;
//							}else{
//								state=Waiting;
//							}
//						}
//						
//						delay(5);
//						curr_floor-=1;
//					}
//				
//				
//				}
//		
//}
//}
//}
///////////////////////////////////////////////////////////////////////////////
///
#include "MKL25Z4.h"
#include <stdbool.h>

// Define the max size for our heaps
#define MAX_HEAP_SIZE 15

// Heap structures and variables
int min_heap[MAX_HEAP_SIZE]; // For up direction requests
int max_heap[MAX_HEAP_SIZE]; // For down direction requests
int size_min = 0;
int size_max = 0;

// Elevator state variables
int curr_floor = 0;
int destination_floor = 0;
int emergency = 0;
int blink_state = 0;
int active_digit=0;
int blink_display=0;
//bool display_blinking = false;

// State management enums
typedef enum {
    UP,
    DOWN,
    WAITING
} ElevatorState;

ElevatorState state = WAITING;
ElevatorState prev_state = WAITING;

// Function prototypes
void display(int floor);
void turn_on(int floor);
void turn_off(int floor);
void delay(int t);
void add_floor(int floor);
void init_timer(void);
void init_PORTC(void);
void init_PORTB(void);
void init_pins(void);

// Min heap operations
void swap_min(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_min(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap_min(&arr[i], &arr[smallest]);
        heapify_min(arr, n, smallest);
    }
}

void insert_min(int arr[], int val) {
    if (size_min >= MAX_HEAP_SIZE)
        return;

    // Insert new value at the end
    arr[size_min] = val;
    size_min++;
    
    // Fix min heap property
    for (int i = size_min / 2 - 1; i >= 0; i--) {
        heapify_min(arr, size_min, i);
    }
}

int pop_min(int arr[]) {
    if (size_min <= 0)
        return -1;
    
    // Store the root and remove it
    int root = arr[0];
    arr[0] = arr[size_min - 1];
    size_min--;
    
    // Fix min heap property
    heapify_min(arr, size_min, 0);
    
    return root;
}

// Max heap operations
void swap_max(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_max(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap_max(&arr[i], &arr[largest]);
        heapify_max(arr, n, largest);
    }
}

void insert_max(int arr[], int val) {
    if (size_max >= MAX_HEAP_SIZE)
        return;
    
    // Insert new value at the end
    arr[size_max] = val;
    size_max++;
    
    // Fix max heap property
    for (int i = size_max / 2 - 1; i >= 0; i--) {
        heapify_max(arr, size_max, i);
    }
}

int pop_max(int arr[]) {
    if (size_max <= 0)
        return -1;
    
    // Store the root and remove it
    int root = arr[0];
    arr[0] = arr[size_max - 1];
    size_max--;
    
    // Fix max heap property
    heapify_max(arr, size_max, 0);
    
    return root;
}

// Display function for 7-segment display
void display(int floor) {
    static const uint32_t patterns[] = {
        0x00000C00, // 0
        0x00000CF0, // 1
        0x00000848, // 2
        0x00000B66, // 3
        0x000008B0, // 4
        0x00000821  // 5
    };

    blink_display=0;
    if (floor >= 0 && floor < 6)
        GPIOC->PDOR = patterns[floor];
    else
        GPIOC->PDOR = 0xFFFFFFFF;
}

// Display with blinking effect for moving elevator
void display_moving(int floor) {
   // display_blinking = true;
    active_digit=floor;
		blink_display=1;
}

// LED control functions
void turn_on(int floor) {
    if (floor >= 0 && floor <= 3) {
        GPIOB->PDOR |= (1 << floor);
    } else if (floor >= 4 && floor <= 5) {
        GPIOB->PDOR |= (1 << (floor + 4));
    }
}

void turn_off(int floor) {
    if (floor >= 0 && floor <= 3) {
        GPIOB->PDOR &= ~(1 << floor);
    } else if (floor >= 4 && floor <= 5) {
        GPIOB->PDOR &= ~(1 << (floor + 4));
    }
}

// Delay function
void delay(int t) {
    for (volatile int i = 0; i < t * 1000000; i++) {
        __NOP();
    }
}

// Idle function - wait until state changes from WAITING
void idle(void) {
    while (state == WAITING) {
        __NOP();
    }
}

// Add floor request to appropriate heap
void add_floor(int floor) {
    // Don't add if it's the current floor
    if (floor == curr_floor) {
        return;
    }
    
    // Add floor to appropriate heap based on direction
    if (state == UP) {
        if (floor > curr_floor) {
            insert_min(min_heap, floor);
        } else {
            insert_max(max_heap, floor);
        }
    } else if (state == DOWN) {
        if (floor < curr_floor) {
            insert_max(max_heap, floor);
        } else {
            insert_min(min_heap, floor);
        }
    } else { // WAITING state
        if (floor > curr_floor) {
            insert_min(min_heap, floor);
            state = UP;
        } else {
            insert_max(max_heap, floor);
            state = DOWN;
        }
    }
}

// Initializations
void init_timer(void) {
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

    TPM0->SC = 0;
    TPM0->MOD = 30000;
    TPM0->SC = TPM_SC_PS(7) | TPM_SC_TOIE_MASK | TPM_SC_CMOD(1);

    NVIC_EnableIRQ(TPM0_IRQn);
}

void init_PORTC(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    PORTC->PCR[0] = PORT_PCR_MUX(1);
    PORTC->PCR[3] = PORT_PCR_MUX(1);
    PORTC->PCR[4] = PORT_PCR_MUX(1);
    PORTC->PCR[5] = PORT_PCR_MUX(1);
    PORTC->PCR[6] = PORT_PCR_MUX(1);
    PORTC->PCR[7] = PORT_PCR_MUX(1);
    PORTC->PCR[10] = PORT_PCR_MUX(1);
    PORTC->PCR[11] = PORT_PCR_MUX(1);

    GPIOC->PDDR = 0xFFFFFFFF; // Set all as output
}

void init_PORTB(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

    PORTB->PCR[0] = PORT_PCR_MUX(1);
    PORTB->PCR[1] = PORT_PCR_MUX(1);
    PORTB->PCR[2] = PORT_PCR_MUX(1);
    PORTB->PCR[3] = PORT_PCR_MUX(1);
    PORTB->PCR[8] = PORT_PCR_MUX(1);
    PORTB->PCR[9] = PORT_PCR_MUX(1);
    PORTB->PCR[10] = PORT_PCR_MUX(1);

    GPIOB->PDDR |= 0x070F; // Set pins as output
}

void init_pins(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

    // Emergency button on PORTA1 - input with interrupt
    PORTA->PCR[1] = PORT_PCR_MUX(1) | PORT_PCR_IRQC(0xA) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    GPIOA->PDDR &= ~(1 << 1); // Input
    
    // Floor buttons on PORTD0-5
    for (int i = 0; i <= 5; i++) {
        PORTD->PCR[i] = PORT_PCR_MUX(1) | PORT_PCR_IRQC(0xA) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    }
    GPIOD->PDDR &= ~0x3F; // Set D0-D5 as input
}

// Interrupt Handlers

// Emergency button handler
void PORTA_IRQHandler(void) {
    if (PORTA->ISFR & (1 << 1)) {
        if (emergency == 1) {
            emergency = 0;
            state = prev_state;
        } else {
            emergency = 1;
            prev_state = state;
            state = WAITING;
            display(curr_floor);
        }
        PORTA->ISFR = (1 << 1); // Clear interrupt flag
    }
}
// Floor button handler
void PORTD_IRQHandler(void) {
    for (int i = 0; i <= 5; i++) {
        if (PORTD->ISFR & (1 << i)) {
            add_floor(i);
            turn_on(i);
            PORTD->ISFR = (1 << i); // Clear interrupt flag
        }
    }
}

// Timer interrupt for blinking display
void TPM0_IRQHandler(void) {
     
			
			 if(state!=WAITING ){
					if (blink_state == 0) {
							GPIOC->PDOR = 0xFFFFFFFF; // Turn off display
							blink_state = 1;
					} else {
							display(active_digit); // Show current floor
							blink_state = 0;
					}
				}
		TPM0->SC |= TPM_SC_TOF_MASK;// Clear timer overflow flag
}

// Main function
int main(void) {
    // Initialize all peripherals
    init_PORTC();
    init_PORTB();
    init_pins();
    init_timer();
    
    // Enable interrupts
    NVIC_EnableIRQ(PORTD_IRQn);
    NVIC_EnableIRQ(PORTA_IRQn);
    NVIC_EnableIRQ(TPM0_IRQn);
    
    // Initial display
    display(curr_floor);
    
    while (1) {
				
        // Emergency check
        if (emergency) {
						display(curr_floor);
						delay(7);
						state=prev_state;// Skip elevator operation if in emergency mode
        }
        
        // If waiting, check if there are pending requests
        if (state == WAITING) {
						display(curr_floor);
            if (size_min > 0) {
                state = UP;
            } else if (size_max > 0) {
                state = DOWN;
            } else {
                idle(); // Wait for input
                continue;
            }
        }
        
        // Update destination based on current direction
        if (state == UP) {
						
            if (size_min > 0) {
                destination_floor = min_heap[0];
            } else if (size_max > 0) {
                state = DOWN;
                destination_floor = max_heap[0];
            } else {
                state = WAITING;
                continue;
            }
        } else if (state == DOWN) {
						
            if (size_max > 0) {
                destination_floor = max_heap[0];
            } else if (size_min > 0) {
                state = UP;
                destination_floor = min_heap[0];
            } else {
                state = WAITING;
                continue;
            }
        }
        
        // Display movement indication
        
        // Move elevator based on current state
        if (state == UP) {
            if (curr_floor < destination_floor) {
                delay(6); // Simulate movement time
                curr_floor++;
                display_moving(curr_floor);
            } else if (curr_floor == destination_floor) {
                // Arrived at destination
								
                state=WAITING;
                display(curr_floor);
								delay(5);	
								state=UP;
                turn_off(curr_floor);
                pop_min(min_heap); // Remove current destination
                //delay(5); // Wait at floor
                
                // Check if we should change direction
                if (size_min == 0) {
                    if (size_max > 0) {
                        state = DOWN;
                    } else {
                        state = WAITING;
                    }
                }
            }
        } else if (state == DOWN) {
            if (curr_floor > destination_floor) {
                delay(6); // Simulate movement time
                curr_floor--;
                display_moving(curr_floor);
            } else if (curr_floor == destination_floor) {
                // Arrived at destination
								
								state=WAITING;
                display(curr_floor);
								delay(5);	
								state=DOWN;
                turn_off(curr_floor);
                pop_max(max_heap); // Remove current destination
                 // Wait at floor
                
                // Check if we should change direction
                if (size_max == 0) {
                    if (size_min > 0) {
                        state = UP;
                    } else {
                        state = WAITING;
                    }
                }
            }
        }
    }
}
