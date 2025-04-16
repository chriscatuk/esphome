#include "esphome.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/update_interval/update_interval.h"

namespace esphome
{
    namespace rainfall_sensor
    {

        class RainfallSensor : public UpdateIntervalComponent, public UARTDevice, public Sensor
        {
        public:
            explicit RainfallSensor(UARTComponent *parent) : UARTDevice(parent) {}

            void setup() override
            {
                // Perform any setup necessary (e.g., initialize UART, etc.)
            }

            void update() override
            {
                std::string line = read_line();
                float rainfall_value = 0.0;

                try
                {
                    rainfall_value = std::stof(line);
                }
                catch (const std::invalid_argument &e)
                {
                    rainfall_value = 0.0;
                }

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
