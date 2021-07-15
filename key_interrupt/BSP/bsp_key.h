#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "fsl_gpio.h"

/* KEY1 <---> PMIC_STBY_REQ */
#define KEY1_GPIO               GPIO4
#define KEY1_GPIO_PIN           (20U)
#define KEY1_GPIO_IRQ           GPIO4_Combined_16_31_IRQn
#define KEY1_GPIO_IRQ_HANDLER   GPIO4_Combined_16_31_IRQHandler

/* KEY2 <---> PMIC_ON_REQ */
#define KEY2_GPIO               GPIO1
#define KEY2_GPIO_PIN           (11U)
#define KEY2_GPIO_IRQ           GPIO1_Combined_0_15_IRQn
#define KEY2_GPIO_IRQ_HANDLER   GPIO1_Combined_0_15_IRQHandler

extern volatile bool g_KEY1_Signal;
extern volatile bool g_KEY2_Signal;

void bsp_key_init(char num);

#endif /* _BSP_LED_H_ */
