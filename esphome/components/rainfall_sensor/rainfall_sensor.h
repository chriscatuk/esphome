#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome
{
  namespace rainfall_sensor
  {

    class RainfallSensor : public sensor::Sensor, public Component, public uart::UARTDevice
    {
    public:
      void setup() override;
      void loop() override;
      void dump_config() override;
    };

  } // namespace rainfall_sensor
} // namespace esphome
