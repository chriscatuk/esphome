from esphome.components import sensor, uart
import esphome.codegen as cg
import esphome.config_validation as cv

DEPENDENCIES = ["uart"]
CODEOWNERS = ["@your-github"]

rainfall_sensor_ns = cg.esphome_ns.namespace("rainfall_sensor")
RainfallSensor = rainfall_sensor_ns.class_(
    "RainfallSensor", cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(RainfallSensor),
        cv.Required("rainfall"): sensor.sensor_schema(
            unit_of_measurement="mm", accuracy_decimals=1
        ),
    }
).extend(cv.polling_component_schema("60s"))


async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    sens = await sensor.new_sensor(config["rainfall"])
    cg.add(var.set_sensor(sens))
