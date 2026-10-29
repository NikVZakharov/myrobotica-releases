const int LEFT_SENSOR_PIN = {{pins.leftSensor}};
const int RIGHT_SENSOR_PIN = {{pins.rightSensor}};

// Впиши свои измерения из бортового журнала.
const int LEFT_WHITE = 0;
const int LEFT_BLACK = 0;
const int RIGHT_WHITE = 0;
const int RIGHT_BLACK = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int leftValue = analogRead(LEFT_SENSOR_PIN);
  int rightValue = analogRead(RIGHT_SENSOR_PIN);

  bool leftOnLine = abs(leftValue - LEFT_BLACK) < abs(leftValue - LEFT_WHITE);
  bool rightOnLine = abs(rightValue - RIGHT_BLACK) < abs(rightValue - RIGHT_WHITE);

  Serial.print("L=");
  Serial.print(leftValue);
  Serial.print("  R=");
  Serial.print(rightValue);

  if (leftOnLine) {
    Serial.print("  слева линия");
  }
  if (rightOnLine) {
    Serial.print("  справа линия");
  }

  Serial.println();
  delay(200);
}
