#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_PIN 25
#define BUF_SIZE 150

void print_prompt(void)
{
    printf("uart-shell$ ");
}

void read_line(char *buf, size_t len)
{
    int i = 0;

    while (true)
    {
        int ch = getchar();

        putchar(ch);   // echo character

        if (ch == '\r' || ch == '\n')
        {
            printf("\n");
            break;
        }

        if (i < len - 1)
        {
            buf[i] = (char)ch;
            i++;
        }
    }

    buf[i] = '\0';
}

void process_command(char *cmd)
{
    if (strcmp(cmd, "led on") == 0)
    {
        gpio_put(LED_PIN, 1);
        printf("LED ON\n");
    }
    else if (strcmp(cmd, "led off") == 0)
    {
        gpio_put(LED_PIN, 0);
        printf("LED OFF\n");
    }
    else if (strcmp(cmd, "help") == 0)
    {
        printf("Available commands:\n");
        printf("  help\n");
        printf("  led on\n");
        printf("  led off\n");
    }
    else
    {
        printf("Unknown command\n");
    }
}

int main()
{
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    sleep_ms(2000);

    char cmd[BUF_SIZE];

    while (true)
    {
        print_prompt();

        read_line(cmd, BUF_SIZE);

        process_command(cmd);
    }
}