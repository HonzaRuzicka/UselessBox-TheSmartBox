const char* APP_VERSION = "0.0.1";

const int PIN_LID_SERVO = 9;     // The GPIO number of the pin where the lid opener servo is connected.
const int PIN_SWITCH_SERVO = 10;  // The GPIO number of the pin where the switch manipulator servo is connected.
const int PIN_SWITCH = 5;        // The GPIO number of the pin where the switch is connected.
const int PIN_SENSOR_SDA = 2;    // The GPIO number of the pin where the SDA pin of the APDS-9660 sensor is connected.
const int PIN_SENSOR_SCL = 1;    // The GPIO number of the pin where the SCL pin of the APDS-9660 sensor is connected.
const uint8_t SENSOR_TRIGGER_THRESHOLD = 100;  // The proximity value level that triggers a lid opening. (lower=brighter, higher=darker)

const int LID_START_POSITION = 90;
const int LID_END_POSITION = 40;
const int SWITCH_START_POSITION = 0;
const int SWITCH_END_POSITION = 145;
const int SWITCH_HALF_POSITION = 90;