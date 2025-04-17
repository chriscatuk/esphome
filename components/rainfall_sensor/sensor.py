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
    UNIT_MILLIMETER_PER_HOUR,
    ICON_WATER,
)

CODEOWNERS = ["@chriscatuk"]

MULTI_CONF = True

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["sensor", "text_sensor"]

CONF_PRECIPITATION = "precipitation"
CONF_PRECIPITATION_INTENSITY = "precipitation_intensity"

# Hack to prevent compile error due to ambiguity with lib namespace
rainfall_sensor_ns = cg.esphome_ns.namespace("esphome::rainfall_sensor")
RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.declare_id(RainfallSensor),
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

    # Retrieve the UART component from the configuration.
    uart_component = await cg.get_variable(config[CONF_UART_ID])

    # Register the UART device and associate it with the rainfall sensor.
    await uart.register_uart_device(var, uart_component)

    if CONF_PRECIPITATION in config:
        sens = await sensor.new_sensor(config[CONF_PRECIPITATION])
        cg.add(var.set_precipitation_sensor(sens))

    if CONF_PRECIPITATION_INTENSITY in config:
        sens = await sensor.new_sensor(config[CONF_PRECIPITATION_INTENSITY])
        cg.add(var.set_precipitation_intensity_sensor(sens))
