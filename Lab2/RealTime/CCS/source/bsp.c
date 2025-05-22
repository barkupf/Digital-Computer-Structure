#include  "../header/bsp_msp430x2xx.h"    // private library - BSP layer, for personal kit
//#include  "../header/bsp_msp430x4xx.h"    // private library - BSP layer, for lab kit

//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;			 // Stop WDT
  
  // Switches Setup					 // SW0
  SWsArrPortSel &= ~0x01;            // I/O
  SWsArrPortDir &= ~0x01;            // Input

  // PushButtons Setup				 // PB0,PB1,PB2
  PBsArrPortSel &= ~0x07;            // I/O
  PBsArrPortDir &= ~0x07;            // Input
  PBsArrIntEdgeSel |= 0x03;  	     // pull-up mode
  PBsArrIntEdgeSel &= ~0x04;         // pull-down mode
  PBsArrIntEn |= 0x07;
  PBsArrIntPend &= ~0xFF;            // clear pending interrupts
                                     // PB3
  PBsArrPortSel3 &= ~0x02;           // I/O
  PBsArrPortDir3 &= ~0x02;           // Input
  PBsArrIntEdgeSel3 &= ~0x02;        // pull-down mode
  PBsArrIntEn3 |= 0x02;
  PBsArrIntPend3 &= ~0x02;            // clear pending interrupts
  
  // Buzzer Setup
  BuzzerArrPortDir |= 0x04;			// P2.2 Output compare - '1'
  BuzzerArrPortSel |= 0x04;         // P2.2 Select = '1'
  BuzzerArrPort    &= ~0x04;        // P2.2 out = '0'

  _BIS_SR(GIE);                      // enable interrupts globally
}                             
//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void TIMERconfig(void){
	
	// Initial configuration of Timers - put them on hold, enable&disable (incl. IE) upon state entrance
	TimerA1_Dir &= ~0x10; // P2.4 set to Input
	TimerA1_Sel |= 0x10; // P2.4 'select' set to 1 to set as Timer A
	
	// State 1
	TA1CTL = TASSEL_2 + TACLR; // SMCLK input, cleared current value
	TA1CCTL2 = CM_1 + SCS + CAP; // Capture on rising edge, synchronous capture, capture mode
	
	// State 2
	TA0CTL = TASSEL_2 + ID_3 + TACLR; // SMCLK input divided by 8, cleared current value
	TA0CCR0 = 0x8FFF;

	// State 3
	TA1CCTL1 = OUTMOD_0;
}
//------------------------------------------------------------------------------------- 
//            ADC congiguration 
//-------------------------------------------------------------------------------------
void ADCconfig(void){
	
	ADC10CTL0 &= ~ENC;
	ADC10CTL0 = SREF_0 + ADC10SHT_2; // V_R+=Vcc & V_R-=Vss, Sample&hold time = 16 x ADC10CLKs, Turn on, Enable interrupts
	ADC10CTL1 = INCH_3 + ADC10SSEL_3;	// Input channel A3(P1.3), ADC10CLK = SMCLK
	ADC10AE0 |= BIT3;
}              

//------------------------------------------------------------------------------------- 
//            LCD configuration
//-------------------------------------------------------------------------------------

