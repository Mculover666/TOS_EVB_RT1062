#include "bsp_key.h"

volatile bool g_KEY1_Signal = false;
volatile bool g_KEY2_Signal = false;

void bsp_key_init(char num)
{
   /* Define the init structure for the input switch pin */
    gpio_pin_config_t sw_config = {kGPIO_DigitalInput, 0, kGPIO_IntLowLevel};

    switch (num) {
        case 1:
            /* Init input switch GPIO. */
            GPIO_PinInit(KEY1_GPIO, KEY1_GPIO_PIN, &sw_config);
        
            /* Enable GPIO pin interrupt */
            GPIO_PortEnableInterrupts(KEY1_GPIO, 1U << KEY1_GPIO_PIN);
        
            /* NVIC enable. */
            EnableIRQ(KEY1_GPIO_IRQ);
            break;
        case 2:
            /* Init input switch GPIO. */
            GPIO_PinInit(KEY2_GPIO, KEY2_GPIO_PIN, &sw_config);
        
            /* Enable GPIO pin interrupt */
            GPIO_PortEnableInterrupts(KEY2_GPIO, 1U << KEY2_GPIO_PIN);
        
            /* NVIC enable. */
            EnableIRQ(KEY2_GPIO_IRQ);
        
            break;
        default:
            break;
    }
}

void KEY1_GPIO_IRQ_HANDLER(void)
{
//    GPIO_PortClearInterruptFlags(KEY1_GPIO, 1U << KEY1_GPIO_PIN);
    GPIO_PortClearInterruptFlags(KEY1_GPIO, 1U << KEY1_GPIO_PIN);
    g_KEY1_Signal = true;
}

void KEY2_GPIO_IRQ_HANDLER()
{
    GPIO_PortClearInterruptFlags(KEY2_GPIO, 1U << KEY2_GPIO_PIN);
    g_KEY2_Signal = true;
}
