#include "rainfall_sensor.h"

namespace esphome
{
    namespace rainfall_sensor
    {

        // Constructor and setup function as in the header file
        RainfallSensor::RainfallSensor(UARTComponent *parent) : UARTDevice(parent) {}

        void RainfallSensor::setup()
        {
            // Initialization code if needed
        }

        void RainfallSensor::update()
        {
            std::string line = this->read_line();
            if (!line.empty())
            {
                float value = std::stof(line); // Convert string to float
                this->publish_state(value);    // Publish the state to ESPHome
            }
        }

    } // namespace rainfall_sensor
} // namespace esphome
