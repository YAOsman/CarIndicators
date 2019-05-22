#ifndef __PORT_H__
#define __PORT_H__

#include "Main.h"

#define GPIO_PORT_B         (PORTB)
#define GPIO_PORT_B_DDR     (TRISB)
#define GPIO_PORT_D         (PORTD)
#define GPIO_PORT_D_DDR     (TRISD)

#define GPIO_PIN0            (0)
#define GPIO_PIN1            (1)
#define GPIO_PIN2            (2)
#define GPIO_PIN3            (3)
#define GPIO_PIN4            (4)
#define GPIO_PIN5            (5)
#define GPIO_PIN6            (6)
#define GPIO_PIN7            (7)

#define GPIO_INPUT_DDR       (1)
#define GPIO_OUTPUT_DDR      (0)

#define GPIO_INIT_PORT(GPIO_PORT_DDR, GPIO_PORT_DIRECTION)               do{\
                                                                            GPIO_PORT_DDR = GPIO_PORT_DIRECTION;\
                                                                        }while(0)

#define GPIO_INIT_PORTPIN(GPIO_PORT_DDR, GPIO_PIN, GPIO_PORT_DIRECTION) do{\
                                                                            GPIO_PORT_DDR = GPIO_PORT_DDR & (~(1<<GPIO_PIN));\
                                                                            GPIO_PORT_DDR = GPIO_PORT_DDR | (GPIO_PORT_DIRECTION<<GPIO_PIN);\
                                                                        }while(0)


#define GPIO_WRITE_PORT(GPIO_PORT, GPIO_VALUE)                          do{\
                                                                            GPIO_PORT = GPIO_VALUE;\
                                                                        }while(0)

#define GPIO_READ_PORT(GPIO_PORT)                                       (GPIO_PORT)

#define GPIO_WRITE_PORTPIN(GPIO_PORT, GPIO_PIN, GPIO_VALUE)             do{\
                                                                            GPIO_PORT = GPIO_PORT & (~(1<<GPIO_PIN));\
                                                                            GPIO_PORT = GPIO_PORT | (GPIO_VALUE<<GPIO_PIN);\
                                                                        }while(0)

#define GPIO_READ_PORTPIN(GPIO_PORT, GPIO_PIN)                          ((GPIO_PORT & (1<<GPIO_PIN)) >> GPIO_PIN)


#define SSD_DATA_PORT           GPIO_PORT_D
#define SSD_DATA_PORT_DDR       GPIO_PORT_D_DDR

#define SSD_CONTROL_PORT        GPIO_PORT_B
#define SSD_CONTROL_DDR         GPIO_PORT_B_DDR
#define SSD_LEFT_CONTROL_PIN    GPIO_PIN5
#define SSD_RIGHT_CONTROL_PIN   GPIO_PIN4

#define STEP_DOWN_BTN_PORT      GPIO_PORT_B
#define STEP_DOWN_BTN_DDR       GPIO_PORT_B_DDR
#define STEP_DOWN_BTN_PIN       GPIO_PIN1

#define STEP_UP_BTN_PORT        GPIO_PORT_B
#define STEP_UP_BTN_DDR         GPIO_PORT_B_DDR
#define STEP_UP_BTN_PIN         GPIO_PIN2

#define HAZZARD_BTN_PORT        GPIO_PORT_B
#define HAZZARD_BTN_DDR         GPIO_PORT_B_DDR
#define HAZZARD_BTN_PIN         GPIO_PIN3


#endif // __PORT_H__
