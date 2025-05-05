#include "sen0575.h"
#include "esphome/core/log.h"

namespace esphome
{
    namespace sen0575
    {

        static const char *const TAG = "sen0575";

        void Sen0575::setup()
        {
            ESP_LOGCONFIG(TAG, "Setting up SEN0575 Rainfall Sensor...");
            // Add any required initialization for the sensor here.
        }

        void Sen0575::update()
        {
            ESP_LOGD(TAG, "Polling SEN0575 sensor...");

            // Simulate or retrieve precipitation data
            float precipitation = 0.1f;           // mm
            float precipitation_intensity = 0.5f; // mm/h

            if (this->precipitation_sensor_ != nullptr)
                this->precipitation_sensor_->publish_state(precipitation);

            if (this->precipitation_intensity_sensor_ != nullptr)
                this->precipitation_intensity_sensor_->publish_state(precipitation_intensity);
        }

        void Sen0575::dump_config()
        {
            ESP_LOGCONFIG(TAG, "SEN0575:");
            LOG_SENSOR("  ", "Precipitation", this->precipitation_sensor_);
            LOG_SENSOR("  ", "Precipitation Intensity", this->precipitation_intensity_sensor_);
        }

        float Sen0575::get_setup_priority() const
        {
            return setup_priority::DATA;
        }
    } // namespace sen0575
} // namespace esphome
