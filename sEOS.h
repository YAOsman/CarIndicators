#ifndef _sEOS_H__
#define _sEOS_H__
#include "Main.h"

// Modify code below
#define TICK_MS (20)

void sEOS_Init_Timer0(const tByte TICK);
void sEOS_Go_To_Sleep(void);
void sEOS_Timer0_ISR(void) __interrupt 0;

#endif // _sEOS_H__
