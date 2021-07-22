#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#include "fsl_gpio.h"

#define LED_GPIO     GPIO3
#define LED_GPIO_PIN (2U)

void bsp_led_init(void);
void bsp_led_ctl(char state);

#endif /* _BSP_LED_H_ */
