#pragma once

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace rainfall_sensor {

class RainfallSensor : public sensor::Sensor, public PollingComponent, public uart::UARTDevice {
 public:
  void setup() override;
  void update() override;

 protected:
  float parse_rainfall_data(const std::string &data);
};

}  // namespace rainfall_sensor
}  // namespace esphome

