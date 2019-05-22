#include "Button.h"
#include "Main.h"
#include "Port.h"
#include "sEOS.h"

/* BTN_Update period */
#define BTN_PERIOD_MS   (20)

/* Number of samples per button */
#define N_SAMPLES      (3)

#define N_BUTTONS      (3)

/* Buttons voltage level */
#define BTN_PRESSED_LEVEL       (0)
#define BTN_NOT_PRESSED_LEVEL   (1)



/* Button info: samples, state and press time */
typedef struct
{
    tByte btn_samples[N_SAMPLES];
    tBTN_State btn_state;
    tLong btn_press_time_MS;
}tBTN_Info;

/* Buttons info */
static tBTN_Info BTNs_Info[N_BUTTONS];

/* Initializes system buttons as inputs */
/* Parameters: None */
/* Returns: None */
void BTN_Init(void)
{
    tByte x;
    GPIO_INIT_PORTPIN(HAZZARD_BTN_DDR, HAZZARD_BTN_PIN, GPIO_INPUT_DDR);
    GPIO_INIT_PORTPIN(STEP_UP_BTN_DDR, STEP_UP_BTN_PIN, GPIO_INPUT_DDR);
    GPIO_INIT_PORTPIN(STEP_DOWN_BTN_DDR, STEP_DOWN_BTN_PIN, GPIO_INPUT_DDR);

    for(x=0;x<N_BUTTONS;x++)
    {
        BTNs_Info[x].btn_press_time_MS=0;
        BTNs_Info[x].btn_state=BTN_RELEASED;
    }
}

/* Updates system buttons states, should be called every BTN_PERIOD_MS */
/* Parameters: None */
/* Returns: None */
void BTN_Update(void)
{
    tByte i;
    static tWord BTN_counter = 0;

    BTN_counter+= TICK_MS;
    if (BTN_counter != BTN_PERIOD_MS)
    {
        return;
    }
    BTN_counter = 0;

    for( i=0;i<N_BUTTONS;i++){
        if((PORTB<<(i+1))==BTN_PRESSED_LEVEL)
        {
            BTNs_Info[i].btn_press_time_MS+=TICK_MS;
            BTNs_Info[i].btn_samples[0]=BTNs_Info[i].btn_samples[1];
            BTNs_Info[i].btn_samples[1]=BTNs_Info[i].btn_samples[2];
            BTNs_Info[i].btn_samples[2]=BTN_PRESSED_LEVEL;
            BTNs_Info[i].btn_state=BTN_ComputeState(BTNs_Info[i].btn_samples[0],BTNs_Info[i].btn_samples[1],BTNs_Info[i].btn_samples[2]);
        }
        else
        {
          BTNs_Info[i].btn_press_time_MS+=TICK_MS;
           BTNs_Info[i].btn_samples[0]=BTNs_Info[i].btn_samples[1];
            BTNs_Info[i].btn_samples[1]=BTNs_Info[i].btn_samples[2];
            BTNs_Info[i].btn_samples[2]=BTN_NOT_PRESSED_LEVEL;
            BTNs_Info[i].btn_state=BTN_ComputeState(BTNs_Info[i].btn_samples[0],BTNs_Info[i].btn_samples[1],BTNs_Info[i].btn_samples[2]);

        }
    }
}

/* Returns selected button state */
/* Parameters:
 * btn - Button to get its state
 */
/* Returns: Button state  */
tBTN_State BTN_GetState(tBTN btn)
{
    return BTNs_Info[btn].btn_state;
}

/* Returns selected button press time */
/* Parameters:
 * btn - Button to get its press time
 */
/* Returns: Button press time  */
tLong BTN_GetPressTime(tBTN btn)
{
    return BTNs_Info[btn].btn_press_time_MS;
}

tBTN_State BTN_ComputeState(tByte oldest, tByte middle, tByte newest)
{
    if(middle==BTN_NOT_PRESSED_LEVEL && newest==BTN_NOT_PRESSED_LEVEL)
        return BTN_RELEASED;
    else if(oldest== BTN_NOT_PRESSED_LEVEL && newest==BTN_PRESSED_LEVEL)
        return BTN_PRE_PRESSED;
    else if(middle==BTN_PRESSED_LEVEL && newest==BTN_PRESSED_LEVEL)
        return BTN_PRESSED;
    else if(oldest==BTN_PRESSED_LEVEL && newest==BTN_NOT_PRESSED_LEVEL)
        return BTN_PRE_RELEASED;
    else
        return 0;
}
