#include "Main.h"
#include "Button.h"
#include "SSD.h"
#include "HIF.h"
#include "TIF.h"
#include "Controller.h"
#include "sEOS.h"

/* Configuration Word */
static tWord __at(0x2007) CONFIG = _HS_OSC & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CP_OFF;


/* Initializes system and gives control to sEOS */
/* Parameters: None */
/* Returns: None  */
void main(void)
{
    /* Modules initialization */
    BTN_Init();
    SSD_Init();
    HIF_Init();
    TIF_Init();
    Controller_Init();
    sEOS_Init_Timer0(TICK_MS);

    /* Go to sleep mode */
    while (1){
        sEOS_Go_To_Sleep();
    }
}
