#include "Controller.h"
#include "Main.h"
#include "HIF.h"
#include "TIF.h"
#include "Button.h"
#include "sEOS.h"

/* Controller_Update period */
#define CON_PERIOD_MS   (20)

/* Controller states */
typedef enum
{
    CON_IDLE,
    CON_LEFT,
    CON_RIGHT,
    CON_HAZZARD,
}tCON_State;

/* CON module current state */
static tCON_State CON_current_state;

/* CON module previous state */
static tCON_State CON_previous_state;

/* Local functions prototypes */
static void Controller_ProcesIdleState(tBTN_State STEP_DOWN_STATE,
                                       tBTN_State STEP_UP_STATE,
                                       tBTN_State HAZZARD_STATE);
static void Controller_ProcesLeftState(tBTN_State STEP_UP_STATE,
                                       tBTN_State HAZZARD_STATE);
static void Controller_ProcesRightState(tBTN_State STEP_DOWN_STATE,
                                       tBTN_State HAZZARD_STATE);
static void Controller_ProcesHazzardState(tBTN_State HAZZARD_STATE);

/* Initializes controller state machine */
/* Parameters: None */
/* Returns: None */
void Controller_Init(void)
{
    CON_previous_state=CON_IDLE;
    CON_current_state=CON_IDLE;
}

/* Updates state machine, should be called every CON_PERIOD_MS */
/* Parameters: None */
/* Returns: None */
void Controller_Update(void)
{
    static tWord CONT_counter = 0;

    CONT_counter+= TICK_MS;
    if (CONT_counter != CON_PERIOD_MS)
    {
        return;
    }
    CONT_counter = 0;
    if(CON_current_state==CON_HAZZARD)
    Controller_ProcesHazzardState(BTN_HAZZARD);
    else if(CON_current_state==CON_LEFT)
    Controller_ProcesLeftState(BTN_STEP_UP,BTN_HAZZARD);
    else if(CON_current_state==CON_RIGHT)
    Controller_ProcesRightState(BTN_STEP_DOWN,BTN_HAZZARD);
    else if(CON_current_state==CON_IDLE)
    Controller_ProcesIdleState(BTN_STEP_DOWN,BTN_STEP_UP,BTN_HAZZARD);
    if(CON_current_state==CON_HAZZARD)
    {
        HIF_Command(HIF_ON);
        TIF_Command(TIF_OFF);
    }
    else if(CON_current_state==CON_LEFT)
    {
        HIF_Command(HIF_OFF);
        TIF_Command(TIF_LEFT);
    }
    else if(CON_current_state==CON_RIGHT)
    {
        HIF_Command(HIF_OFF);
        TIF_Command(TIF_RIGHT);
    }
      else if(CON_current_state==CON_IDLE)
    {
        HIF_Command(HIF_OFF);
        TIF_Command(TIF_OFF);
    }

}

/* Idle state processing*/
/* Parameters:
 * STEP_DOWN_STATE - BTN_STEP_DOWN state
 * STEP_UP_STATE - BTN_STEP_UP state
 * HAZZARD_STATE - BTN_HAZZARD state
 */
/* Returns: None  */
static void Controller_ProcesIdleState(tBTN_State STEP_DOWN_STATE,
                                       tBTN_State STEP_UP_STATE,
                                       tBTN_State HAZZARD_STATE)
{

if(BTN_GetState(HAZZARD_STATE)==BTN_PRE_RELEASED && BTN_GetPressTime(HAZZARD_STATE)>=200)
{
    CON_previous_state=CON_current_state;
    CON_current_state=CON_HAZZARD;
}
else if(BTN_GetState(STEP_DOWN_STATE)==BTN_PRE_PRESSED && BTN_GetPressTime(STEP_DOWN_STATE)>=10)
{
    CON_previous_state=CON_current_state;
    CON_current_state=CON_LEFT;
}
else if(BTN_GetState(STEP_UP_STATE)==BTN_PRE_PRESSED && BTN_GetPressTime(STEP_UP_STATE)>=10)
{
    CON_previous_state=CON_current_state;
    CON_current_state=CON_RIGHT;
}

}

/* left state processing*/
/* Parameters:
 * STEP_UP_STATE - BTN_STEP_UP state
 * HAZZARD_STATE - BTN_HAZZARD state
 */
/* Returns: Button state  */
static void Controller_ProcesLeftState(tBTN_State STEP_UP_STATE,
                                       tBTN_State HAZZARD_STATE)
{
    if(BTN_GetState(HAZZARD_STATE)==BTN_PRE_RELEASED && BTN_GetPressTime(HAZZARD_STATE)>=200)
    {
    CON_previous_state=CON_current_state;
    CON_current_state=CON_HAZZARD;
    }
    else if(BTN_GetState(STEP_UP_STATE)==BTN_PRE_PRESSED && BTN_GetPressTime(STEP_UP_STATE)>=10)
    {
    CON_previous_state=CON_current_state;
    CON_current_state=CON_IDLE;
    }

}

/* Right state processing */
/* Parameters:
 * STEP_DOWN_STATE - BTN_STEP_DOWN state
 * HAZZARD_STATE - BTN_HAZZARD state
 */
/* Returns: None  */
static void Controller_ProcesRightState(tBTN_State STEP_DOWN_STATE,
                                       tBTN_State HAZZARD_STATE)
{
    if(BTN_GetState(HAZZARD_STATE)==BTN_PRE_RELEASED && BTN_GetPressTime(HAZZARD_STATE)>=200)
    {
    CON_previous_state=CON_current_state;
    CON_current_state=CON_HAZZARD;
    }
    else if(BTN_GetState(STEP_DOWN_STATE)==BTN_PRE_PRESSED && BTN_GetPressTime(STEP_DOWN_STATE)>=10)
    {
    CON_previous_state=CON_current_state;
    CON_current_state=CON_IDLE;
    }

}

/* Hazzard state processing*/
/* Parameters:
 * HAZZARD_STATE - BTN_HAZZARD state
 */
/* Returns: None  */
static void Controller_ProcesHazzardState(tBTN_State HAZZARD_STATE)
{
    if(BTN_GetState(HAZZARD_STATE)==BTN_PRE_RELEASED && BTN_GetPressTime(HAZZARD_STATE)>=200)
    {

    CON_current_state= CON_previous_state;
    CON_previous_state=HAZZARD_STATE;
    }
}
