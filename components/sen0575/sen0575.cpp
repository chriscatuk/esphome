#include "sen0575.h"
#include "esphome/core/log.h"

namespace esphome
{
    namespace sen0575
    {

        static const char *const TAG = "sen0575";

        void Sen0575::setup()
        {
            ESP_LOGCONFIG(TAG, "Setting up Sen0575Sensor...");
            // Initialize UART or sensor-specific logic
        }

        void Sen0575::update()
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
