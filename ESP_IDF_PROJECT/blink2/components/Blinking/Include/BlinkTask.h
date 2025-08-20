#pragma once
#include "driver/gpio.h"
#include <memory>

class Blink {
    /**
     * @class Blink
     * @brief A class to handle blinking an LED connected to a specified GPIO pin.
     * This class initializes the GPIO pin, sets it as an output, and provides a method to start blinking the LED.
     * The blinking is controlled by a specified delay time.
     */
public:
    Blink(gpio_num_t pin, int timeDelay);

    static void startBlink(void* arg);

    ~Blink();

private:
    gpio_num_t mPin; // GPIO pin number for the LED
    int mTimeDelay; // Delay time in milliseconds for blinking
};
