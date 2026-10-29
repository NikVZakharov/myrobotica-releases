#include <Servo.h>

// Контакт сервопривода захвата: впиши номер из таблицы проводки своего робота.
const int SERVO_PIN = -1;

int angle = 90; // меняй понемногу, чтобы найти «открыто» и «закрыто»

Servo gripper;

void setup() {
  if (SERVO_PIN < 0) {
    while (true) {
    }
  }
  gripper.attach(SERVO_PIN);
  gripper.write(angle);
}

void loop() {
}
