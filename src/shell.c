#include "shell.h"
#include "hardware/gpio.h"

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