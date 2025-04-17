from esphome.components import sensor
from esphome.components.uart import UARTComponent, uart
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_NAME,
    UNIT_MILLIMETER,
    ICON_WATER,
    CONF_UART_ID,
)
from esphome import automation
from esphome import pins

from . import rainfall_sensor_ns, RainfallSensor

RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", sensor.Sensor, uart.UARTDevice
)

CONFIG_SCHEMA = sensor.sensor_schema(
    RainfallSensor,
    unit_of_measurement=UNIT_MILLIMETER,
    icon=ICON_WATER,
    accuracy_decimals=2,
).extend(
    {
        cv.GenerateID(): cv.declare_id(RainfallSensor),
        cv.Required(CONF_UART_ID): cv.use_id(UARTComponent),
    }
)
