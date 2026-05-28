#include <stdio.h>
#include "pico/stdlib.h"

int main()
{
    stdio_init_all();

    sleep_ms(5000);

    printf("Program started!\n");

    while (true)
    {
        char arr[150];
        int i = 0;

        printf("Enter characters: ");

        while (true)
        {
            int ch = getchar();

            // Enter key pressed
            if (ch == '\n' || ch == '\r')
            {
                break;
            }

            // Prevent buffer overflow
            if (i < 149)
            {
                arr[i] = (char)ch;
                i++;
            }
        }

        // Null terminate string
        arr[i] = '\0';

        printf("Received: %s\n", arr);
    }
}