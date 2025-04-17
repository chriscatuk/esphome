# __init__.py

# core vs cg: core in the older versions of ESPHome
from esphome import cg, uart

rainfall_sensor_ns = cg.esphome_ns.namespace("rainfall_sensor")

RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", cg.Component, uart.UARTDevice
)
