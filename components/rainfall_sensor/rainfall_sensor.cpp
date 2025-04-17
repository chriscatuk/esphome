#include "rainfall_sensor.h"
#include "esphome/core/log.h"

namespace esphome
{
    namespace rainfall_sensor
    {

        static const char *const TAG = "rainfall_sensor";

        void RainfallSensor::setup()
        {
            ESP_LOGCONFIG(TAG, "Setting up RainfallSensor...");
            // Initialize UART or sensor-specific logic
        }

        void RainfallSensor::update()
        {
            // Example: Read one line from UART
            std::string line = this->read_line();
            ESP_LOGD(TAG, "Received line: %s", line.c_str());

            // Here, you can parse the line to extract rainfall data
            // Example:
            if (line.find("RAIN:") != std::string::npos)
            {
                float rain_mm = parse_float(line.substr(line.find(":") + 1).c_str());
                if (this->sensor_ != nullptr)
                {
                    this->sensor_->publish_state(rain_mm);
                }
            }
        }

    } // namespace rainfall_sensor
} // namespace esphome
