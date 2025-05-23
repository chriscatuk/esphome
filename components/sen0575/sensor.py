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

sen0575_ns = cg.esphome_ns.namespace("sen0575")
Sen0575 = sen0575_ns.class_("Sen0575", cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ID): cv.declare_id(Sen0575),
        cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
        cv.Optional(CONF_PRECIPITATION): sensor.sensor_schema(
            unit_of_measurement=UNIT_MILLIMETER,  # default values
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


# turn the YAML configuration into C++
async def to_code(config):

    # add arduino framework
    # cg.add_platformio_option("framework", "arduino, espidf")

    # Check if the units are correct
    precip_unit = config[CONF_PRECIPITATION]["unit_of_measurement"]
    intensity_unit = config[CONF_PRECIPITATION_INTENSITY]["unit_of_measurement"]
    if precip_unit != UNIT_MILLIMETER:
        raise cv.Invalid(
            f"Invalid unit for {CONF_PRECIPITATION}: {precip_unit}. Expected {UNIT_MILLIMETER}"
        )
    if intensity_unit != UNIT_MILLIMETER_PER_HOUR:
        raise cv.Invalid(
            f"Invalid unit for {CONF_PRECIPITATION_INTENSITY}: {intensity_unit}. Expected {UNIT_MILLIMETER_PER_HOUR}"
        )

    # Create a new variable for the Sen0575.
    my_sensor = cg.new_Pvariable(config[CONF_ID])

    # Register the component (this makes it known to ESPHome).
    await cg.register_component(my_sensor, config)

    # That line is only valid if your class (Sen0575) directly inherits from sensor.Sensor
    # # Register the sensor itself (this makes it an actual sensor component in ESPHome).
    # await sensor.register_sensor(my_sensor, config)

    # Attach the UART device to your Sen0575
    await uart.register_uart_device(
        my_sensor, config
    )  # <-- pass full config, not just uart_id

    # If precipitation sensor is configured, create the sensor and link it to the Sen0575 object
    if CONF_PRECIPITATION in config:
        precipitation_sensor = await sensor.new_sensor(config[CONF_PRECIPITATION])
        cg.add(my_sensor.set_precipitation_sensor(precipitation_sensor))

    # If precipitation intensity sensor is configured, create the sensor and link it
    if CONF_PRECIPITATION_INTENSITY in config:
        precipitation_intensity_sensor = await sensor.new_sensor(
            config[CONF_PRECIPITATION_INTENSITY]
        )
        cg.add(
            my_sensor.set_precipitation_intensity_sensor(precipitation_intensity_sensor)
        )
