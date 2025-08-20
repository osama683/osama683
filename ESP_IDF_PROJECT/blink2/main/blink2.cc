#include <stdio.h>
#include "sdkconfig.h"
#include "BlinkTask.h"

extern "C" void app_main(void)
{
    static Blink led1(GPIO_NUM_2, 1000);   
    static Blink led2(GPIO_NUM_4, 1000);   
    static Blink led3(GPIO_NUM_5, 1000);   

}
