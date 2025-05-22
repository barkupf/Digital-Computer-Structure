#ifndef _bsp_H_
#define _bsp_H_

#include  <msp430g2553.h>          // MSP430x2xx


#define   debounceVal      250
#define   LEDs_SHOW_RATE   0xFFFF  // 62_5ms

// Switches abstraction
#define SWsArrPort         P2IN
#define SWsArrPortDir      P2DIR
#define SWsArrPortSel      P2SEL
#define SWmask             0xF0
#define SWsArrIntPend      P2IFG
#define SW0                0x01

// PushButtons abstraction
#define PBsArrPort	       P1IN
#define PBsArrIntPend	   P1IFG 
#define PBsArrIntEn	       P1IE
#define PBsArrIntEdgeSel   P1IES
#define PBsArrPortSel      P1SEL 
#define PBsArrPortDir      P1DIR 
#define PB0                0x01
#define PB1                0x02
#define PB2                0x04
//#define PB3                0x08

// PushButtons BP3 abstraction
#define PBsArrPort3        P2IN
#define PBsArrIntPend3     P2IFG
#define PBsArrIntEn3       P2IE
#define PBsArrIntEdgeSel3  P2IES
#define PBsArrPortSel3     P2SEL
#define PBsArrPortDir3     P2DIR
#define PB3                0x02     // Connects to P2.1

// Buzzer  abstraction
#define BuzzerArrPort	   P2OUT
#define BuzzerArrPortDir   P2DIR
#define BuzzerArrPortSel   P2SEL

// Timer abstraction
#define TimerA1_Dir			P2DIR
#define TimerA1_Sel			P2SEL
#define SMCLK_freq          1114000 // 2^20 (measured 1.111~1.114Mhz)

// LCDs abstraction

// #define CHECKBUSY	1  // using this define, only if we want to read from LCD
#ifdef CHECKBUSY
    #define LCD_WAIT lcd_check_busy()
#else
    #define LCD_WAIT DelayMs(5)
#endif

/*----------------------------------------------------------
  CONFIG: change values according to your port pin selection
------------------------------------------------------------*/
#define LCD_CTRL_WRITE  P2OUT // LCD control lines connected to P2.5-P2.7
#define LCD_CTRL_DIR    P2DIR
#define LCD_CTRL_READ   P2IN
#define LCD_CTRL_SEL    P2SEL

#define LCD_EN(a)       (a ? (LCD_CTRL_WRITE |= 0x20) : (LCD_CTRL_WRITE &= ~0x20)) // P2.5 is lcd enable pin
#define LCD_EN_DIR(a)   (a ? (LCD_CTRL_DIR |= 0x20) : (LCD_CTRL_DIR &= ~0x20)) // P2.5 pin direction

#define LCD_RS(a)       (a ? (LCD_CTRL_WRITE |=0x40) : (LCD_CTRL_WRITE &=~0x40)) // P2.6 is lcd RS pin
#define LCD_RS_DIR(a)   (a ? (LCD_CTRL_DIR |= 0x40) : (LCD_CTRL_DIR &= ~0x40)) //P2.6, direction pin

#define LCD_RW(a)       (a ? (LCD_CTRL_WRITE |=0x80) : (LCD_CTRL_WRITE &=~0x80)) // P2.7 is lcd RW pin
#define LCD_RW_DIR(a)   (a ? (LCD_CTRL_DIR |=0x80) : (LCD_CTRL_DIR &=~0x80)) // P2.7 pin direction


#define LCD_DATA_OFFSET 0x04 	// Data pin selection offset for 4 bit mode, variable range is 0-4, default 0 - Px.0-3, no offset
#define LCD_DATA_WRITE  P1OUT   // Output port for the LCD screen
#define LCD_DATA_DIR    P1DIR
#define LCD_DATA_READ   P1IN
/*---------------------------------------------------------
  END CONFIG
-----------------------------------------------------------*/
#define FOURBIT_MODE    0x0
#define EIGHTBIT_MODE   0x1
#define LCD_MODE        FOURBIT_MODE

#define OUTPUT_PIN      1
#define INPUT_PIN       0
#define OUTPUT_DATA     (LCD_MODE ? 0xFF : (0x0F << LCD_DATA_OFFSET))
#define INPUT_DATA      0x00

#define LCD_STROBE_READ(value)  LCD_EN(1), \
                asm("nop"), asm("nop"), \
                value=LCD_DATA_READ, \
                LCD_EN(0)					// This is the trigger rutine in the tutorial

// Might come in handy, need to verify they are all suitable for 4-bit mode
#define lcd_cursor(x)       lcd_cmd(((x)&0x7F)|0x80)
#define lcd_clear           lcd_cmd(0x01)
#define lcd_putchar(x)      lcd_data(x)
#define lcd_goto(x)         lcd_cmd(0x80+(x))
#define lcd_cursor_right()  lcd_cmd(0x14)
#define lcd_cursor_left()   lcd_cmd(0x10)
#define lcd_display_shift() lcd_cmd(0x1C)
#define lcd_home            lcd_cmd(0x02)
#define cursor_off          lcd_cmd(0x0C)
#define cursor_on           lcd_cmd(0x0F)
#define lcd_function_set    lcd_cmd(0x3C) // 8bit,two lines,5x10 dots
#define lcd_new_line        lcd_cmd(0xC0)
#define lcd_entry_mode      lcd_cmd(0x6)


extern void GPIOconfig(void);
extern void TIMERconfig(void);
extern void ADCconfig(void);
extern void lcd_cmd(unsigned char c);
extern void lcd_data(unsigned char c);
extern void lcd_puts(unsigned char* s);
extern void lcd_init();
extern void DelayUs(unsigned int cnt);
extern void DelayMs(unsigned int cnt);
extern void lcd_strobe();


#endif



