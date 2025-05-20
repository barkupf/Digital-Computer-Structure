#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer
#include <string.h>

enum FSMstate state;
enum SYSmode lpm_mode;

void main(void){
  
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  s_or_e = 0;
  sysConfig();
  
  while(1){
	switch(state){
		case state0: // Idel, sleep
		    clearLCD();
			enterLPM(lpm_mode);
			break;
		 
		case state1:	// Frequancy counter
			state1Logic();
			clearLCD();
			break;
	
		case state2:	// Seconds timer
		    state2Logic();
		    clearLCD();
			break;
		
		case state3:	// Buzzer
		    state3Logic();
			break;
	}
  }
}
  
  
  
  
  
  
