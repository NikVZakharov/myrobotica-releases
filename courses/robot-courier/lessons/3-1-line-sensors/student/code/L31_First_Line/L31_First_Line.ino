const int LEFT_SENSOR_PIN = {{pins.leftSensor}};
const int RIGHT_SENSOR_PIN = {{pins.rightSensor}};

// Впиши свои измерения из бортового журнала.
const int LEFT_WHITE = 0;
const int LEFT_BLACK = 0;
const int RIGHT_WHITE = 0;
const int RIGHT_BLACK = 0;

const int LEFT_DIR_PIN = {{pins.leftDir}};
const int LEFT_SPEED_PIN = {{pins.leftPwm}};
const int RIGHT_DIR_PIN = {{pins.rightDir}};
const int RIGHT_SPEED_PIN = {{pins.rightPwm}};
const int FORWARD = {{values.forwardLevel}};

int speed = 100; // начальная скорость, подбираем на подставке

void setup() {
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_SPEED_PIN, OUTPUT);

  analogWrite(LEFT_SPEED_PIN, 0);
  analogWrite(RIGHT_SPEED_PIN, 0);
  digitalWrite(LEFT_DIR_PIN, FORWARD);
  digitalWrite(RIGHT_DIR_PIN, FORWARD);

  // Без измерений робот не поедет: программа остановится здесь.
  if (LEFT_WHITE == LEFT_BLACK || RIGHT_WHITE == RIGHT_BLACK) {
    while (true) {
    }
  }

  delay(2000); // время убрать руки от робота
}

void loop() {
  int leftValue = analogRead(LEFT_SENSOR_PIN);
  int rightValue = analogRead(RIGHT_SENSOR_PIN);

  bool leftOnLine = abs(leftValue - LEFT_BLACK) < abs(leftValue - LEFT_WHITE);
  bool rightOnLine = abs(rightValue - RIGHT_BLACK) < abs(rightValue - RIGHT_WHITE);

  int leftSpeed = speed;
  int rightSpeed = speed;

  if (leftOnLine) {
    leftSpeed = 0;
  }
  if (rightOnLine) {
    rightSpeed = 0;
  }

  analogWrite(LEFT_SPEED_PIN, leftSpeed);
  analogWrite(RIGHT_SPEED_PIN, rightSpeed);
}
