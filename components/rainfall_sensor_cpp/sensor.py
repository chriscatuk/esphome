import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import (
    CONF_ID,
    CONF_NAME,
    CONF_UNIT_OF_MEASUREMENT,
    CONF_ACCURACY_DECIMALS,
)

rainfall_sensor_ns = cg.esphome_ns.namespace("rainfall_sensor")
RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", sensor.Sensor, cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = (
    sensor.sensor_schema()
    .extend(
        {
            cv.GenerateID(): cv.declare_id(RainfallSensor),
            cv.Optional(CONF_UNIT_OF_MEASUREMENT, default="mm"): cv.string_strict,
            cv.Optional(CONF_ACCURACY_DECIMALS, default=2): cv.int_,
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    cg.add(var)
