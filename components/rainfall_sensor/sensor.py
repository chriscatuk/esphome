from esphome.components import sensor
from esphome.components import uart
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_ID,
    CONF_NAME,
    UNIT_MILLIMETER,
    ICON_WATER,
    CONF_UART_ID,
)

from . import rainfall_sensor_ns, RainfallSensor

CONFIG_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_MILLIMETER,
    icon=ICON_WATER,
    accuracy_decimals=2,
).extend(
    {
        cv.GenerateID(): cv.declare_id(RainfallSensor),
        cv.Required(CONF_ID): cv.declare_id(RainfallSensor),
        cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    uart_component = await cg.get_variable(config[CONF_UART_ID])
    await uart.register_uart_device(var, uart_component)
