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
                // Any initialization code for the sensor
            }

            void update() override
            {
                std::string line = this->read_line();
                if (!line.empty())
                {
                    // Example: convert the line to float and publish the state
                    float value = std::stof(line);
                    this->publish_state(value); // Send the data to ESPHome
                }
            }
        };

    } // namespace rainfall_sensor
} // namespace esphome
