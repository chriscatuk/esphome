#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome.h"

namespace esphome
{
    namespace sen0575
    {

        class Sen0575 : public PollingComponent, public uart::UARTDevice
        {
        public:
            Sen0575(uart::UARTComponent *parent);

            void setup() override;
            void update() override; // Declare the update method here

            bool parse_data(uint8_t byte);

            void set_total_rainfall(float rainfall) { total_rainfall_ = rainfall; }
            void set_precipitation_intensity(float intensity) { precipitation_intensity_ = intensity; }

            void dump_config() override;
            float get_setup_priority() const override;

            void set_precipitation_sensor(sensor::Sensor *precipitation_sensor) { precipitation_sensor_ = precipitation_sensor; }
            void set_precipitation_intensity_sensor(sensor::Sensor *precipitation_intensity_sensor) { precipitation_intensity_sensor_ = precipitation_intensity_sensor; }

        protected:
            UARTComponent *uart_;

            Sensor *total_rainfall_sensor_{nullptr};
            Sensor *intensity_sensor_{nullptr};

            float total_rainfall_ = 0.0;
            float precipitation_intensity_ = 0.0;

            bool read_data_(uint8_t *data);

            sensor::Sensor *precipitation_sensor_{nullptr};
            sensor::Sensor *precipitation_intensity_sensor_{nullptr};
        };

    } // namespace dht12
} // namespace esphome