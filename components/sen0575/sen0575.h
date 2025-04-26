#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome
{
    namespace sen0575
    {

        class Sen0575 : public PollingComponent, public uart::UARTDevice
        {
        public:
            Sen0575() = default;

            void setup() override;
            void update() override;

            void set_sensor(sensor::Sensor *sensor) { this->sensor_ = sensor; }

        protected:
            sensor::Sensor *sensor_{nullptr};
        };

    } // namespace sen0575
} // namespace esphome
