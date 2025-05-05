#include "sen0575.h"
#include "esphome/core/log.h"

namespace esphome
{
    namespace sen0575
    {

        static const char *const TAG = "sen0575";

        // `setup()` is where you can initialize components if necessary
        void Sen0575::setup()
        {
            ESP_LOGCONFIG(TAG, "Setting up SEN0575 Rainfall Sensor...");
            pid = 0;
            vid = 0;
        }

        // `update()` will be called every `PollingComponent` interval
        void Sen0575::update()
        {
            ESP_LOGD(TAG, "Polling SEN0575 sensor...");

            uint8_t incoming_byte = 0;

            if (available())
            {
                incoming_byte = read();

                // Parse data from the incoming byte
                if (parse_data(incoming_byte))
                {
                    ESP_LOGI(TAG, "total_rainfall_: %f", total_rainfall_);
                    ESP_LOGI(TAG, "precipitation_intensity_: %f", precipitation_intensity_);
                    if (precipitation_sensor_ != nullptr)
                    {
                        precipitation_sensor_->publish_state(total_rainfall_);
                    }
                    if (precipitation_intensity_sensor_ != nullptr)
                    {
                        precipitation_intensity_sensor_->publish_state(precipitation_intensity_);
                    }
                }
            }
        }

        // The method to parse data from the UART stream
        bool Sen0575::parse_data(uint8_t byte)
        {
            // Example parsing logic
            // This would be more complex based on your sensor's protocol
            total_rainfall_ += byte * 0.1;          // Placeholder logic for total rainfall
            precipitation_intensity_ = byte * 0.05; // Placeholder for intensity

            return true;
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

        bool Sen0575::begin(void)
        {
            return getPidVid();
        }

        std::string Sen0575::getFirmwareVersion(void)
        {
            uint16_t version = 0;
            version = readRegister(eInputRegVersionSEN0575);
            return std::to_string(version >> 12) + "." +
                   std::to_string((version >> 8) & 0x0F) + "." +
                   std::to_string((version >> 4) & 0x0F) + "." +
                   std::to_string(version & 0x0F);
        }

        bool Sen0575::getPidVid(void)
        {
            bool ret = false;
            pid = readRegister(eInputRegPidSEN0575);
            vid = readRegister(eInputRegVidSEN0575);
            pid = (vid & 0xC000) << 2 | pid;
            vid = vid & 0x3FFF;
            if ((vid == 0x3343) && (pid == 0x100C0))
            {
                ret = true;
            }
            return ret;
        }

        float Sen0575::getRainfall(void)
        {
            uint32_t rainfall = 0;
            rainfall = readRegister(eInputRegCumulativeRainFallHSEN0575);
            rainfall = rainfall << 16 | readRegister(eInputRegCumulativeRainFallLSEN0575);
            return rainfall / 10000.0;
        }

        float Sen0575::getRainfall(uint8_t hour)
        {
            uint32_t rainfall = 0;
            writeRegister(eHoldingRegRainHourSEN0575, hour);
            rainfall = readRegister(eInputRegTimeRainFallHSEN0575);
            rainfall = rainfall << 16 | readRegister(eInputRegTimeRainFallLSEN0575);
            return rainfall / 10000.0;
        }

        uint32_t Sen0575::getRawData(void)
        {
            uint32_t rawdata = 0;
            rawdata = readRegister(eInputRegRawDataHSEN0575);
            rawdata = rawdata << 16 | readRegister(eInputRegRawDataLSEN0575);
            return rawdata;
        }

        uint8_t Sen0575::setRainAccumulatedValue(float value)
        {
            uint8_t ret = 0;
            uint16_t data = value * 10000;
            ret = writeRegister(eHoldingRegBaseRainFallSEN0575, data);
            return ret;
        }

        float Sen0575::getSensorWorkingTime(void)
        {
            uint16_t WorkingTime = 0;
            WorkingTime = readRegister(eInputRegSysWorkingTimeSEN0575);
            return WorkingTime / 60.0;
        }
    } // namespace sen0575
} // namespace esphome
