#include <stdio.h>
#include <inttypes.h>
#include "hal/gpio_types.h"
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
    gpio_set_direction(PIN_A, GPIO_MODE_OUTPUT);
    gpio_pulldown_en(PIN_A);
    gpio_pillup_dis(PIN_A);
    gpio_set_direction(PIN_B, GPIO_MODE_OUTPUT);
    gpio_pulldown_en(PIN_B);
    gpio_pillup_dis(PIN_B);
    gpio_set_direction(PIN_C, GPIO_MODE_OUTPUT);
    gpio_pulldown_en(PIN_B);
    gpio_pillup_dis(PIN_C);
    
    /*
    */

    int readbits[8];
    int setbits[3];

    for(int i;i<8;i++){
        intToBits(i,setbits,3);
        gpio_set_level(PIN_A,setbits[0]);
        gpio_set_level(PIN_B,setbits[1]);
        gpio_set_level(PIN_C,setbits[2]);
        readbits[i] = gpio_get_level(PIN_READ);
    }

    printf("Binary array: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", bits[i]);
    }

}



void intToBits(int num, int bits[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        bits[i] = num & 1;   // take the least significant bit
        num >>= 1;           // shift right for the next bit
    }
}

int bitsToInt(int bits[], int size) {
    int value = 0;
    for (int i = 0; i < size; i++) {
        value = (value << 1) | bits[i];  
    }
    return value;
}
