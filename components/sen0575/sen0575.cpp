#include "sen0575.h"
#include "esphome/core/log.h"

namespace esphome
{
    namespace sen0575
    {

        static const char *const TAG = "sen0575";

        // Constructor
        Sen0575::Sen0575(uart::UARTComponent *parent) : PollingComponent(1000), UARTDevice(parent) {}

        // `setup()` is where you can initialize components if necessary
        void Sen0575::setup()
        {
            ESP_LOGCONFIG(TAG, "Setting up SEN0575 Rainfall Sensor...");
            // Add any required initialization for the sensor here.
        }

        // `update()` will be called every `PollingComponent` interval
        void Sen0575::update()
        {
            ESP_LOGD(TAG, "Polling SEN0575 sensor...");

            uint8_t incoming_byte = 0;

            if (uart_->available())
            {
                incoming_byte = uart_->read();

                // Parse data from the incoming byte
                if (parse_data(incoming_byte))
                {
                    // Update the sensor values and publish
                    publish_state(total_rainfall_);
                    publish_state(precipitation_intensity_);
                }
            }
        }

        // The method to parse data from the UART stream
        bool Sen0575::parse_data(uint8_t byte)
        {
            // Example parsing logic
            // This would be more complex based on your sensor's protocol
            total_rainfall_ += byte * 0.1;          // Placeholder logic for total rainfall
            precipitation_intensity_ = byte * 0.05; // Placeholder for intensity

            return true;
        }

        void Sen0575::dump_config()
        {
            ESP_LOGCONFIG(TAG, "SEN0575:");
            LOG_SENSOR("  ", "Precipitation", this->precipitation_sensor_);
            LOG_SENSOR("  ", "Precipitation Intensity", this->precipitation_intensity_sensor_);
        }

        float Sen0575::get_setup_priority() const
        {
            return setup_priority::DATA;
        }
    } // namespace sen0575
} // namespace esphome
