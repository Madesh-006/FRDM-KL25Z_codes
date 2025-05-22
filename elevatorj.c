#include "MKL25Z4.h"
#include <stdio.h>
#define ONE_SECOND_DELAY 1000000
void delay(int t);
void enable_buttons_leds(void);
void add_floor(int i);
void swap(int*a ,int*b);
void Clear_Led(int floor);
int DownIsEmpty(void);
int UpIsEmpty(void);
void initialize_display(void);
void display_floor(int f);
void toggle_comms(void);
void initialize_timer(void);
void initialize_direction_display(void);
void display_direction(void);
#define MAX_SIZE 6
typedef struct {
	int data[MAX_SIZE];
	int size;	
} UpQueue;

typedef struct{
	int data[MAX_SIZE];
	int size;
}DownQueue;
void pushUpQueue(UpQueue* q,int d);
void pushDownQueue(DownQueue* q,int d);
int popUpQueue(UpQueue* q);
int popDownQueue(DownQueue* q);

enum Flag { Up,Down,Waiting};
enum Flag flag=Waiting;
UpQueue upvalues = {.size =0};
DownQueue downvalues ={.size=0};

int current_floor =0;
int destination_floor =0;

int emergency =0;
enum Flag prev_state = Waiting;

int floor_wait =5*ONE_SECOND_DELAY;
int floor_climb = 10*ONE_SECOND_DELAY;
int main(void){
	SIM_SCGC5 |= (1<<9) | (1<<11) | (1<<12); //Enables port A and port D and port C and D takes care of all interrupts and C takes care of output to leds
	enable_buttons_leds();
	initialize_display();
	display_floor(0);
	initialize_direction_display();
	display_direction();
	initialize_timer();
	NVIC_EnableIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);
while (1){
        if (flag==Up){
                if (current_floor == destination_floor){
										Clear_Led(current_floor);
										flag=Waiting;
                    delay(floor_wait);
                    if (UpIsEmpty() && DownIsEmpty()){
                        flag=Waiting;
												display_direction();
                    }
                    else if (UpIsEmpty() && !DownIsEmpty()){
                        flag=Down;
												display_direction();
                        destination_floor = popDownQueue(&downvalues);
                    }
                    else{
											flag=Up;
                        destination_floor = popUpQueue(&upvalues);
                    }
                }
                else{
                    current_floor +=1;
                    delay(floor_climb);
                    display_floor(current_floor);
                }
    
        }
        else if (flag== Down){
        
                    if (current_floor == destination_floor){
										Clear_Led(current_floor);
										flag=Waiting;
                    delay(floor_wait);
                    if (UpIsEmpty() && DownIsEmpty()){
                        flag=Waiting;
												display_direction();
                    }
                    else if (!UpIsEmpty() && DownIsEmpty()){
                        flag=Up;
                        display_direction();
                        destination_floor = popUpQueue(&upvalues);
                    }
                    else{
											flag=Down;
                        destination_floor = popDownQueue(&downvalues);
                    }
                }
                else{
                    current_floor -=1;
                    delay(floor_climb);
                    display_floor(current_floor);
                }
        
        }
        else {
            //When i am waiting do nothing since your waiting for input
            __NOP();
        }	
            
        }
}

void PORTA_IRQHandler(){
	if (!(GPIOA_PDIR & 0x2)){
		//Make an emergency button
			if (PORTA_ISFR & 0x2) {
			if (emergency ==1){
				emergency=0;
				flag=prev_state;
				display_direction();
			}
			else{
				emergency=1;
				prev_state=flag;
				flag=Waiting;
				display_direction();
				display_floor(current_floor);
			}
		}
		PORTA_ISFR |= 0x2;
		
	}
}


void PORTD_IRQHandler(){
	if (!(GPIOD_PDIR & (1<<0))){
		add_floor(0);
		PORTD_ISFR |= (1<<0);
	}
	else if (!(GPIOD_PDIR & (1<<1))){
		add_floor(1);
		PORTD_ISFR |= (1<<1);
	}
	else if (!(GPIOD_PDIR & (1<<2))){
		add_floor(2);		
		PORTD_ISFR |= (1<<2);
	}
	else if (!(GPIOD_PDIR & (1<<3))){
		add_floor(3);		
		PORTD_ISFR |= (1<<3);
	}
	else if (!(GPIOD_PDIR & (1<<4))){
		add_floor(4);		
		PORTD_ISFR |= (1<<4);
	}
	else if (!(GPIOD_PDIR & (1<<5))){
		add_floor(5);		
		PORTD_ISFR |= (1<<5);
	}	
	
}


