# __init__.py
from esphome import pins
import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_UART_ID

CODEOWNERS = ["@chriscatuk"]

MULTI_CONF = True

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["sensor", "text_sensor"]

CONF_REQUEST_INTERVAL = "request_interval"
CONF_REQUEST_PIN = "request_pin"

# rainfall_sensor_ns = cg.esphome_ns.namespace("rainfall_sensor")

# RainfallSensor = rainfall_sensor_ns.class_(
#     "RainfallSensor", cg.Component, uart.UARTDevice
# )
