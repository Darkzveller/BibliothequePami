#include <Arduino.h>
#include <SoftwareSerial.h>
#include <HerkulexServo.h>
#include "rgb_lcd.h"

rgb_lcd lcd;


#define PIN_SW_RX PB2
#define PIN_SW_TX PB1
#define SERVO_ID 0xFE

SoftwareSerial servo_serial(PIN_SW_RX, PIN_SW_TX);
HerkulexServoBus herkulex_bus(servo_serial);
HerkulexServo my_servo(herkulex_bus, SERVO_ID);

unsigned long last_update = 0;
unsigned long now = 0;
bool toggle = false;

int position;

void setup() {
  Serial.begin(115200);
  servo_serial.begin(115200);
  delay(500);
  my_servo.setTorqueOn();  // turn power on
  lcd.begin(16, 2);
  lcd.setRGB(255, 255, 0);
  my_servo.setTorqueOff();
}
int i = 0;
void loop() {
  herkulex_bus.update();

  now = millis();
  if (i == 0) {
    my_servo.setTorqueOn();  // turn power on
    herkulex_bus.prepareIndividualMove();
    my_servo.setPosition(512, 80);
    herkulex_bus.executeMove();
    delay(100 * 11.2f);
    // my_servo.setTorqueOn();  // turn power on
    herkulex_bus.prepareIndividualMove();
    my_servo.setPosition(820, 80);
    herkulex_bus.executeMove();
    delay(100 * 11.2f);
    i = 1;
    Serial.println("Je passe par la");
  }
  position = my_servo.getPosition();


  Serial.println(position);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("position: ");
  lcd.setCursor(0, 1);
  lcd.print(position);

  // if ( (now - last_update) > 1000) {
  //   // called every 1000 ms
  //   if (toggle) {
  //     // move to -90° over a duration of 560ms, set LED to green
  //     // 512 - 90°/0.325 = 235
  //     my_servo.setPosition(235, 100, HerkulexLed::Green);
  //   } else {
  //     // move to +90° over a duration of 560ms, set LED to blue
  //     // 512 + 90°/0.325 = 789
  //     my_servo.setPosition(789, 100, HerkulexLed::Blue);
  //   }

  //   last_update = now;
  //   toggle = !toggle;
  // }
}