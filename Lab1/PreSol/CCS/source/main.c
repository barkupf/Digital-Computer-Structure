#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

enum FSMstate state;
enum SYSmode lpm_mode;

void main(void){
  
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sel_pwm = 1;
  sysConfig();
  
  int leds_state1 = 1;
  int leds_state2 = 1;
  int op = 1;
  int* pleds_state1 = &leds_state1;
  int* pleds_state2 = &leds_state2;

  while(1){
	switch(state){
	  case state0: // Idel, sleep
	    printmaine2LEDs(0x0000);
        enterLPM(lpm_mode);
		break;
		 
	  case state1: // Leds counting binary, PB0
		disable_interrupts();
		SubAdd_leds(pleds_state1, op, 52350);// need to check that it 0.5s
		op = (-1) * op;         // Change direction of the counting
		state = state0;         // When finish go back to sleep
		enable_interrupts();
		break;
		 
	  case state2:  // Leds from right to left, PB1
		disable_interrupts();
		Shift_leds(pleds_state2, 52350); // need to check that it 0.5s
		state = state0;         // When finish go back to sleep
		enable_interrupts();
		break;
		

	  case state3:  // PWM, PB2
	    printmaine2LEDs(0x0000); // LEDs are not involved
	    PWM_Pram(sel_pwm);
	    break;
	}
  }
}
  
  
  
  
  
  
