import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ['uart']

rainfall_sensor_ns = cg.esphome_ns.namespace('rainfall_sensor')
RainfallSensor = rainfall_sensor_ns.class_('RainfallSensor', sensor.Sensor, cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RainfallSensor),
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
}).extend(cv.polling_component_schema('60s'))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await sensor.register_sensor(var, config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config[CONF_UART_ID])

    cg.add(var.set_uart_parent(await cg.get_variable(config[CONF_UART_ID])))

