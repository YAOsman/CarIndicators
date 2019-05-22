#include "TIF.h"
#include "Main.h"
#include "SSD.h"
#include "sEOS.h"


/* TIF_Update period */
#define TIF_PERIOD_MS   (20)

/* TIF blink ON and OFF time */
#define TIF_ON_TIME_MS  (200)
#define TIF_OFF_TIME_MS (300)

/* TIF module current state */
static tTIF_Command TIF_state;

/* Counter for ON/OFF time */
static tWord TIF_Last_Blink_Counter_MS;

/* Initializes TIF as off */
/* Parameters: None */
/* Returns: None */
void TIF_Init(void)
{
    TIF_state=TIF_OFF;
    TIF_Last_Blink_Counter_MS=0;
}

/* Updates TIF blinking, should be called every TIF_PERIOD_MS */
/* Parameters: None */
/* Returns: None */
void TIF_Update(void)
{
    //LEFT state
    if(TIF_state==TIF_LEFT){
    TIF_Last_Blink_Counter_MS+=TICK_MS;
    if(SSD_GetState(SSD_LEFT)==SSD_ON && TIF_Last_Blink_Counter_MS<=TIF_ON_TIME_MS)
    {

        SSD_Command(SSD_LEFT,SSD_ON);
        if((TIF_Last_Blink_Counter_MS+TICK_MS)>=TIF_ON_TIME_MS)
        {
            SSD_Command(SSD_LEFT,SSD_OFF);
            TIF_Last_Blink_Counter_MS=0;
        }

    }
    else if (SSD_GetState(SSD_LEFT)==SSD_OFF && TIF_Last_Blink_Counter_MS<=TIF_OFF_TIME_MS)
    {
        SSD_Command(SSD_LEFT,SSD_OFF);
        if((TIF_Last_Blink_Counter_MS+TICK_MS)>=TIF_OFF_TIME_MS)
        {
            SSD_Command(SSD_LEFT,SSD_ON);
            TIF_Last_Blink_Counter_MS=0;
        }
    }
    }
    //RIGHT STATE
    else if(TIF_state==TIF_RIGHT)
    {
    TIF_Last_Blink_Counter_MS+=TICK_MS;
    if(SSD_GetState(SSD_RIGHT)==SSD_ON && TIF_Last_Blink_Counter_MS<=TIF_ON_TIME_MS)
    {

        SSD_Command(SSD_RIGHT,SSD_ON);
        if((TIF_Last_Blink_Counter_MS+TICK_MS)>=TIF_ON_TIME_MS)
        {
            SSD_Command(SSD_RIGHT,SSD_OFF);
            TIF_Last_Blink_Counter_MS=0;
        }

    }
    else if (SSD_GetState(SSD_RIGHT)==SSD_OFF && TIF_Last_Blink_Counter_MS<=TIF_OFF_TIME_MS)
    {
        SSD_Command(SSD_RIGHT,SSD_OFF);
        if((TIF_Last_Blink_Counter_MS+TICK_MS)>=TIF_OFF_TIME_MS)
        {
            SSD_Command(SSD_RIGHT,SSD_ON);
            TIF_Last_Blink_Counter_MS=0;
        }
    }
    }
    //IDLE STATE
    else if (TIF_state==TIF_OFF)
   {
    TIF_Last_Blink_Counter_MS+=TICK_MS;
    if(SSD_GetState(SSD_LEFT)==SSD_ON && TIF_Last_Blink_Counter_MS<=TIF_ON_TIME_MS)
    {

        SSD_Command(SSD_LEFT,SSD_ON);
        SSD_Command(SSD_RIGHT,SSD_ON);
        if((TIF_Last_Blink_Counter_MS+TICK_MS)>=TIF_ON_TIME_MS)
        {
            SSD_Command(SSD_LEFT,SSD_OFF);
            SSD_Command(SSD_RIGHT,SSD_OFF);
            TIF_Last_Blink_Counter_MS=0;
        }

    }
    else if (SSD_GetState(SSD_LEFT)==SSD_OFF && TIF_Last_Blink_Counter_MS<=TIF_OFF_TIME_MS)
    {
        SSD_Command(SSD_LEFT,SSD_OFF);
        SSD_Command(SSD_RIGHT,SSD_OFF);
        if((TIF_Last_Blink_Counter_MS+TICK_MS)>=TIF_OFF_TIME_MS)
        {
            SSD_Command(SSD_LEFT,SSD_ON);
             SSD_Command(SSD_RIGHT,SSD_ON);
            TIF_Last_Blink_Counter_MS=0;
        }
    }
    }
}

/* Turns TIF LEFT/RIGHT/OFF */
/* Parameters:
 * command - LEFT/RIGHT/OFF command
 */
/* Returns: None */
void TIF_Command(tTIF_Command command)
{
    TIF_state=command;
}
