#ifndef _halGPIO_H_
#define _halGPIO_H_

#include  "../header/bsp_msp430x2xx.h"    // private library - BSP layer, for personal kit
//#include  "../header/bsp_msp430x4xx.h"    // private library - BSP layer, for lab kit
#include  "../header/app.h"    		// private library - APP layer


extern enum FSMstate state;   // global variable
extern enum SYSmode lpm_mode; // global variable

extern void sysConfig(void);
extern unsigned char readSW0(void);
extern void print2LCD(unsigned char * arr);
extern void clearLCD(void);
extern void moveRightLCD(int x);
extern void moveLeftLCD(int x);
extern unsigned int getNADC(void);
extern void delay(unsigned int);
extern void enterLPM(unsigned char);
extern void enable_interrupts();
extern void disable_interrupts();
extern void TIMERS1start(void);
extern void TIMERS1stop(void);
extern void enableCaptureState1(void);
extern void disableCaptureState1(void);
extern void TIMERS2start(void);
extern void TIMERS2stop(void);
extern void TIMERS3start(void);
extern void TIMERS3stop(void);
extern void TIMERS4start(void);
extern void TIMERS4stop(void);
extern void ADCStart(void);
extern void ADCStop(void);
extern void TimerPWMUpdateFreq(unsigned int t);
extern void TimerPWMUpdateDuty(unsigned int d);

extern __interrupt void PBs_handler(void);
extern __interrupt void SWs_handler(void);
extern __interrupt void TIMER1_A0_ISR (void);

#endif







