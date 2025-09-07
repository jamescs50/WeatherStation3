#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define PIN_A 16;
#define PIN_B 17;
#define PIN_C 18;
#define PIN_READ 25;
#define PIN_INHIBIT 26;


void app_main(void)
{

}


void intToBits(int num, int bits[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        bits[i] = num & 1;   // take the least significant bit
        num >>= 1;           // shift right for the next bit
    }
}

int bitsToDecimal(int bits[], int size) {
    int decimal = 0;
    for (int i = 0; i < size; i++) {
        decimal = (decimal << 1) | bits[i];  
    }
    return decimal;
}