void enable_buttons_leds(void){
	PORTD_PCR0 |= (0xA01 <<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOD_PDDR |= (0<<0);
	PORTC_PCR0 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOC_PDDR |= (1<<0);
	

	PORTD_PCR1 |= (0xA01 <<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOD_PDDR |= (0<<1);
	PORTC_PCR1 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOC_PDDR |= (1<<1);
	
	PORTD_PCR2 |= (0xA01 <<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOD_PDDR |= (0<<2);
	PORTC_PCR2 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOC_PDDR |= (1<<2);
	
	PORTD_PCR3 |= (0xA01 <<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOD_PDDR |= (0<<3);
	PORTC_PCR3 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOC_PDDR |= (1<<3);

	PORTD_PCR4 |= (0xA01 <<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOD_PDDR |= (0<<4);
	PORTC_PCR4 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOC_PDDR |= (1<<4);

	PORTD_PCR5 |= (0xA01 <<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOD_PDDR |= (0<<5);
	PORTC_PCR5 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOC_PDDR |= (1<<5);
	

	PORTA_PCR1 |= (0xA01 <<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	GPIOA_PDDR |= (0<<1);
		
}

void initialize_display(void){
	SIM_SCGC5 |= (1<<13);
	PORTE_PCR0 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTE_PCR1 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTE_PCR2 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTE_PCR3 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTE_PCR4 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTE_PCR5 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTE_PCR20 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTE_PCR21 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTE_PCR22 |= (1<<8);
	GPIOE_PDDR |= (0x3F << 0) | (1<<20) | (1<<21) | (1<<22);
	GPIOE_PDOR |= (1<<22);
}
void display_floor(int f){

	switch (f){
		case 0:
			GPIOE_PDOR = (1<<20) | (1<<21)| (1<<22);
			break;
		case 1:
			GPIOE_PDOR = (1<<0) | (1<<5) | (1<<20) |(1<<4) | (1<<3) | (1<<21) | (1<<22);
			break;			
		case 2:
			GPIOE_PDOR = (1 <<2) | (1<<5) | (1<<21) | (1<<22);
			break;			
		case 3:
			GPIOE_PDOR = (1<<5) | (1<<4) | (1<<21) | (1<<22);
			break;
		case 4:
			GPIOE_PDOR =(1<<0) | (1<<3) | (1<<4) | (1<<21) | (1<<22);
			break;
		case 5:
			GPIOE_PDOR = (1<<1) | (1<<4) | (1<<21) | (1<<22);
			break;		
		default:
			GPIOE_PDOR = 0x0;		
	}
}

//For Up smaller values should be closer to the lower index
void pushUpQueue(UpQueue* q,int d){
	int temp=d;
	int t2;
 for (int i=0;i<q->size;i++){
	if (q->data[i] > temp){
		t2=q->data[i];
		q->data[i]=temp;
		temp=t2;
	} 
	else if (q->data[i] == temp) {
		return;
	}
 }
 q->data[q->size] = temp;
 q->size +=1;
}

//For down larger values should be at smalle index
void pushDownQueue(DownQueue* q,int d){
	int temp=d;
 for (int i=0;i<q->size;i++){
	if (q->data[i] < temp){
		swap(&temp,&(q->data[i]));
	} 
	else if (q->data[i] == temp) {
		return;
	}
 }
 q->data[q->size] = temp;
 q->size +=1;
}


int popUpQueue(UpQueue* q){
	int temp=q->data[0];
	for (int i=1; i<q->size;i++){
		q->data[i-1] = q->data[i];
	}
	q->size -=1;
	return temp;
}

int popDownQueue(DownQueue* q){
	int temp=q->data[0];
	for (int i=1; i<q->size;i++){
		q->data[i-1] = q->data[i];
	}
	q->size -=1;
	return temp;
}

void swap(int*a ,int*b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

void add_floor(int i){
	if (current_floor ==i){
	return;
	}
	GPIOC_PDOR |= (1<<i);
	if (flag == Up){
		if (i<current_floor){
			pushDownQueue(&downvalues,i);
		}
		else if(i==current_floor){
			if (i!=destination_floor ){
				pushUpQueue(&upvalues,destination_floor);
				destination_floor = i;
			}
		}
		else{
			if (i>destination_floor){
			pushUpQueue(&upvalues,i);
			}
			else if (i<destination_floor){
			pushUpQueue(&upvalues,destination_floor);
				destination_floor=i;
			}
		}
	}
	else if (flag==Down){
		
	if (i>current_floor){
			pushUpQueue(&upvalues,i);
		}
		else if(i==current_floor){
			if (i!=destination_floor ){
				pushDownQueue(&downvalues,destination_floor);
				destination_floor = i;
			}
		}
		else{
			if (i<destination_floor){
			pushDownQueue(&downvalues,i);
			}
			else if (i>destination_floor){
			pushDownQueue(&downvalues,destination_floor);
				destination_floor=i;
			}
		}	
		
		
	}
	else{
		destination_floor = i;
		if (i>current_floor){
			flag=Up;
		}
		else if (i<current_floor){
			flag=Down;
		}
	}
	
}


void Clear_Led(int floor){
	GPIOC_PTOR |= (1<<floor);
}


int UpIsEmpty(void){
 if (upvalues.size == 0){
 return 1;
 }
 return 0;
}

int DownIsEmpty(void){
 if (downvalues.size ==0){
	 return 1;
 }
 return 0;
}


void delay(int t){

for (int i=0;i<t;i++){
	__NOP();
}
}

void toggle_comms(void){
	GPIOE_PTOR |= (1<<22);
}

void initialize_timer(void){
	SIM_SCGC6 |= (1<<24);
	SIM_SOPT2 |= (1<<24);
	TPM0_SC |= TPM_SC_TOIE_MASK | (0xF <<0); 
	TPM0_MOD = 30000;

}

void TPM0_IRQHandler(void){
if (flag != Waiting){
	toggle_comms();
}
else{
		GPIOE_PDOR |= (1<<22);
}
	TPM0_SC  |= (1 <<7); 
}

void initialize_direction_display(void){

		SIM_SCGC5 |= (1<<10);
		PORTB_PCR0 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
		PORTB_PCR1 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
		PORTB_PCR2 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
		PORTB_PCR3 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
		PORTB_PCR8 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
		PORTB_PCR9 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
		PORTB_PCR10 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;	
		PORTB_PCR11 |= (1<<8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;	
		GPIOB_PDDR |= (0xF <<0) | (0xF <<8);
}

void display_direction(void){
	if (flag==Up){
		GPIOB_PDOR |= (1<<0)  | (1<<10) | (1<<11);
	}
	else if (flag==Down){
		GPIOB_PDOR |= (1<<10) | (1<<11);
	}
	else{
		GPIOB_PDOR |=  (1<<0) | (1<<3);
	}
}
