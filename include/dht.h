#ifndef DHT_H
#define DHT_H

#include <stdbool.h>
#include "pico/stdlib.h"

typedef struct
{
    float humidity;
    float temp_celsius;
} dht_reading;

bool dht11_init(uint gpio);
bool dht11_read(dht_reading *reading);

#endif