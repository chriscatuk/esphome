#include "rainfall_sensor.h"

namespace esphome
{
    namespace rainfall_sensor
    {

        // Constructor implementation (if needed)
        RainfallSensor::RainfallSensor(UARTComponent *parent) : UARTDevice(parent) {}

        // Setup function (already defined in the header)
        void RainfallSensor::setup()
        {
            // Setup code for the sensor, if any.
        }

        // Update function (already defined in the header)
        void RainfallSensor::update()
        {
            // Example: Read a line from the UART sensor
            std::string line = this->read_line();
            if (!line.empty())
            {
                // Parse the string (example, adapt to your sensor data format)
                float value = std::stof(line);
                this->publish_state(value); // Send the value to ESPHome
            }
        }

    } // namespace rainfall_sensor
} // namespace esphome
