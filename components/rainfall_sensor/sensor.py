import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_ID,
    CONF_NAME,
    CONF_UNIT_OF_MEASUREMENT,
    CONF_ACCURACY_DECIMALS,
)

CODEOWNERS = ["@chriscatuk"]
DEPENDENCIES = ["uart"]

rainfall_sensor_ns = cg.esphome_ns.namespace("rainfall_sensor")
RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", cg.PollingComponent, uart.UARTDevice, sensor.Sensor
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(unit_of_measurement="mm", accuracy_decimals=2)
    .extend(
        {
            cv.GenerateID(): cv.declare_id(RainfallSensor),
            cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
        }
    )
    .extend(cv.polling_component_schema("60s"))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config["uart_id"])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    await uart.register_uart_device(var, config)
