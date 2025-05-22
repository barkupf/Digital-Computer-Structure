#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer
//---------------------------------------------------------------------
//				State 1 Logic
//---------------------------------------------------------------------
void state1Logic(){
	unsigned int freq;
	char freq2print[6];
	unsigned int lastfreq;
	
	lcd_home;
	print2LCD("fin=");
	moveRightLCD(5);
	print2LCD("Hz");
	cursor_off;
	lastfreq = 0;
	TIMERS1start();
	disable_interrupts();
	while (1) {
		startCount = 0;
		endCount = 0;
		enableCaptureState1();
		__bis_SR_register(LPM0_bits + GIE);
		if (state != state1){		// Check state didn't change
			TIMERS1stop();			// If did, stop timer
			break;
		}
		if (startCount == 0 && endCount == 0){ // Check that somting interesting happened
			continue;
		}
		if ((endCount - startCount > lastfreq + 1 )||(endCount - startCount < lastfreq - 1)){
		    freq = (SMCLK_freq/(endCount-startCount));  // Calcullate the current frequancy
		    IntToStr(freq2print, 6, (unsigned int)freq);    // If changed update the string to the new frequancy
            lcd_home;
            moveRightLCD(4);
            print2LCD(freq2print);
            cursor_off;
            lastfreq = endCount-startCount;
		}
	}
}
//---------------------------------------------------------------------
//				State 2 Logic
//---------------------------------------------------------------------
void state2Logic(){
	unsigned char time2print[6] = {'0','0',':','0','0'}; // Value of the timer MM:SS
    lcd_home; // Set LCD's cursor at the start
    print2LCD(time2print); // When first entry display 00:00
    TIMERS2start(); // Start timer in Up-Down mode
    while (1) {
        lcd_home;   // Set LCD's cursor at the start
        cursor_off;
        enterLPM(lpm_mode); // Go to sleep
        if (state != state2){	// Check if state had changed
			TIMERS2stop();	// If changed turn off state 2 timer (to save power)
			break;
        }
        enterLPM(lpm_mode); // First interrupt, go back to sleep
        if (state != state2){	// Check if state had changed
			TIMERS2stop(); // If changed turn off state 2 timer (to save power)
			break;
        }
        if (readSW0() == 0x01) { // If didn't changed then check enable is '1'
            update_time(time2print);	// If enable is '1' then update the time value
            print2LCD(time2print);
       }
    }
}
//---------------------------------------------------------------------
//				State 3 Logic
//---------------------------------------------------------------------
void state3Logic(){
	unsigned int Nadc = 0;
	unsigned int NumtoUpdate = 0;
	
	TIMERS3start();
	while (1) {
	    ADCStart();
		 __bis_SR_register(LPM0_bits + GIE);
		if (state != state3){		// Check state didn't change
			TIMERS3stop();			// If did, stop timer
			ADCStop();              // Stop ADC
			break;
		}
		Nadc = getNADC();
		NumtoUpdate = 1111 - multy_byM(Nadc);
		TimerPWMUpdateFreq(NumtoUpdate);
	}
	
}
//---------------------------------------------------------------------
//              State 4 Logic
//---------------------------------------------------------------------
void state4Logic(){
    unsigned int n = 1111;

    TIMERS4start(); // Start timer A1
    TIMERS2start(); // Start timer A0 in Up-Down mode

    while (state == state4) {
        TimerPWMUpdateDuty(n>>2);
        enterLPM(lpm_mode);     // Go to sleep
        if (state != state4){   // Check if state had changed
            break;
        }
        TimerPWMUpdateDuty(n>>1);
        enterLPM(lpm_mode);     // Go to sleep
        if (state != state4){   // Check if state had changed
            break;
        }
        TimerPWMUpdateDuty(n - (n>>2));
        enterLPM(lpm_mode);     // Go to sleep
    }
    TIMERS2stop();  // Stop timer A0
    TIMERS4stop();  // Stop timer A1
}
//---------------------------------------------------------------------
//				Update Routine For Time Value
//---------------------------------------------------------------------	
void update_time (unsigned char* arr){
	// arr = M M : S S
    if (arr[4] < '9'){			// If lower sec < 9, only lower sec should be updated
        arr[4] = arr[4] + 1;
        return;
    }
    arr[4] = '0'; 			    // Else, set lower sec to '0' and check higher sec
    if (arr[3] < '5'){			// If higher sec < 5, only higher sec should be updated 
        arr[3] = arr[3] + 1;
        return;
    }
    arr[3] = '0'; 				// Else, set higher sec also to '0' and check lower minutes
    if (arr[1] < '9'){			// If lower minutes < 9, only lower minutes should be updated  
        arr[1] = arr[1] + 1;
        return;
    }
    arr[1] = '0'; 				// Else, set lower minutes also to '0' and check higher minutes
    if (arr[0] < '5'){			// If higher minutes < 9 add 1
        arr[0] = arr[0] + 1;
        return;
    }
    arr[0] = '0'; 				// Else, we reached to the highest limit then set to '0' and restart 
}	
//---------------------------------------------------------------------
//				Update Rutine For Time Value
//---------------------------------------------------------------------	
void IntToStr(char* str,int strLen , int num){
  int i;
  
  str[strLen-1] = '\0';
  for (i = strLen - 2;i >= 0; i--){
      if (num == 0)
          str[i] = ' ';
      else{
          str[i] = num%10 + '0';
          num = num/10;
      }
  }
}
//---------------------------------------------------------------------
//				Find Fout
//---------------------------------------------------------------------	
unsigned int multy_byM(unsigned int n){
    /* 	We would like to multiply by 0.625 but we can't use float so:
		we use Q format - Q4.4 to present 0.625 = 0000101 = 0x05 which means:
		n*0.625 = n*(0x05)_Q = n/2 + n/8 so we did this: */
    unsigned int tmp = n;
    unsigned int result = 0;
    tmp = tmp >> 1; 		// n/2
    result += tmp; 			// n/2
    tmp = tmp >> 2; 		// (n/2)/4 = n/8
    result += tmp;			// n/2 + n/8
    return result;	
}
