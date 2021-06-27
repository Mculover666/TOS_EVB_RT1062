#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "fsl_gpio.h"

/* KEY1 <---> PMIC_STBY_REQ */
#define KEY1_GPIO               GPIO5
#define KEY1_GPIO_PIN           (2U)
#define KEY1_GPIO_IRQ           GPIO5_Combined_0_15_IRQn

/* KEY2 <---> PMIC_ON_REQ */
#define KEY2_GPIO               GPIO5
#define KEY2_GPIO_PIN           (1U)
#define KEY2_GPIO_IRQ           GPIO5_Combined_0_15_IRQn

#define KEY1_2_GPIO_IRQHandler  GPIO5_Combined_0_15_IRQHandler


extern volatile bool g_KEY1_Signal;
extern volatile bool g_KEY2_Signal;

void bsp_key_init(char num);



#endif /* _BSP_LED_H_ */
