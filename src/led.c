#include "led.h"
#include "hardware/gpio.h"

#define LED_PIN 25

void led_init(void)
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void led_on(void)
{
    gpio_put(LED_PIN, 1);
}

void led_off(void)
{
    gpio_put(LED_PIN, 0);
}