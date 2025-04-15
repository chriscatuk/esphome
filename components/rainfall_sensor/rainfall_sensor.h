#include "esphome.h"

class RainfallSensor : public PollingComponent, public UARTDevice, public Sensor
{
public:
    RainfallSensor(UARTComponent *parent) : UARTDevice(parent) {}

    void setup() override
    {
        // Nothing to initialise
    }

    void update() override
    {
        // Send the request command
        this->write_str("GET+RAINFALL=1\r\n");
    }

    void loop() override
    {
        while (available())
        {
            std::string line = this->read_line();
            int idx = line.find("+RAINFALL:");
            if (idx != std::string::npos)
            {
                std::string val_str = line.substr(idx + 10);
                val_str.erase(val_str.find("mm")); // remove 'mm'
                float value = atof(val_str.c_str());
                publish_state(value);
            }
        }
    }
};
