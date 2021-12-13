//verze programu pro zobrazení v serial portu
const string APP_VERSION = "0.0.1";

//nastavení PIN
const int PIN_VYKO_SERVO = 9;     // The GPIO number of the pin where the lid opener servo is connected.
const int PIN_PREPINAC_SERVO = 10;  // The GPIO number of the pin where the switch manipulator servo is connected.
const int PIN_PREPINAC = 5;        // The GPIO number of the pin where the switch is connected.

//Konstanty nastavení pozice
const int LID_START_POSITION = 90;
const int LID_END_POSITION = 40;
const int SWITCH_START_POSITION = 0;
const int SWITCH_END_POSITION = 145;
const int SWITCH_HALF_POSITION = 90;