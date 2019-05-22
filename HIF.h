#ifndef __HIF_H__
#define __HIF_H__

/* HIF commands */
typedef enum
{
    HIF_OFF,
    HIF_ON
}tHIF_Command;

/* HIF prototypes */
void HIF_Init(void);
void HIF_Update(void);
void HIF_Command(tHIF_Command command);

#endif // __HIF_H__
