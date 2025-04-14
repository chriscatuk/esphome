import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_NAME, UNIT_MILLIMETER, ICON_WATER, DEVICE_CLASS_RAINFALL

rainfall_sensor_ns = cg.esphome_ns.namespace("rainfall_sensor")
RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", sensor.Sensor, cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = sensor.sensor_schema(
    UNIT_MILLIMETER, ICON_WATER, 2, DEVICE_CLASS_RAINFALL
).extend(
    {
        cv.GenerateID(): cv.declare_id(RainfallSensor),
        cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
    }
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
