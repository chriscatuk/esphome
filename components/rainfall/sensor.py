from esphome import pins
import esphome.codegen as cg
from esphome.components import sensor, uart
import esphome.config_validation as cv
from esphome.const import (
    CONF_UART_ID,
)


CONFIG_SCHEMA = cv.Schema(
    {cv.Optional(CONF_UART_ID): cv.use_id(uart.UARTComponent)}
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    # Create a new variable for the RainfallSensor.
    uartID = "hello"
