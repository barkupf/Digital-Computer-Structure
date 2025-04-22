#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer

//-------------------------------------------------------------
//            Print SWs value onto LEDs
//-------------------------------------------------------------
void printSWs2LEDs(void){
	unsigned char ch;
	
	ch = readSWs();
	print2LEDs(ch);
}
//-------------------------------------------------------------
//            Print main value onto LEDs
//-------------------------------------------------------------
void printmaine2LEDs(char ch){

    print2LEDs(ch);
}
//--------------------------------------------------------------------
//            Print array to LEDs array with rate of LEDs_SHOW_RATE
//--------------------------------------------------------------------            
void printArr2SWs(char Arr[], int size, unsigned int rate){
	unsigned int i;
	
	for(i=0; i<size; i++){
		print2LEDs(Arr[i]);
		delay(rate);
	}
}
//--------------------------------------------------------------------
//            Print LEDs from right to left
//--------------------------------------------------------------------
void Shift_leds(int* pleds_state2, unsigned int rate){
    unsigned int i;

    for(i=0; i<14; i++){        // Check time - need to work 7 sec
        print2LEDs(*pleds_state2);
        *pleds_state2 = (*pleds_state2 * 2) % 255;  // check this line for the correctness
        delay(rate);
    }
}
//--------------------------------------------------------------------
//            Print LEDs binary counting
//--------------------------------------------------------------------
void SubAdd_leds(int* pleds_state1, int op, unsigned int rate){
    unsigned int i;

    for(i=0; i<20; i++){
        print2LEDs(*pleds_state1);
        *pleds_state1 = (*pleds_state1 + op) % 255;  // check this line for the correctness
        delay(rate);
    }
}
//---------------------------------------------------------------------
//            PWM
//---------------------------------------------------------------------
void PWM_Pram(){
    unsigned int freq = 4;
    float dutyCycle = 0.75;
    float period_time = 1;
    unsigned int ton = 1;

    switch(sel_pwm){
        case 0:
            freq = 4;
            dutyCycle = 0.75;
            period_time = 92.0/freq;
            ton =  dutyCycle * period_time;
            break;
        case 1:
            freq = 2;
            dutyCycle = 0.25;
            period_time = 92.0/freq;
            ton =  dutyCycle * period_time;
            break;
    }

    pwm(period_time, ton, 0xFFFF);
}
