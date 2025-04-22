#include  "../header/bsp_msp430x2xx.h"    // private library - BSP layer, for personal kit
//#include  "../header/bsp_msp430x4xx.h"    // private library - BSP layer, for lab kit

//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   
  // LEDs 8-bit Array Port configuration
  LEDsArrPortSel &= ~0xFF;            // GPIO capability
  LEDsArrPortDir |= 0xFF;             // output
  LEDsArrPort = 0x00;				  // clear all LEDs
  
/*  // Switches Setup
  SWsArrPortSel &= ~0x0F;
  SWsArrPortDir &= ~0x0F;
*/
  // PushButtons Setup
  PBsArrPortSel &= ~0x0F;            // I/O
  PBsArrPortDir &= ~0x0F;            // input
  PBsArrIntEdgeSel |= 0x03;  	     // pull-up mode
  PBsArrIntEdgeSel &= ~0x0C;         // pull-down mode
  PBsArrIntEn |= 0x0F;
  PBsArrIntPend &= ~0x0F;            // clear pending interrupts
  
  // PWM Setup                         P2.7
  PWMArrPortSel &= ~0x80;           // I/O
  PWMArrPortDir |= 0x80;            // output


  _BIS_SR(GIE);                     // enable interrupts globally
}                             
//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void TIMERconfig(void){
	
	//write here timers congiguration code
} 
//------------------------------------------------------------------------------------- 
//            ADC congiguration 
//-------------------------------------------------------------------------------------
void ADCconfig(void){
	
	//write here ADC congiguration code
}              

           
             

 
             
             
            
  

