const int LEFT_SENSOR_PIN = {{pins.leftSensor}};
const int RIGHT_SENSOR_PIN = {{pins.rightSensor}};

void setup() {
  Serial.begin(9600);
}

void loop() {
  int leftValue = analogRead(LEFT_SENSOR_PIN);
  int rightValue = analogRead(RIGHT_SENSOR_PIN);

  Serial.print("L=");
  Serial.print(leftValue);
  Serial.print("  R=");
  Serial.println(rightValue);

  delay(200);
}
