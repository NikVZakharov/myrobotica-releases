#include <Servo.h>

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

// Контакты ультразвукового датчика: впиши номера из таблицы проводки своего робота.
const int TRIG_PIN = -1;
const int ECHO_PIN = -1;

// Расстояние в сантиметрах или -1, если эхо не вернулось.
int readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long echoUs = pulseIn(ECHO_PIN, HIGH, 25000);
  if (echoUs == 0) {
    return -1;
  }
  return echoUs / 58;
}

void setupSonar() {
  // Без контактов датчика программа дальше не пойдёт.
  if (TRIG_PIN < 0 || ECHO_PIN < 0) {
    while (true) {
    }
  }
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

int turnSpeed = 100;
int centerMs = 250; // подбираем: проехать от датчиков до центра перекрёстка
int leaveMs = 200;  // время, чтобы датчик ушёл со старой линии

// Выехать на центр перекрёстка: датчики стоят впереди колёс.
void toCenter() {
  drive(FORWARD, baseSpeed, FORWARD, baseSpeed);
  delay(centerMs);
  stopMotors();
}

// Крутиться на месте, пока датчик со стороны поворота не найдёт новую линию.
void turnUntilLine(bool left) {
  if (left) {
    drive(BACKWARD, turnSpeed, FORWARD, turnSpeed);
  } else {
    drive(FORWARD, turnSpeed, BACKWARD, turnSpeed);
  }
  delay(leaveMs);
  do {
    readSensors();
  } while ((left ? leftLevel : rightLevel) > 30);
  stopMotors();
}

void turnLeftAtCrossing() {
  toCenter();
  turnUntilLine(true);
}

void turnRightAtCrossing() {
  toCenter();
  turnUntilLine(false);
}

// Развернуться на линии: крутиться, пока линия снова не окажется под датчиком.
void turnAroundOnLine() {
  turnUntilLine(true);
}

// Ехать по линии заданное время.
void followLineFor(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    readSensors();
    followLineStep();
  }
  stopMotors();
}

// Сервопривод захвата: впиши контакт и свои углы из журнала.
const int SERVO_PIN = -1;
const int OPEN_ANGLE = 90;
const int CLOSED_ANGLE = 40;
const int STOP_CM = 5;
Servo gripper;

void setupGripper() {
  // Без контакта сервопривода программа дальше не пойдёт.
  if (SERVO_PIN < 0) {
    while (true) {
    }
  }
  gripper.attach(SERVO_PIN);
  gripper.write(OPEN_ANGLE);
  delay(500);
}

// Ехать по линии и остановиться перед грузом по ультразвуку.
void approachCan() {
  while (true) {
    int distance = readDistanceCm();
    if (distance > 0 && distance <= STOP_CM) {
      break;
    }
    readSensors();
    followLineStep();
  }
  stopMotors();
}

// Сначала остановиться, потом закрыть захват.
void pickUp() {
  stopMotors();
  gripper.write(CLOSED_ANGLE);
  delay(600);
}

// Открыть захват, подождать и только потом отъехать назад.
void putDown() {
  stopMotors();
  gripper.write(OPEN_ANGLE);
  delay(600);
  drive(BACKWARD, baseSpeed, BACKWARD, baseSpeed);
  delay(300);
  stopMotors();
}

const unsigned long CARRY_MS = 1500; // сколько ехать по линии с грузом

void setup() {
  setupSonar();
  setupGripper();
  setupRobot();

  approachCan();
  pickUp();
  turnAroundOnLine();
  followLineFor(CARRY_MS);
  putDown();
}

void loop() {
}
