#include "sEOS.h"
#include "Button.h"
#include "Controller.h"
#include "HIF.h"
#include "TIF.h"


static tByte TMR0_reload = 0;

void sEOS_Init_Timer0(const tByte TICK){

        /* Select Prescalar */
        PSA  = 0;

        /* Select Prescalar = 1/256 */
        PS0 = 1;
        PS1 = 1;
        PS2 = 1;

        /* Set initial value of timer */
        TMR0_reload = 256 - (TICK * 8);

        TMR0 = TMR0_reload;

        /* Start TMR 0 */
        T0IF = 0;
        T0CS = 0;

        /* Enable TMR0 interrupts */
        T0IE = 1;
        GIE = 1;

}

void sEOS_Go_To_Sleep(void){
    if (T0CS == 1){ // External clock source
        __asm
        SLEEP
        __endasm;
    } else { // Internal clock course
        // Do nothing
    }
}

void sEOS_Timer0_ISR(void) __interrupt 0{

    // Add your code here

    Controller_Update();
    HIF_Update();
    TIF_Update();
    BTN_Update();
    // End of your code
    TMR0 = TMR0_reload;
    T0IF = 0;

}
