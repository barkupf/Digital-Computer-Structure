#include  "../header/halGPIO.h"     // private library - HAL layer

//--------------------------------------------------------------------
//             System Configuration  
//--------------------------------------------------------------------
void sysConfig(void){ 
	GPIOconfig();
	TIMERconfig();
	ADCconfig();
	lcd_init();
}
//--------------------------------------------------------------------
//				Read value of 4-bit SWs array 
//--------------------------------------------------------------------
unsigned char readSW0(void){
	unsigned char ch;
	ch = SWsArrPort;
	ch &= SW0;     // mask the least bit for SW0
	return ch;
}
//---------------------------------------------------------------------
//              Print to LCD
//---------------------------------------------------------------------
void print2LCD(unsigned char * arr){
    lcd_puts(arr);
}
//---------------------------------------------------------------------
//              Clear LCD
//---------------------------------------------------------------------
void clearLCD(void){
    lcd_clear;
    cursor_off;
}
//---------------------------------------------------------------------
//              Move LCD Cursor To Right X Times
//---------------------------------------------------------------------
void moveRightLCD(int x){
    int i;
    for (i = 0; i < x; i++){
		lcd_cursor_right();
	}
}
//---------------------------------------------------------------------
//              Move LCD Cursor To Left X Times
//---------------------------------------------------------------------
void moveLeftLCD(int x){
    int i;
    for (i = 0; i < x; i++){
		lcd_cursor_left();
	}
}
//---------------------------------------------------------------------
//              Get N_ADC
//---------------------------------------------------------------------
unsigned int getNADC(void){
    return ADC10MEM;
}
//---------------------------------------------------------------------
//				Timer State 1
//---------------------------------------------------------------------
void TIMERS1start(void){
    TA1CTL |= MC_2 + TACLR;	// Clear the register and start in continuous mode
}
void TIMERS1stop(void){
	TA1CTL &= ~MC_3;		// Stop timer to save power
    TA1CCTL2 &= ~CCIE; 		// Disable envelope interrupts
    TA1CCTL1 = OUTMOD_0;    // Output mode OUT
}
void enableCaptureState1(void){
	TA1CCTL2 |= CCIE;		// Enable envelope interrupts
}
void disableCaptureState1(void){
	TA1CCTL2 &= ~CCIE;		// Disable envelope interrupts
}
//---------------------------------------------------------------------
//				Timer State 2
//---------------------------------------------------------------------
void TIMERS2start(void){
	TA0CCTL0 |= CCIE;
    TA0CTL |= MC_3 + TACLR;	// Clear the register and start in Up/Down mode
}
void TIMERS2stop(void){
	TA0CTL &= ~MC_3;		// Stop timer to save power
    TA0CCTL0 &= ~CCIE; 		// Disable envelope interrupts
}
//---------------------------------------------------------------------
//				Timer State 3
//---------------------------------------------------------------------
void TIMERS3start(void){
	TA1CTL |= MC_1 + TACLR;
	TA1CCTL1 = OUTMOD_7;
}
void TIMERS3stop(void){
	TA1CTL &= ~ MC_3;
	TA1CCTL1 = OUTMOD_0;
}
void TimerPWMUpdateFreq(unsigned int t){
	TA1CCR0 = t;
    TA1CCR1 = t >> 1; // t/2
}
//---------------------------------------------------------------------
//              Timer State 4
//---------------------------------------------------------------------
void TIMERS4start(void){
    TA1CTL |= MC_1 + TACLR;
    TA1CCTL1 = OUTMOD_7;
    TA1CCR0 = 1111;
}
void TIMERS4stop(void){
    TA1CTL &= ~ MC_3;
    TA1CCTL1 = OUTMOD_0;
}
void TimerPWMUpdateDuty(unsigned int d){
    TA1CCR1 = d;
}
//---------------------------------------------------------------------
//            ADC10
//---------------------------------------------------------------------
void ADCStart(void){
	ADC10CTL0 |= ENC + ADC10SC + ADC10ON + ADC10IE;
}	
void ADCStop(void){
	ADC10CTL0 &= ~ADC10ON;
	ADC10CTL0 &= ~ADC10IE;
}
//---------------------------------------------------------------------
//            Polling based Delay function
//---------------------------------------------------------------------
void delay(unsigned int t){  // t[msec]
	volatile unsigned int i;
	
	for(i=t; i>0; i--);
}
//---------------------------------------------------------------------
//            Enter from LPM0 mode
//---------------------------------------------------------------------
void enterLPM(unsigned char LPM_level){
	if (LPM_level == 0x00) 
	  _BIS_SR(LPM0_bits);     /* Enter Low Power Mode 0 */
        else if(LPM_level == 0x01) 
	  _BIS_SR(LPM1_bits);     /* Enter Low Power Mode 1 */
        else if(LPM_level == 0x02) 
	  _BIS_SR(LPM2_bits);     /* Enter Low Power Mode 2 */
	else if(LPM_level == 0x03) 
	  _BIS_SR(LPM3_bits);     /* Enter Low Power Mode 3 */
        else if(LPM_level == 0x04) 
	  _BIS_SR(LPM4_bits);     /* Enter Low Power Mode 4 */
}
//---------------------------------------------------------------------
//            Enable interrupts
//---------------------------------------------------------------------
void enable_interrupts(){
  _BIS_SR(GIE);
}
//---------------------------------------------------------------------
//            Disable interrupts
//---------------------------------------------------------------------
void disable_interrupts(){
  _BIC_SR(GIE);
}
//*********************************************************************
//            Port1 Interrupt Service Rotine
//*********************************************************************
#pragma vector=PORT1_VECTOR
  __interrupt void PBs_handler(void){
   
	delay(debounceVal);
//---------------------------------------------------------------------
//            selector of transition between states
//---------------------------------------------------------------------
	if(PBsArrIntPend & PB0){
	  state = state1;
	  PBsArrIntPend &= ~PB0;
	//  _BIC_SR_IRQ(GIE);
        }
	else if(PBsArrIntPend & PB1){
	  state = state2;
	  PBsArrIntPend &= ~PB1; 
	//  _BIC_SR_IRQ(GIE);
        }
	else if(PBsArrIntPend & PB2){ 
	  state = state3;
	  PBsArrIntPend &= ~PB2;
	//  _BIC_SR_IRQ(GIE);
        }
//---------------------------------------------------------------------
//            Exit from a given LPM 
//---------------------------------------------------------------------	
        switch(lpm_mode){
		case mode0:
		 LPM0_EXIT; // must be called from ISR only
		 break;
		 
		case mode1:
		 LPM1_EXIT; // must be called from ISR only
		 break;
		 
		case mode2:
		 LPM2_EXIT; // must be called from ISR only
		 break;
                 
                case mode3:
		 LPM3_EXIT; // must be called from ISR only
		 break;
                 
                case mode4:
		 LPM4_EXIT; // must be called from ISR only
		 break;
	}
        
}
//*********************************************************************
//            Port2 Interrupt Service Routine - switch & PB3
//*********************************************************************
  #pragma vector=PORT2_VECTOR
    __interrupt void SWs_handler(void){
		delay(debounceVal);
		if (SWsArrIntPend & SW0){ 		// SW0
			SWsArrIntPend &= ~SW0; 		// Turn off IFG
			__no_operation();
		}
		if(PBsArrIntPend3 & PB3){
		    state = state4;
		    PBsArrIntPend3 &= ~PB3;
		    LPM0_EXIT;
		}
	}
    /*
#pragma vector=PORT2_VECTOR
  __interrupt void PBs_handler(void){

    delay(debounceVal);
//---------------------------------------------------------------------
//            selector of transition between states
//---------------------------------------------------------------------
    if(PBsArrIntPend3 & PB3){
      state = state4;
      PBsArrIntPend3 &= ~PB3;
    //  _BIC_SR_IRQ(GIE);
        }
//---------------------------------------------------------------------
//            Exit from a given LPM
//---------------------------------------------------------------------
        switch(lpm_mode){
        case mode0:
         LPM0_EXIT; // must be called from ISR only
         break;

        case mode1:
         LPM1_EXIT; // must be called from ISR only
         break;

        case mode2:
         LPM2_EXIT; // must be called from ISR only
         break;

                case mode3:
         LPM3_EXIT; // must be called from ISR only
         break;

                case mode4:
         LPM4_EXIT; // must be called from ISR only
         break;
    }

}
*/
//*********************************************************************
//            TimerA1 Interrupt Service Routine
//*********************************************************************
// State 1 - TA_A1 Interrupt vector
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A1_VECTOR))) TIMER1_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{
	switch(TA1IV){
		case 0x02:
			break;
		case 0x04:
			if (s_or_e == 0){
				startCount = TA1CCR2;
				s_or_e = 1;
			}
			else{
				endCount = TA1CCR2;
				s_or_e = 0;
				TA1CCTL2 &= ~CCIE;
				__bic_SR_register_on_exit(LPM0_bits + GIE);
			}
			break;
			default:
				break;
	}	
}
//*********************************************************************
//            TimerA0 Interrupt Service Routine
//*********************************************************************
// State 2 - TA_A0 Interrupt vector
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER1_A0_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) TIMER1_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    LPM0_EXIT;                // Exit LPM0 on return to main
}
//*********************************************************************
//            ADC10 Interrupt Service Rotine
//*********************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
  //  __bic_SR_register_on_exit(LPM0_bits + GIE);
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
