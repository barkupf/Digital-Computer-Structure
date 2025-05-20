#ifndef _api_H_
#define _api_H_

#include  "../header/halGPIO.h"     // private library - HAL layer


extern void printSWs2LEDs(void);
extern void printmaine2LEDs(char ch);
extern void printArr2SWs(char Arr[], int size, unsigned int rate);
extern void Shift_leds(int* pleds_state2, unsigned int rate);
extern void SubAdd_leds(int* pleds_state1, int op, unsigned int rate);
extern void PWM_Pram();

extern void PrintStr(char str[] , unsigned int delay_ms);

#endif







