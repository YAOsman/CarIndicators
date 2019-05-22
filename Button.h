#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Main.h"

/* Valid press time before release */
#define VALID_HAZZARD_BTN_PRESS_TIME_MS (200)

/* Types of buttons */
typedef enum
{
    BTN_STEP_DOWN = 0,
    BTN_STEP_UP = 1,
    BTN_HAZZARD = 2
}tBTN;

/* Button states */
typedef enum
{
    BTN_RELEASED,
    BTN_PRE_PRESSED,
    BTN_PRESSED,
    BTN_PRE_RELEASED,
}tBTN_State;

/* BTN prototypes */

void BTN_Init(void);
void BTN_Update(void);
tBTN_State BTN_GetState(tBTN btn);
tLong BTN_GetPressTime(tBTN btn);
tBTN_State BTN_ComputeState(tByte oldest, tByte middle, tByte newest);
#endif // __BUTTON_H__
