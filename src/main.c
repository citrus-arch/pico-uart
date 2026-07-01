#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "led.h"
#include "commands.h"
#include "shell.h"

#define LED_PIN 25
#define DHT_GPIO 15
#define BUF_SIZE 150

int main()
{
    stdio_init_all();

    led_init();
    dht11_init(DHT_GPIO);

    sleep_ms(2000);

    char cmd[BUF_SIZE];

    while (true)
    {
        print_prompt();

        read_line(cmd, BUF_SIZE);

        process_command(cmd);
    }
}

