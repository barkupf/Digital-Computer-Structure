#ifndef _api_H_
#define _api_H_

#include  "../header/halGPIO.h"     // private library - HAL layer

extern void state1Logic(void);
extern void state2Logic(void);
extern void state3Logic(void);
extern void update_time (unsigned char* arr);
extern void IntToStr(char* str,int strLen , int num);
extern unsigned int multy_byM(unsigned int x);
#endif







