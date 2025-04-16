#include "rainfall_sensor.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace rainfall_sensor
  {

    static const char *const TAG = "rainfall_sensor";

    void RainfallSensor::setup()
    {
      ESP_LOGCONFIG(TAG, "Setting up DFRobot Rainfall Sensor (UART)...");
      sensor_ = new DFRobot_RainfallSensor_UART(&this->parent_->stream());

      if (sensor_->begin())
      {
        ESP_LOGI(TAG, "Rainfall sensor initialized successfully");
      }
      else
      {
        ESP_LOGE(TAG, "Failed to initialize rainfall sensor");
      }
    }

    void RainfallSensor::loop()
    {
      if (!sensor_)
        return;

      // Get rainfall in mm
      float rainfall = sensor_->getRainfall();
      ESP_LOGD(TAG, "Rainfall measured: %.2f mm", rainfall);
      this->publish_state(rainfall);
    }

    void RainfallSensor::dump_config()
    {
      LOG_SENSOR("", "DFRobot Rainfall Sensor", this);
    }

  } // namespace rainfall_sensor
} // namespace esphome
