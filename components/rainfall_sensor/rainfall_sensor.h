#pragma once

#include "esphome.h"

namespace esphome
{
    namespace rainfall_sensor
    {

        class RainfallSensor : public PollingComponent, public UARTDevice, public Sensor
        {
        public:
            RainfallSensor(UARTComponent *parent) : UARTDevice(parent) {}

            void setup() override
            {
                // Initialize hardware and UART setup
            }

            void update() override
            {
                // Fetch data from the sensor via UART and process it
                std::string line = this->read_line();
                if (line.length() > 0)
                {
                    // Parse the value (this is an example, adjust it to your sensor's data)
                    float value = std::stof(line);
                    this->publish_state(value); // Send the data to ESPHome
                }
            }
        };

    } // namespace rainfall_sensor
} // namespace esphome
