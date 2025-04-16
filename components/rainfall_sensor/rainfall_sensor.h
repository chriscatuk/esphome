#pragma once

#include "esphome.h"

namespace esphome
{
    namespace rainfall_sensor
    {

        class RainfallSensor : public PollingComponent, public UARTDevice, public Sensor
        {
        public:
            // Constructor to initialize UART parent
            RainfallSensor(UARTComponent *parent) : UARTDevice(parent) {}

            // Setup method to initialize components
            void setup() override
            {
                // Initialization code, if needed
            }

            // Method to update sensor readings (called periodically)
            void update() override
            {
                // Example: reading a line of data from UART
                std::string line = this->read_line();
                if (!line.empty())
                {
                    // Parse the line to extract the rainfall value (adjust based on your data format)
                    float value = std::stof(line); // Adjust parsing as needed
                    this->publish_state(value);    // Send the value to ESPHome
                }
            }
        };

    } // namespace rainfall_sensor
} // namespace esphome
