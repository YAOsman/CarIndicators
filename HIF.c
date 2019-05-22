#include "HIF.h"
#include "Main.h"
#include "SSD.h"
#include "sEOS.h"


/* HIF_Update period */
#define HIF_PERIOD_MS   (20)

/* Hazzard blink ON and OFF time */
#define HAZZARD_ON_TIME_MS  (200)
#define HAZZARD_OFF_TIME_MS (400)

/* HIF module current state */
static tHIF_Command HIF_state;

/* Counter for ON/OFF time */
static tWord HIF_Last_Blink_Counter_MS;

/* Initializes HIF as off */
/* Parameters: None */
/* Returns: None */
void HIF_Init(void)
{

}

/* Updates HIF blinking, should be called every HIF_PERIOD_MS */
/* Parameters: None */
/* Returns: None */
void HIF_Update(void)
{
    
}

/* Turns HIF ON/OFF */
/* Parameters:
 * command - ON/OFF command
 */
/* Returns: None */
void HIF_Command(tHIF_Command command)
{
    
}
