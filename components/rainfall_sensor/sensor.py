from esphome import pins
import esphome.codegen as cg
from esphome.components import sensor, uart
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_UART_ID

CODEOWNERS = ["@chriscatuk"]

MULTI_CONF = True

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["sensor", "text_sensor"]

CONF_REQUEST_INTERVAL = "request_interval"
CONF_REQUEST_PIN = "request_pin"


# Hack to prevent compile error due to ambiguity with lib namespace
rainfall_sensor_ns = cg.esphome_ns.namespace("esphome::rainfall_sensor")
RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", cg.Component, uart.UARTDevice
)

# Define the schema for your configuration.
CONFIG_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.declare_id(RainfallSensor),
        cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    }
).extend(cv.COMPONENT_SCHEMA)


# The async function to generate the code for this sensor.
async def to_code(config):
    # Create a new variable for the RainfallSensor.
    var = cg.new_Pvariable(config[CONF_ID])

    # Register the component (this makes it known to ESPHome).
    await cg.register_component(var, config)

    # Register the sensor itself (this makes it an actual sensor component in ESPHome).
    await sensor.register_sensor(var, config)

    # Retrieve the UART component from the configuration.
    uart_component = await cg.get_variable(config[CONF_UART_ID])

    # Register the UART device and associate it with the rainfall sensor.
    await uart.register_uart_device(var, uart_component)
