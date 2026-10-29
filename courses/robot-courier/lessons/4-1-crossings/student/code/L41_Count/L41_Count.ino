const int LEFT_SENSOR_PIN = {{pins.leftSensor}};
const int RIGHT_SENSOR_PIN = {{pins.rightSensor}};
const int LEFT_DIR_PIN = {{pins.leftDir}};
const int LEFT_SPEED_PIN = {{pins.leftPwm}};
const int RIGHT_DIR_PIN = {{pins.rightDir}};
const int RIGHT_SPEED_PIN = {{pins.rightPwm}};
const int FORWARD = {{values.forwardLevel}};
const int BACKWARD = (FORWARD == HIGH) ? LOW : HIGH;

// Измерения и настройки из журнала (уроки 3.1 и 3.2).
const int LEFT_WHITE = 0;
const int LEFT_BLACK = 0;
const int RIGHT_WHITE = 0;
const int RIGHT_BLACK = 0;
float kp = 0.5;
int baseSpeed = 100;

int leftLevel = 100;
int rightLevel = 100;

int level(int value, int white, int black) {
  long result = (long)(value - black) * 100 / (white - black);
  return constrain(result, 0, 100);
}

void readSensors() {
  leftLevel = level(analogRead(LEFT_SENSOR_PIN), LEFT_WHITE, LEFT_BLACK);
  rightLevel = level(analogRead(RIGHT_SENSOR_PIN), RIGHT_WHITE, RIGHT_BLACK);
}

void drive(int leftDir, int leftSpeed, int rightDir, int rightSpeed) {
  digitalWrite(LEFT_DIR_PIN, leftDir);
  digitalWrite(RIGHT_DIR_PIN, rightDir);
  analogWrite(LEFT_SPEED_PIN, leftSpeed);
  analogWrite(RIGHT_SPEED_PIN, rightSpeed);
}

void stopMotors() {
  analogWrite(LEFT_SPEED_PIN, 0);
  analogWrite(RIGHT_SPEED_PIN, 0);
}

void followLineStep() {
  int error = leftLevel - rightLevel;
  int correction = kp * error;
  drive(FORWARD, constrain(baseSpeed + correction, 0, 255),
        FORWARD, constrain(baseSpeed - correction, 0, 255));
}

void setupRobot() {
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_SPEED_PIN, OUTPUT);
  stopMotors();
  // Без измерений робот не поедет.
  if (LEFT_WHITE == LEFT_BLACK || RIGHT_WHITE == RIGHT_BLACK) {
    while (true) {
    }
  }
  delay(2000);
}

// Перекрёсток: оба датчика видят чёрное.
bool onCrossing() {
  return leftLevel < 30 && rightLevel < 30;
}

// Ехать по линии, пока не найдём перекрёсток.
void followLineToCrossing() {
  while (true) {
    readSensors();
    if (onCrossing()) {
      return;
    }
    followLineStep();
  }
}

// Проехать перекрёсток прямо, пока датчики не съедут с чёрного.
void passCrossing() {
  drive(FORWARD, baseSpeed, FORWARD, baseSpeed);
  do {
    readSensors();
  } while (onCrossing());
  delay(100);
}

const int TARGET = 1; // на каком перекрёстке остановиться

void setup() {
  setupRobot();
  for (int i = 1; i < TARGET; i++) {
    followLineToCrossing();
    passCrossing();
  }
  followLineToCrossing();
  stopMotors();
}

void loop() {
}
