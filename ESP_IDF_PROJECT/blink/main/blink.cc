/**
 * @file blink.cc
 * @brief Implementation of a simple blinking LED functionality using ESP-IDF.
 * This file defines a Blink class that manages the blinking of an LED connected to a specified GPIO pin.
 * The class initializes the GPIO pin, sets it as an output, and provides a method to
 */
#include <stdio.h> // Standard I/O for debugging
#include "sdkconfig.h" // Configuration header for ESP-IDF
#include "driver/gpio.h" // GPIO driver for ESP-IDF
#include "freertos/FreeRTOS.h" // FreeRTOS header for task management
#include "freertos/task.h" // FreeRTOS task header
#include "esp_log.h"   // ESP-IDF logging library

static const char* TAG = "blink"; // Log tag for this module

class Blink{
    /**
     * @class Blink
     * @brief A class to handle blinking an LED connected to a specified GPIO pin.
     * This class initializes the GPIO pin, sets it as an output, and provides a method to start blinking the LED.
     * The blinking is controlled by a specified delay time.
     * @note The class uses ESP-IDF's GPIO and FreeRTOS functionalities.
     * @param pin The GPIO pin number to which the LED is connected.
     * @param timeDelay The delay time in milliseconds between turning the LED on and off.
     */
    public:
        Blink(gpio_num_t pin, int timeDelay) : mPin(pin), mTimeDelay(timeDelay){
            /**
             * @brief Constructor for the Blink class.
             * Initializes the GPIO pin and sets it as an output for blinking the LED.
             * @param pin The GPIO pin number to which the LED is connected.
             * @param timeDelay The delay time in milliseconds between toggling the LED state.
             */
            gpio_reset_pin(mPin);
            gpio_set_direction(mPin, GPIO_MODE_OUTPUT);
            ESP_LOGW(TAG,"Blink intialized for blinking on pin %d with delay time = %d ms", mPin, mTimeDelay);
        }

        void startBlinking(){
            /**
             * @brief Starts blinking the LED connected to the specified GPIO pin.
             * This method toggles the GPIO pin state to turn the LED on and off with a specified delay.
             * It uses FreeRTOS tasks for timing control.
             */
            ESP_LOGW(TAG, "Blinking is started on pin %d With delay time = %d ms", mPin, mTimeDelay);
            gpio_set_level(mPin, 1);
            vTaskDelay(pdMS_TO_TICKS(mTimeDelay));
            gpio_set_level(mPin, 0);
            vTaskDelay(mTimeDelay / portTICK_PERIOD_MS);
        }


        static void blinkTask(void* arg)
        {     /**
             * @brief FreeRTOS task function to handle the blinking of the LED.
             * This function is called by FreeRTOS to run the blinking logic in a separate task.
             * @param arg Pointer to the Blink object that contains the GPIO pin and delay time.
             */
            Blink* ledObj = static_cast<Blink*>(arg);
            while (1)
            {
                ledObj->startBlinking(); // Call the startBlinking method of the Blink object
            }
        }


        ~Blink(){ 
            /**
             * @brief Destructor for the Blink class.
             * This destructor resets the GPIO pin when the Blink object is destroyed.
             */
            gpio_reset_pin(mPin); // Reset the GPIO pin when the object is destroyed
            // Log a warning message indicating the Blink object is being destroyed
            ESP_LOGW(TAG, "Blink object is destroyed for pin %d", mPin);
        }

    private:
        gpio_num_t mPin; // GPIO pin number for the LED
        int mTimeDelay; // Delay time in milliseconds for blinking
};


extern "C" void app_main(void)
{
    static Blink led1(GPIO_NUM_2, 1000); // Create a Blink object for GPIO pin with a 1000 ms delay
    static Blink led2(GPIO_NUM_4, 500); // Create another Blink object for GPIO pin 4 with a 500 ms delay
    static Blink led3(GPIO_NUM_5, 1500); // Create a third Blink object for GPIO pin 5 with a 1500 ms delay

    xTaskCreate(Blink::blinkTask, "led1_task", 2048, &led1, 5, NULL); // Start blinking task for led1
    xTaskCreate(Blink::blinkTask, "led2_task", 2048, &led2, 5, NULL); // Start blinking task for led2
    xTaskCreate(Blink::blinkTask, "led3_task", 2048, &led3, 5, NULL); // Start blinking task for led3

}
