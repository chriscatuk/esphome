from esphome.components import uart
import esphome.codegen as cg

rainfall_sensor_ns = cg.esphome_ns.namespace("rainfall_sensor")
RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", cg.Component, uart.UARTDevice
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield sensor.register_sensor(var, config)
    yield uart.register_uart_device(var, config[CONF_UART_ID])
