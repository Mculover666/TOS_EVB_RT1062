#include "bsp_led.h"

void bsp_led_init(void)
{
    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

     /* Init output LED GPIO. */
    GPIO_PinInit(LED_GPIO, LED_GPIO_PIN, &led_config);
}

void bsp_led_ctl(char state)
{
    if (!state) {
        GPIO_PinWrite(LED_GPIO, LED_GPIO_PIN, 0);
    } else {
        GPIO_PinWrite(LED_GPIO, LED_GPIO_PIN, 1);
    }
}
