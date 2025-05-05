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
            void setup() override;
            void dump_config() override;
            float get_setup_priority() const override;
            void update() override;

            void set_precipitation_sensor(sensor::Sensor *precipitation_sensor) { precipitation_sensor_ = precipitation_sensor; }
            void set_precipitation_intensity_sensor(sensor::Sensor *precipitation_intensity_sensor) { precipitation_intensity_sensor_ = precipitation_intensity_sensor; }

        protected:
            bool read_data_(uint8_t *data);

            sensor::Sensor *precipitation_sensor_{nullptr};
            sensor::Sensor *precipitation_intensity_sensor_{nullptr};
        };

    } // namespace dht12
} // namespace esphome