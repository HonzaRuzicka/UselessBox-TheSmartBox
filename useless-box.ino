//Nutné knihovny
#include <Arduino.h>  // To add IntelliSense for platform constants.
#include <Servo.h>

//Moje Knihovny
#include "status-led.h";
#include "config.h"; //nastavení

Servo lidServo;
Servo switchServo;
StatusLed led;
//ProximitySensor sensor;

int lastSwitchState = 0;
long playCount = 0;
bool isLidOpen = false;
bool monitorSensor = false;

void setup() {
  initSerial();
  initServos();
  //initLed();
  //initSensor();
  pinMode(PIN_SWITCH, INPUT);

  Serial.print("Application version: ");
  Serial.println(APP_VERSION);
  Serial.println("Setup completed.");
}

void initSerial() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Initializing serial connection DONE.");
}

void initServos() {
  lidServo.attach(PIN_LID_SERVO);
  lidServo.write(LID_START_POSITION);

  switchServo.attach(PIN_SWITCH_SERVO);
  switchServo.write(SWITCH_START_POSITION);
}

//void initLed() {
//  led.setPin(LED_BUILTIN);
//  led.turnOff();
//}

//void initSensor() {
//  sensor.attach(PIN_SENSOR_SDA, PIN_SENSOR_SCL, SENSOR_TRIGGER_THRESHOLD);
//}

void loop() {
  int switchState = digitalRead(PIN_SWITCH);
  boolean isSwitchTurnedOn = (switchState != lastSwitchState) && (switchState == LOW);
  


  if (isSwitchTurnedOn) {
   // led.turnOn();
    Serial.println("Switch-On");
    run();
    isLidOpen = false;
   // led.turnOff();
  } else {
    // Check the proximity sensor.
    //if (sensor.isInRange()) {
    //  if (!isLidOpen && monitorSensor) {
    //    openLidFast();
    //    isLidOpen = true;
    //  }
   // } else {
      if (isLidOpen) {
        closeLidFast();
        isLidOpen = false;
      }
    //}
  }

  lastSwitchState = switchState;

  // Wait 250 ms before next reading (required for the sensor).
  delay(250);
}

void run() {
  switch (playCount % 10) {
    case 0:
    case 1:
      Serial.println("Case-1");
      runSlow();
      break;
    case 2:
      Serial.println("Case-2");
      runWaitThenFast();
      break;
    case 3:
      Serial.println("Case-3");
      runFast();
      break;
    case 4:
      Serial.println("Case-4");
      runFastThenClap();
      monitorSensor = true;
      break;
    case 5:
      Serial.println("Case-5");
      runOpenCloseThenFast();
      monitorSensor = false;
      break;
    case 6:
      Serial.println("Case-6");
      runPeekThenFast();
      break;
    case 7:
      Serial.println("Case-7");
      runFastWithDelay();
      monitorSensor = true;
      break;
    case 8:
      Serial.println("Case-8");
      runClap();
      monitorSensor = false;
      break;
    case 9:
      Serial.println("Case-9");
      runHalf();
      break;
    default:
      break;
  }

  playCount++;
}

void runSlow() {
  Serial.println("runSlow");
  openLidSlow();
  //flipSwitchSlow();
  closeLidSlow();
}

void runWaitThenFast() {
  delay(5000);
  flipSwitchFast();
}

void runFast() {
  flipSwitchFast();
}

void runFastThenClap() {
  flipSwitchFast();
  clapLid();
}

void runOpenCloseThenFast() {
  openLidSlow();
  delay(2000);
  closeLidSlow();
  delay(2000);
  flipSwitchFast();
}

void runPeekThenFast() {
  switchServo.write(SWITCH_HALF_POSITION);
  delay(3000);
  switchServo.write(SWITCH_START_POSITION);
  delay(3000);
  flipSwitchFast();
}

void runFastWithDelay() {
  openLidSlow();
  delay(4000);
  flipSwitchFast();
  closeLidFast();
}

void runClap() {
  clapLid();
  clapLid();
  clapLid();
  clapLid();
  openLidFast();
  flipSwitchFast();
  closeLidFast();
}

void runHalf() {
  switchServo.write(SWITCH_HALF_POSITION);
  delay(3000);
  switchServo.write(SWITCH_END_POSITION);
  switchServo.write(SWITCH_START_POSITION);
}

void openLidSlow() {
  Serial.println("OpenLidSlow");
  for (int pos = LID_START_POSITION; pos <= LID_END_POSITION; pos += 1) { 
    lidServo.write(pos);  
    delay(5);
  }
}

void openLidFast() {
  Serial.println("OpenLidFast");
  lidServo.write(LID_END_POSITION);
}

void closeLidSlow() {
  lidServo.write(LID_START_POSITION);
}

void closeLidFast() {
  lidServo.write(LID_START_POSITION);
}

void clapLid() {
  openLidFast();
  closeLidFast();
}

void flipSwitchSlow() {
  switchServo.write(SWITCH_END_POSITION);
  switchServo.write(SWITCH_START_POSITION);
}

void flipSwitchFast() {
  switchServo.write(SWITCH_END_POSITION);
  switchServo.write(SWITCH_START_POSITION);
}
