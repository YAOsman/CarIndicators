#ifndef __SSD_H__
#define __SSD_H__

/* Types of SSD */
typedef enum
{
    SSD_LEFT,
    SSD_RIGHT
}tSSD;

/* SSD commands */
typedef enum
{
    SSD_OFF = 0,
    SSD_ON  = 1
}tSSD_Command;

/* SSD prototypes */
void SSD_Init(void);
void SSD_Command(tSSD ssd, tSSD_Command command);
tSSD_Command SSD_GetState(tSSD ssd);
#endif // __SSD_H__