//******************************************************************
// send a command to the LCD
//******************************************************************
void lcd_cmd(unsigned char c){
  /* Sends a command to the LCD (using LCD_DATA_WRITE as output port)
  // Using 4 bit-mode, it first sets the 4 MSBs then the 4 LSBs
  // The LCD_DATA_WRITE is used as 4-bits-long (rest are kept as-is) */
  
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	if (LCD_MODE == FOURBIT_MODE)
	{
		LCD_DATA_WRITE &= ~OUTPUT_DATA;// clear bits before new write
                LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
		lcd_strobe();
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
    		LCD_DATA_WRITE |= (c & (0x0F)) << LCD_DATA_OFFSET;
		lcd_strobe();
	}
	else
	{
		LCD_DATA_WRITE = c;
		lcd_strobe();
	}
}
//******************************************************************
// send data to the LCD
//******************************************************************
void lcd_data(unsigned char c){
        
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	LCD_DATA_WRITE &= ~OUTPUT_DATA;       
	LCD_RS(1);
	if (LCD_MODE == FOURBIT_MODE)
	{
    		LCD_DATA_WRITE &= ~OUTPUT_DATA;
                LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;  
		lcd_strobe();		
                LCD_DATA_WRITE &= (0xF0 << LCD_DATA_OFFSET) | (0xF0 >> 8 - LCD_DATA_OFFSET);
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
		LCD_DATA_WRITE |= (c & 0x0F) << LCD_DATA_OFFSET; 
		lcd_strobe();
	}
	else
	{
		LCD_DATA_WRITE = c;
		lcd_strobe();
	}
          
	LCD_RS(0);   
}
//******************************************************************
// write a string of chars to the LCD
//******************************************************************
void lcd_puts(unsigned char* s){
  
	while(*s) //when the array of characters reaches the NULL character (00), breaks
		lcd_data(*s++);
}
//******************************************************************
// initialize the LCD
//******************************************************************
void lcd_init(){
  
	char init_value;

	if (LCD_MODE == FOURBIT_MODE) init_value = 0x3 << LCD_DATA_OFFSET;
        else init_value = 0x3F;
	LCD_CTRL_SEL &= ~0xE0;
	LCD_RS_DIR(OUTPUT_PIN); // output mode for all RS+EN+RW
	LCD_EN_DIR(OUTPUT_PIN);
	LCD_RW_DIR(OUTPUT_PIN);
	LCD_DATA_DIR |= OUTPUT_DATA; // output mode for 4 "data" bits
	LCD_RS(0); // "data contains instruction code"
	LCD_EN(0); // enable signal = 0 (LCD transition when 1->0)
	LCD_RW(0); // write mode
        
	DelayMs(15);
    
	LCD_DATA_WRITE &= ~OUTPUT_DATA; // data channel to 0x0
	LCD_DATA_WRITE |= init_value;	// data channel to 4'b0011
	lcd_strobe();					// update screen & advance to next 'matrix'
	DelayMs(5);						
	LCD_DATA_WRITE &= ~OUTPUT_DATA;	// data channel to 4'b0000
	LCD_DATA_WRITE |= init_value;	// data channel to 4'b0011
	lcd_strobe();					// ....
	DelayUs(200);					// 200 Microsecond delay
	LCD_DATA_WRITE &= ~OUTPUT_DATA; // data channel to 4'b0000
	LCD_DATA_WRITE |= init_value;	// data channel to 4'b0011
	lcd_strobe();					// ....
	
	if (LCD_MODE == FOURBIT_MODE)
	{
		LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h
		LCD_DATA_WRITE &= ~OUTPUT_DATA;
		LCD_DATA_WRITE |= 0x2 << LCD_DATA_OFFSET; // Set 4-bit mode
		lcd_strobe();
		lcd_cmd(0x28); // Function Set - configuartion of screen
	}
	else lcd_function_set; // 8bit,two lines,5x10 dots 
	
	cursor_on;
	lcd_clear;
	lcd_entry_mode; //Entry Mode
	lcd_goto(0);//Initialize DDRAM address to zero
	lcd_home; // move cursor to start (defined in header)
}
//******************************************************************
// Delay usec functions
//******************************************************************
void DelayUs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--)
            __no_operation();
}
//******************************************************************
// Delay msec functions
//******************************************************************
void DelayMs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) DelayUs(1000); // tha command asm("nop") takes raphly 1usec
	
}
//******************************************************************
// lcd strobe functions
//******************************************************************
void lcd_strobe(){
  LCD_EN(1);
  __no_operation();
  __no_operation();
  LCD_EN(0);
}

           
             

 
             
             
            
  

