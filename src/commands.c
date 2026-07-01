#include "commands.h"
#include "hardware/gpio.h"
#include "led.h"
#include "dht.h" 

#define LED_PIN 25

static void cmd_help(void)
    {
        printf("Available commands: \n");
        printf("    help\n");
        printf("    led on\n");
        printf("    led off\n");
        printf("    sensor read\n");
    }

static void cmd_led_on(void)
{
    led_on();
    printf("LED ON\n");
}

static void cmd_led_off(void)
{
    led_off();
    printf("LED OFF\n");
}

static void cmd_dht11_read(void)
{
    dht_reading reading;
    if (dht11_read(&reading))
    {
        printf("temperature: %.1f C\n", reading.temp_celsius);
        printf("humidity: %.1f %%\n", reading.humidity);
    }
    else
    {
        printf("sensor read failed.\n");
    }

}

//registry
static command_t commands[] =
{
    {"help", cmd_help},
    {"led on", cmd_led_on},
    {"led off", cmd_led_off},
    {"sensor read", cmd_dht11_read},
};

void process_command(char *cmd)
{
    size_t count = sizeof(commands) / sizeof(commands[0]);

    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(cmd, commands[i].name) == 0)
        {
            commands[i].handler();
            return;
        }
    }

    printf("Unknown command\n");
}