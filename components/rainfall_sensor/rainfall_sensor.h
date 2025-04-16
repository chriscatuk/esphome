#pragma once

#include "esphome.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

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
                // Initialization code for the sensor
            }

            void update() override
            {
                // Fetch sensor data and publish it
                // For example, if you receive a string, you can read it like:
                std::string line = this->read_line();
                if (!line.empty())
                {
                    float value = std::stof(line); // Convert the string to a float
                    this->publish_state(value);    // Send the data to ESPHome
                }
            }

            void loop() override
            {
                // Optional: If there's any other logic that needs to run in the loop, add it here
            }
        };

    } // namespace rainfall_sensor
} // namespace esphome
