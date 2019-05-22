#include "SSD.h"
#include "Port.h"

/* SSD display value when blinking */
#define SSD_VALUE   (0x7F)

/* Initializes SSD_LEFT and SSD_RIGHT and turns them OFF */
/* Parameters: None */
/* Returns: None */
void SSD_Init(void)
{
    //SET DIRECTION
    GPIO_INIT_PORTPIN(SSD_CONTROL_DDR, SSD_LEFT_CONTROL_PIN, GPIO_OUTPUT_DDR);
    GPIO_INIT_PORTPIN(SSD_CONTROL_DDR, SSD_RIGHT_CONTROL_PIN, GPIO_OUTPUT_DDR);
    SSD_DATA_PORT_DDR=GPIO_OUTPUT_DDR;
    //SET DATA
    GPIO_WRITE_PORTPIN(SSD_CONTROL_PORT, SSD_LEFT_CONTROL_PIN, 0);
    GPIO_WRITE_PORTPIN(SSD_CONTROL_PORT, SSD_RIGHT_CONTROL_PIN, 0);
    GPIO_WRITE_PORT(SSD_DATA_PORT,0);
}

/* Turns SSD_LEFT/SSD_RIGHT ON/OFF */
/* Parameters:
 * ssd - SSD_LEFT/SSD_RIGHT ssd
 * command - ON/OFF command
 */
/* Returns: None */
void SSD_Command(tSSD ssd, tSSD_Command command)
{
    switch (ssd)
    {
    case SSD_LEFT:
      //  GPIO_WRITE_PORTPIN(SSD_CONTROL_PORT,SSD_RIGHT_CONTROL_PIN , SSD_OFF);
        GPIO_WRITE_PORTPIN(SSD_CONTROL_PORT,SSD_LEFT_CONTROL_PIN , SSD_ON);
         if(command==0)
         {
             GPIO_WRITE_PORT(SSD_DATA_PORT,0);

         }
         else
         {
              GPIO_WRITE_PORT(SSD_DATA_PORT,SSD_VALUE);
         }
         break;
    case SSD_RIGHT:
       GPIO_WRITE_PORTPIN(SSD_CONTROL_PORT,SSD_RIGHT_CONTROL_PIN , SSD_ON);
    //    GPIO_WRITE_PORTPIN(SSD_CONTROL_PORT,SSD_LEFT_CONTROL_PIN , SSD_OFF);
         if(command==0)
         {
             GPIO_WRITE_PORT(SSD_DATA_PORT,0);

         }
         else
         {
              GPIO_WRITE_PORT(SSD_DATA_PORT,SSD_VALUE);
         }
        break;
    }
}

/* Returns ssd state */
/* Parameters:
 * ssd - SSD_LEFT/SSD_RIGHT ssd
 */
/* Returns: SSD state */
tSSD_Command SSD_GetState(tSSD ssd)
{
    if(ssd==SSD_LEFT)
    {
        return SSD_LEFT_CONTROL_PIN;
    }
    else if(ssd==SSD_RIGHT)
    {
        return SSD_RIGHT_CONTROL_PIN;
    }
}
