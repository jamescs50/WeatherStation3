#include <stdio.h>
#include <inttypes.h>
#include "hal/gpio_types.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define PIN_A 16
#define PIN_B 17
#define PIN_C 18
#define PIN_READ 25
#define PIN_1INHIBIT 26
#define PIN_2INHIBIT 27


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


int read_multiplex(int which)
{
    switch(which){
        case 1:{
            gpio_set_level(PIN_1INHIBIT, 0);
            gpio_set_level(PIN_2INHIBIT, 1);            
            break;
        }
        case 2:{
            gpio_set_level(PIN_1INHIBIT, 1);
            gpio_set_level(PIN_2INHIBIT, 0);            
            break;
        }
    }
    
    int readbits[8];
    int setbits[3];

    for(int i = 0; i < 8; i++){
        intToBits(i,setbits,3);
        gpio_set_level(PIN_A,setbits[0]);
        gpio_set_level(PIN_B,setbits[1]);
        gpio_set_level(PIN_C,setbits[2]);
        vTaskDelay(1);  //small delay for CD4051 to switch the switch takes (max)60 ns - the deay should be about 10 us)
        readbits[i] = gpio_get_level(PIN_READ);
    }
    
    printf("Binary array: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", readbits[i]);
    }
    printf("\n");

    return bitsToInt(readbits, 8);

}

void app_main(void)
{
    gpio_set_direction(PIN_A, GPIO_MODE_OUTPUT);
    gpio_pulldown_en(PIN_A);
    gpio_set_direction(PIN_B, GPIO_MODE_OUTPUT);
    gpio_pulldown_en(PIN_B);
    gpio_set_direction(PIN_C, GPIO_MODE_OUTPUT);
    gpio_pulldown_en(PIN_B);
    gpio_set_direction(PIN_READ, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_1INHIBIT, GPIO_MODE_OUTPUT);
    gpio_pulldown_en(PIN_1INHIBIT);
    gpio_set_direction(PIN_2INHIBIT, GPIO_MODE_OUTPUT);
    gpio_pulldown_en(PIN_2INHIBIT);


    int c = 0;
    while (true){
        c++;
        printf("counter %d \n",c);
        printf("Result: %d \n",read_multiplex(1));
        vTaskDelay(4999 / portTICK_PERIOD_MS);    
    }

}


