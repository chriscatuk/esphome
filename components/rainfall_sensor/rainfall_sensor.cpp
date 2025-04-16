#include "esphome.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/polling/polling.h"

namespace esphome
{
    namespace rainfall_sensor
    {

        class RainfallSensor : public PollingComponent, public UARTDevice, public Sensor
        {
        public:
            explicit RainfallSensor(UARTComponent *parent) : UARTDevice(parent) {}

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

            void publish_state(float value)
            {
                Sensor::publish_state(value);
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
