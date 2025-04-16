#include "rainfall_sensor.h"

namespace esphome
{
    namespace rainfall_sensor
    {

        class RainfallSensor : public UARTDevice, public Sensor
        {
        public:
            explicit RainfallSensor(UARTComponent *parent) : UARTDevice(parent) {}

            void setup() override
            {
                // Register the tick for periodic updates (every 60 seconds)
                App.register_tick([this]()
                                  { this->update(); }, 60);
            }

            void update()
            {
                // Get the data from the sensor
                std::string line = read_line();
                float rainfall_value = 0.0;

                // Try to convert the received data to float
                try
                {
                    rainfall_value = std::stof(line);
                }
                catch (const std::invalid_argument &e)
                {
                    rainfall_value = 0.0;
                }

                // Publish the rainfall amount
                this->publish_state(rainfall_value);
            }

            std::string read_line()
            {
                std::string line;
                if (this->available())
                {
                    line = this->read();
                }
                return line;
            }
        };

    } // namespace rainfall_sensor
} // namespace esphome
