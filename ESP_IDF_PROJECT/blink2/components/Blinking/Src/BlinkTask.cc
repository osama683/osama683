#include "freertos/FreeRTOS.h"
#include "BlinkTask.h"
#include "driver/gpio.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <memory>

static const char* TAG ="blink2"; // Log tag for this module

Blink::Blink(gpio_num_t pin, int timeDelay) : mPin(pin), mTimeDelay(timeDelay)
{ 
    /**
     * @brief Constructor for the Blink class.
     * Initializes the GPIO pin and sets it as an output for blinking the LED.
     */
      ESP_LOGI(TAG, "star to intialized the pin %d with delay %d ms to blinking led!", mPin, mTimeDelay);
    gpio_reset_pin(mPin);
    gpio_set_direction(mPin, GPIO_MODE_OUTPUT);
    xTaskCreate(Blink::startBlink,"ledblink", 2048, this, 5, NULL);
    ESP_LOGV(TAG,"the pin is intialized");
}
void Blink::startBlink(void* arg)
{ 
    /**
     * @brief FreeRTOS task function to handle the blinking of the LED.
     * This function is called by FreeRTOS to run the blinking logic in a separate task
     */
      Blink* self = static_cast <Blink*> (arg);
    while(1)
    {   ESP_LOGI(TAG,"The led on pin %d is Ready to blinking in %d s!", self->mPin, self->mTimeDelay /1000);
        gpio_set_level(self->mPin, 0);
        vTaskDelay(pdMS_TO_TICKS(self->mTimeDelay));
        gpio_set_level(self->mPin, 1);
        vTaskDelay(pdMS_TO_TICKS(self->mTimeDelay));
        ESP_LOGD(TAG,"The led on pin %d is Ready to stop in %d s!", self->mPin, self->mTimeDelay /1000);
        vTaskDelay(pdMS_TO_TICKS(self->mPin));
    }

}

Blink::~Blink()
{
    /**
     * @brief Destructor for the Blink class.
     * Cleans up resources and resets the GPIO pin to its default state.
     */
    ESP_LOGE(TAG, "Blink object is being destroyed, cleaning up resources.");
    gpio_reset_pin(mPin); // Reset the GPIO pin to its default state
    ESP_LOGI(TAG, "Blink object destroyed successfully.");
}