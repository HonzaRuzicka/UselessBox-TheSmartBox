//Nutné knihovny
#include <Arduino.h>
#include <Servo.h>

//verze programu pro zobrazení v serial portu
const char* APP_VERSION = "0.0.1";

//nastavení PIN
const int PIN_VYKO_SERVO = 9;     // The GPIO number of the pin where the lid opener servo is connected.
const int PIN_PREPINAC_SERVO = 10;  // The GPIO number of the pin where the switch manipulator servo is connected.
const int PIN_PREPINAC = 5;        // The GPIO number of the pin where the switch is connected.

//Konstanty nastavení pozice
const int VYKO_START_POSITION = 180;
const int VYKO_END_POSITION = 120;
const int PREPINAC_START_POSITION = 0;
const int PREPINAC_END_POSITION = 160;
const int PREPINAC_HALF_POSITION = 90;

Servo vykoServo;
Servo prepinacServo;

int lastSwitchState = 0;
long playCount = 0;
bool isLidOpen = false;
bool monitorSensor = false;

void setup() {
  initSerial();
  initServos();
  pinMode(PIN_PREPINAC, INPUT);

  Serial.print("Verze: ");
  Serial.println(APP_VERSION);
  Serial.println("Setup Dokoncen.");
}

void initSerial() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Inicializace SerialConcetion OK.");
}

void initServos() {
  vykoServo.attach(PIN_VYKO_SERVO);
  vykoServo.write(VYKO_START_POSITION);

  prepinacServo.attach(PIN_PREPINAC_SERVO);
  prepinacServo.write(PREPINAC_START_POSITION);
}

void loop() {
  int switchState = digitalRead(PIN_PREPINAC);
  boolean isSwitchTurnedOn = (switchState != lastSwitchState) && (switchState == LOW);
  


  if (isSwitchTurnedOn) {
    Serial.println("Switch-On");
    run();
  }

  lastSwitchState = switchState;

  // Wait 250 ms before next reading (required for the sensor).
  delay(250);
}

void run() {
  switch (playCount % 1) {
    case 0:
      Serial.println("Case-0");
      runSlowvyko();
      break;
    case 1:
      Serial.println("Case-1");
      runSlowprepinac();
      break;
    default:
      break;
  }

  playCount++;
}

void runSlowvyko() {
  Serial.println("runSlow-vyko");
  openLidSlow();
  delay(1000);
  closeLidSlow();
}

void runSlowprepinac() {
  Serial.println("runSlow-prepinac");
  openSwitchSlow();
  closeSwitchSlow();
}


void openLidSlow() {
  Serial.println("OpenLidSlow");
  for (int pos = VYKO_START_POSITION; pos >= VYKO_END_POSITION; pos -= 1) { 
    vykoServo.write(pos);  
    delay(10);
  }
}

void closeLidSlow() {
  Serial.println("CloseLidSlow");
  for (int pos = VYKO_END_POSITION; pos <= VYKO_START_POSITION; pos += 1) { 
    vykoServo.write(pos);  
    delay(10);
  }
}

void openSwitchSlow() {
  Serial.println("OpenSwitchSlow");
  for (int pos = PREPINAC_START_POSITION; pos <= PREPINAC_END_POSITION; pos += 1) { 
    prepinacServo.write(pos);  
    delay(10);
  }
}

void closeSwitchSlow() {
  Serial.println("CloseSwitchSlow");
  for (int pos = PREPINAC_END_POSITION; pos >= PREPINAC_START_POSITION; pos -= 1) { 
    prepinacServo.write(pos);  
    delay(10);
  }
}