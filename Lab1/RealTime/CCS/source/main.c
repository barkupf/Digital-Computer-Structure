#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer
#include <string.h>

enum FSMstate state;
enum SYSmode lpm_mode;

void main(void){
  
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sel_pwm = 1;
  sysConfig();
  strcpy(name, "Rotem Arbiv");
  
  int leds_state1 = 1;
  int leds_state2 = 1;
  int op = 1;
  int* pleds_state1 = &leds_state1;
  int* pleds_state2 = &leds_state2;

 // char* name_to_print = &name;

  while(1){
	switch(state){
	  case state0: // Idel, sleep
	    printmaine2LEDs(0x0000);
        enterLPM(lpm_mode);
		break;
		 
	  case state1: // Leds counting binary, PB0
		SubAdd_leds(pleds_state1, op, 52350);// need to check that it 0.5s
		op = (-1) * op;         // Change direction of the counting
		state = state0;         // When finish go back to sleep
		enable_interrupts();
		break;
		 
	  case state2:  // Leds from right to left, PB1
		Shift_leds(pleds_state2, 52350); // need to check that it 0.5s
		state = state0;         // When finish go back to sleep
		enable_interrupts();
		break;
		

	  case state3:  // PWM, PB2
	    printmaine2LEDs(0x0000); // LEDs are not involved
	    PWM_Pram(sel_pwm);
	    break;

	  case state4: // Print name
	    PrintStr(name , 26175); // 250 ms delay
        state = state0;         // When finish go back to sleep
        enable_interrupts();
	    break;
	}
  }
}
  
  
  
  
  
  
