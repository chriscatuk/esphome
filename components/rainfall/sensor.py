from esphome import pins
import esphome.codegen as cg
from esphome.components import sensor, uart
import esphome.config_validation as cv


async def to_code(config):
    # Create a new variable for the RainfallSensor.
    uartID = "hello"
