// Шаблон среднего уровня. Напиши код в разделе «Твоя часть» по целям в комментариях.
// Функции drive и forward ниже — образец.

const int LEFT_DIR_PIN = {{pins.leftDir}};
const int LEFT_SPEED_PIN = {{pins.leftPwm}};
const int RIGHT_DIR_PIN = {{pins.rightDir}};
const int RIGHT_SPEED_PIN = {{pins.rightPwm}};
const int FORWARD = {{values.forwardLevel}};
const int BACKWARD = (FORWARD == HIGH) ? LOW : HIGH;
int speed = 100;

// ===== Твоя часть: напиши сам =====

void backward(int ms) {
  // Оба колеса крутятся назад со скоростью speed ms миллисекунд.
}

void stopMotors() {
  // Оба мотора стоят.
}

void setup() {
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_SPEED_PIN, OUTPUT);
  stopMotors();
  delay(2000); // время убрать руки от робота

  // Вперёд 1 секунду, остановка, пауза полсекунды, назад 1 секунду, остановка.
}

// ===== Образец — не меняй =====

void drive(int leftDir, int leftSpeed, int rightDir, int rightSpeed) {
  digitalWrite(LEFT_DIR_PIN, leftDir);
  digitalWrite(RIGHT_DIR_PIN, rightDir);
  analogWrite(LEFT_SPEED_PIN, leftSpeed);
  analogWrite(RIGHT_SPEED_PIN, rightSpeed);
}

void forward(int ms) {
  drive(FORWARD, speed, FORWARD, speed);
  delay(ms);
}

void loop() {
}
