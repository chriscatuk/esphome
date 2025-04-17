import esphome.codegen as cg
from esphome.components import uart

rainfall_sensor_ns = cg.esphome_ns.namespace("rainfall_sensor")
RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", cg.Component, uart.UARTDevice
)
