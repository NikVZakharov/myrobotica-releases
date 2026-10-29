// Шаблон среднего уровня. Напиши код в разделе «Твоя часть» по целям в комментариях.

const int LEFT_DIR_PIN = {{pins.leftDir}};
const int LEFT_SPEED_PIN = {{pins.leftPwm}};
const int RIGHT_DIR_PIN = {{pins.rightDir}};
const int RIGHT_SPEED_PIN = {{pins.rightPwm}};
const int FORWARD = {{values.forwardLevel}};
const int BACKWARD = (FORWARD == HIGH) ? LOW : HIGH;
int speed = 100;
int turnSpeed = 100;
int turn90Ms = 400;  // впиши своё время из журнала
int turn180Ms = 800; // впиши своё время из журнала

// ===== Твоя часть: напиши сам =====

void turnLeft() {
  // Поворот на месте налево на 90° по времени turn90Ms; в конце колёса стоят.
}

void turnRight() {
  // Поворот на месте направо на 90° по времени turn90Ms; в конце колёса стоят.
}

void turnAround() {
  // Разворот на месте на 180° по времени turn180Ms; в конце колёса стоят.
}

void setup() {
  setupMotors();
  delay(2000);

  // Квадрат: четыре раза — вперёд 1 секунду, пауза, поворот налево, пауза.
}

// ===== Готовое из урока 2.1 — не меняй =====

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

void setupMotors() {
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_SPEED_PIN, OUTPUT);
  stopMotors();
}

void forward(int ms) {
  drive(FORWARD, speed, FORWARD, speed);
  delay(ms);
  stopMotors();
}

void loop() {
}
