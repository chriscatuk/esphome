#include "esphome.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/delay/delay.h" // Include the Delay component

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
                // Setup code (e.g., initialize UART, etc.)
            }

            void update() override
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

                // Delay for the next update (e.g., update every 60 seconds)
                delay(60000); // Delay in milliseconds (1 minute)
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
