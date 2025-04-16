#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome
{
    namespace rainfall_sensor
    {

        class RainfallSensor : public PollingComponent, public uart::UARTDevice, public sensor::Sensor
        {
        public:
            RainfallSensor(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

            void setup() override
            {
                // Setup code here
            }

            void update() override
            {
                this->write_str("GET+RAINFALL=1\r\n");
            }

            void loop() override
            {
                while (this->available())
                {
                    std::string line = this->read_line();
                    if (line.find("RAINFALL") != std::string::npos)
                    {
                        float value = std::stof(line.substr(line.find("=") + 1));
                        this->publish_state(value);
                    }
                }
            }
        };

    } // namespace rainfall_sensor
} // namespace esphome
