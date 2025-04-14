#include "rainfall_sensor.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace rainfall_sensor
  {

    static const char *const TAG = "rainfall_sensor";

    void RainfallSensor::setup()
    {
      ESP_LOGCONFIG(TAG, "Setting up Rainfall Sensor...");
      // Setup code here (if needed)
    }

    void RainfallSensor::loop()
    {
      // Read UART input
      while (this->available())
      {
        std::string line = this->read_line();
        ESP_LOGD(TAG, "Received: %s", line.c_str());

        // Try to parse float from the received string
        float value = atof(line.c_str());

        // Optional: validate the value
        if (value >= 0.0f && value < 1000.0f)
        {
          ESP_LOGI(TAG, "Rainfall: %.2f mm", value);
          this->publish_state(value);
        }
      }
    }

    void RainfallSensor::dump_config()
    {
      LOG_SENSOR("", "Rainfall Sensor", this);
      LOG_UPDATE_INTERVAL(this);
    }

  } // namespace rainfall_sensor
} // namespace esphome
