#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include <string>

namespace esphome
{
    namespace sen0575
    {

        class Sen0575 : public PollingComponent, public uart::UARTDevice
        {
        public:
            void setup() override;
            void update() override; // Declare the update method here

            bool parse_data(uint8_t byte);

            void set_total_rainfall(float rainfall) { total_rainfall_ = rainfall; }
            void set_precipitation_intensity(float intensity) { precipitation_intensity_ = intensity; }
            float get_total_rainfall() { return total_rainfall; }
            float get_precipitation_intensity() { return recipitation_intensity_; }

            void dump_config() override;
            float get_setup_priority() const override;

            void set_precipitation_sensor(sensor::Sensor *precipitation_sensor) { precipitation_sensor_ = precipitation_sensor; }
            void set_precipitation_intensity_sensor(sensor::Sensor *precipitation_intensity_sensor) { precipitation_intensity_sensor_ = precipitation_intensity_sensor; }

            /**
             * @enum  eSEN0575InputReg_t
             * @brief  Input Register Address
             */
            typedef enum
            {
                eInputRegPidSEN0575 = 0x0000,        /**< SEN0575 stores the address of the input register for PID in memory. */
                eInputRegVidSEN0575,                 /**< The address of the input register for VID in memory. */
                eInputRegRegAddrSEN0575,             /**< The address of the input register for device address in memory. */
                eInputRegBaudSEN0575,                /**< The address of the input register for device baudrate in memory. */
                eInputRegVerifyAndStopSEN0575,       /**< The address of the input register for RS485 parity bit and stop bit in memory. */
                eInputRegVersionSEN0575,             /**< The address of the input register for firmware version in memory. */
                eInputRegTimeRainFallLSEN0575,       /**< The address of the input register for low 16-bit cumulative rainfall in set time. */
                eInputRegTimeRainFallHSEN0575,       /**< The address of the input register for high 16-bit cumulative rainfall in set time. */
                eInputRegCumulativeRainFallLSEN0575, /**< The address of the input register for low 16-bit cumulative rainfall since working started. */
                eInputRegCumulativeRainFallHSEN0575, /**< The address of the input register for high 16-bit cumulative rainfall since working started. */
                eInputRegRawDataLSEN0575,            /**< The address of the input register for raw data (low 16-bit) in memory. */
                eInputRegRawDataHSEN0575,            /**< he address of the input register for raw data (high 16-bit) in memory. */
                eInputRegSysWorkingTimeSEN0575,      /**< The address of the input register for system working time in memory. */
            } eSEN0575InputReg_t;

            /**
             * @enum  eSEN0575HoldingReg_t
             * @brief  Holding Register Address of the Device
             */
            typedef enum
            {
                eHoldingRegReserved0SEN0575 = 0x0000, /**< SEN0575 this register is reserved. */
                eHoldingRegReserved1SEN0575,          /**< SEN0575 this register is reserved. */
                eHoldingRegReserved2SEN0575,          /**< SEN0575 this register is reserved. */
                eHoldingRegReserved3SEN0575,          /**< SEN0575 this register is reserved. */
                eHoldingRegReserved4SEN0575,          /**< SEN0575 this register is reserved. */
                eHoldingRegReserved5SEN0575,          /**< SEN0575 this register is reserved. */
                eHoldingRegRainHourSEN0575,           /**< Set the time to calculate cumulative rainfall */
                eHoldingRegBaseRainFallSEN0575,       /**< Set the base rainfall value. */
            } eSEN0575HoldingReg_t;

            /**
             * @fn begin
             * @brief This function will attempt to communicate with a slave device and determine if the communication is successful based on the return value.
             * @return Communication result
             * @retval true  Succeed
             * @retval false Failed
             */
            bool begin(void);

            /**
             * @fn getFirmwareVersion
             * @brief  get firmware version
             * @return  Return  firmware version
             */
            std::string getFirmwareVersion(void);

            /**
             * @fn getRainfall
             * @brief Get cumulative rainfall
             * @return Cumulative rainfall value
             */
            float getRainfall(void);

            /**
             * @fn getRainfall
             * @brief Get the cumulative rainfall within the specified time
             * @param hour Specified time (valid range is 1-24 hours)
             * @return Cumulative rainfall
             */
            float getRainfall(uint8_t hour);

            /**
             * @fn getRawData
             * @brief Get the Rawdata object
             * @return Number of tipping bucket counts, unit: count
             */
            uint32_t getRawData();

            /**
             * @fn getSensorWorkingTime
             * @brief Obtain the sensor working time
             * @return Working time of the sensor, in hours
             */
            float getSensorWorkingTime();

            /**
             * @fn setRainAccumulatedValue
             * @brief Set the Rain Accumulated Value object
             * @param accumulatedValue Rainfall accumulation value, in millimeters
             * @return Set result
             * @retval 0  set successfully
             * @retval Other values set failed
             */
            uint8_t setRainAccumulatedValue(float accumulatedValue = 0.2794);
            uint32_t vid;
            uint32_t pid;

        protected:
            float total_rainfall_ = 0.0;
            float precipitation_intensity_ = 0.0;

            bool read_data_(uint8_t *data);

            sensor::Sensor *precipitation_sensor_{nullptr};
            sensor::Sensor *precipitation_intensity_sensor_{nullptr};

        private:
            int _dePin;
            uint8_t _mode;

            /**
             * @fn getPidVid
             * @brief  Get VID and PID
             * @return  Result of getting the VID and PID
             * @retval true:succeeded in getting the VID and PID
             * @retval false:failed to get the data or the data obtained is incorrect
             */
            bool getPidVid(void);
            virtual uint8_t readRegister(uint8_t reg, void *pBuf, size_t size) { return 0; };
            virtual uint16_t readRegister(uint16_t reg) { return 0; };
            virtual uint8_t writeRegister(uint8_t reg, void *pBuf, size_t size) { return 0; };
            virtual uint16_t writeRegister(uint16_t reg, uint16_t data) { return 0; };
        };

    } // namespace dht12
} // namespace esphome