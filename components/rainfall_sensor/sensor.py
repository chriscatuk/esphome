from esphome import pins
import esphome.codegen as cg
from esphome.components import sensor, uart
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_NAME,
    CONF_UART_ID,
    CONF_UNIT_OF_MEASUREMENT,
    CONF_ACCURACY_DECIMALS,
    DEVICE_CLASS_PRECIPITATION,
    DEVICE_CLASS_PRECIPITATION_INTENSITY,
    STATE_CLASS_TOTAL_INCREASING,
    STATE_CLASS_MEASUREMENT,
    UNIT_MILLIMETER,
    ICON_WATER,
)

# Not available in ESPHome, so define it manually:
UNIT_MILLIMETER_PER_HOUR = "mm/h"

CODEOWNERS = ["@chriscatuk"]

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["sensor", "text_sensor"]

CONF_PRECIPITATION = "precipitation"
CONF_PRECIPITATION_INTENSITY = "precipitation_intensity"

rainfall_sensor_ns = cg.esphome_ns.namespace("rainfall_sensor")
RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ID): cv.declare_id(RainfallSensor),
        cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
        cv.Optional(CONF_PRECIPITATION): sensor.sensor_schema(
            unit_of_measurement=UNIT_MILLIMETER,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_PRECIPITATION,
            state_class=STATE_CLASS_TOTAL_INCREASING,
            icon=ICON_WATER,
        ),
        cv.Optional(CONF_PRECIPITATION_INTENSITY): sensor.sensor_schema(
            unit_of_measurement=UNIT_MILLIMETER_PER_HOUR,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_PRECIPITATION_INTENSITY,
            state_class=STATE_CLASS_MEASUREMENT,
            icon=ICON_WATER,
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    # Create a new variable for the RainfallSensor.
    var = cg.new_Pvariable(config[CONF_ID])

    # Register the component (this makes it known to ESPHome).
    await cg.register_component(var, config)

    # That line is only valid if your class (RainfallSensor) directly inherits from sensor.Sensor
    # # Register the sensor itself (this makes it an actual sensor component in ESPHome).
    # await sensor.register_sensor(var, config)

    # Attach the UART device to your RainfallSensor
    await uart.register_uart_device(
        var, config
    )  # <-- pass full config, not just uart_id

    # If precipitation sensor is configured, create the sensor and link it to the RainfallSensor object
    if CONF_PRECIPITATION in config:
        precipitation_sensor = await sensor.new_sensor(config[CONF_PRECIPITATION])
        cg.add(var.set_precipitation_sensor(precipitation_sensor))

    # If precipitation intensity sensor is configured, create the sensor and link it
    if CONF_PRECIPITATION_INTENSITY in config:
        precipitation_intensity_sensor = await sensor.new_sensor(
            config[CONF_PRECIPITATION_INTENSITY]
        )
        cg.add(var.set_precipitation_intensity_sensor(precipitation_intensity_sensor))
