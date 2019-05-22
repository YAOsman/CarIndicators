#ifndef __TIF_H__
#define __TIF_H__

/* TIF commands */
typedef enum
{
    TIF_OFF,
    TIF_LEFT,
    TIF_RIGHT
}tTIF_Command;

/* TIF prototypes */
void TIF_Init(void);
void TIF_Update(void);
void TIF_Command(tTIF_Command command);

#endif // __TIF_H__
