from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_NAME,
    UNIT_MILLIMETER,
    ICON_WATER,
)
from . import rainfall_sensor_ns, RainfallSensor

CONFIG_SCHEMA = sensor.sensor_schema(
    RainfallSensor,
    unit_of_measurement=UNIT_MILLIMETER,
    icon=ICON_WATER,
    accuracy_decimals=1,
    # device_class='rainfall',  # ❌ Not supported — REMOVE this
).extend(
    {
        cv.GenerateID(): cv.declare_id(RainfallSensor),
    }
)
