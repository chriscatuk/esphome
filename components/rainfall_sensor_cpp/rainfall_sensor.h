#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "DFRobot_RainfallSensor.h" // Assuming it's placed in the same folder or included properly

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

    protected:
      DFRobot_RainfallSensor_UART *sensor_{nullptr};
    };

  } // namespace rainfall_sensor
} // namespace esphome
