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

# # Not available in ESPHome, so define it manually:
UNIT_MILLIMETER_PER_HOUR = "mm/h"

# CODEOWNERS = ["@chriscatuk"]

# MULTI_CONF = True

# DEPENDENCIES = ["uart"]
# AUTO_LOAD = ["sensor", "text_sensor"]

# CONF_PRECIPITATION = "precipitation"
# CONF_PRECIPITATION_INTENSITY = "precipitation_intensity"

CONFIG_SCHEMA = cv.Schema(
    {cv.Optional(CONF_UART_ID): cv.use_id(uart.UARTComponent)}
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    # Create a new variable for the RainfallSensor.
    uartID = "hello"
