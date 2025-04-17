#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome
{
    namespace rainfall_sensor
    {

        class RainfallSensor : public PollingComponent, public uart::UARTDevice
        {
        public:
            RainfallSensor() = default;

            void setup() override;
            void update() override;

            void set_sensor(sensor::Sensor *sensor) { this->sensor_ = sensor; }

        protected:
            sensor::Sensor *sensor_{nullptr};
        };

    } // namespace rainfall_sensor
} // namespace esphome
