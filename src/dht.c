#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "dht.h"

//const uint DHT_PIN = 15;
static const uint MAX_TIMINGS = 85;

static uint dht_pin;
bool dht11_init(uint gpio)
{
    dht_pin = gpio;
    gpio_init(dht_pin);
    gpio_set_dir(dht_pin, GPIO_IN);
    return true;
}


bool dht11_read(dht_reading *reading)
{
    //driver is only supposed to talk to the hardware
    //it is unaware of the commands and shell
    //do not try to print anything

    //return true 

    int data[5] = {0,0,0,0,0};
    uint last = 1;
    uint j = 0; //bit counter (0 to 39)

    gpio_set_dir(dht_pin, GPIO_OUT);
    gpio_put(dht_pin, 0); //holding the pin down -> awaken sensor
    sleep_ms(20);
    gpio_set_dir(dht_pin, GPIO_IN);

    for (uint i=0; i<MAX_TIMINGS; i++)
    {
        uint count = 0;
        while(gpio_get(dht_pin) == last)
        {
            count++; //it increments every 1µs while the pin stays in its current state
            sleep_us(1);
            if (count == 255) break;
        }

        last = gpio_get(dht_pin);
        if (count == 255) break;

        if ((i >= 4) && (i % 2 == 0)) //4 is the ack/handshake part (skip it) and each bit = 2edges so i%2==0 picks only high pulses where count tells 0 or 1
        {
            data[j/8] <<= 1; //left shift and put 1 in LSB. j/8 = byte. {{* shift byte left, LSB becomes 0*}}
            if (count > 16) data[j / 8] |= 1; // if long HIGH, set LSB to 1
            j++; //building each byte bit by bit, MSB first
        }
    }

    //checksum
    if ((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
    {
        reading->humidity = (float) ((data[0] << 8) + data[1]) / 10;
        if (reading->humidity > 100) {
            reading->humidity = data[0];
    }

    reading->temp_celsius = (float) (((data[2] & 0x7F) << 8) + data[3]) / 10;
    if (reading->temp_celsius > 125) {
        reading->temp_celsius = data[2];
    }

    if (data[2] & 0x80) {
        reading->temp_celsius = -reading->temp_celsius;
    }
    return true;
} else {
    return false;
}
}
