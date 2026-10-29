const int LEFT_DIR_PIN = {{pins.leftDir}};
const int LEFT_SPEED_PIN = {{pins.leftPwm}};
const int FORWARD = {{values.forwardLevel}};

void setup() {
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);

  digitalWrite(LEFT_DIR_PIN, FORWARD);
  analogWrite(LEFT_SPEED_PIN, 100);
  delay(2000);
  analogWrite(LEFT_SPEED_PIN, 0);
}

void loop() {
}
