#include "../../../Main.h"
#include "../../../SSD.h"

/* Configuration Word */
static tWord __at(0x2007) CONFIG = _HS_OSC & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CP_OFF;

void DELAY_LOOP_Wait(const unsigned int DELAY_MS);

void main(void)
{
    /* Call SSD_Command before initialization */
    SSD_Command(SSD_LEFT, SSD_ON);

    /* Call SSD_GetState before initialization */
    SSD_GetState(SSD_LEFT);

    /* Call SSD_Init */
    SSD_Init();

    /* Call SSD_Command after initialization to toggle SSDs */
    while (1)
    {
        /* Call SSD_GetState after initialization */
        SSD_GetState(SSD_LEFT);
        SSD_GetState(SSD_RIGHT);

        /* Call SSD_Command after initialization to toggle SSDs */
        SSD_Command(SSD_LEFT, SSD_ON);
        SSD_Command(SSD_RIGHT, SSD_ON);
        DELAY_LOOP_Wait(1000);

        /* Call SSD_GetState after initialization */
        SSD_GetState(SSD_LEFT);
        SSD_GetState(SSD_RIGHT);

        /* Call SSD_Command after initialization to toggle SSDs */
        SSD_Command(SSD_LEFT, SSD_OFF);
        SSD_Command(SSD_RIGHT, SSD_OFF);
        DELAY_LOOP_Wait(1000);

        /* Robustness tests */
        /* Call SSD_Command with wrong parameters */
        SSD_Command(10, SSD_OFF);
        SSD_Command(SSD_RIGHT, 6);

        /* Call SSD_GetState with wrong parameters */
        SSD_GetState(5);
    }

}

void DELAY_LOOP_Wait(const unsigned int DELAY_MS){
    unsigned int x, y;

    for (x = 0; x <= DELAY_MS; x++){
        for (y = 0; y <= 120; y++);
    }
}
