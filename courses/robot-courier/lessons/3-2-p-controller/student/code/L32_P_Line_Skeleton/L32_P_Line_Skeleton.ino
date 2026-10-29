// Каркас П-регулятора. Требования к программе — в тексте урока, шаг за шагом.
const int LEFT_SENSOR_PIN = {{pins.leftSensor}};
const int RIGHT_SENSOR_PIN = {{pins.rightSensor}};

// Измерения белого и чёрного из журнала (урок 3.1).
const int LEFT_WHITE = 0;
const int LEFT_BLACK = 0;
const int RIGHT_WHITE = 0;
const int RIGHT_BLACK = 0;

const int LEFT_DIR_PIN = {{pins.leftDir}};
const int LEFT_SPEED_PIN = {{pins.leftPwm}};
const int RIGHT_DIR_PIN = {{pins.rightDir}};
const int RIGHT_SPEED_PIN = {{pins.rightPwm}};
const int FORWARD = {{values.forwardLevel}};

void drive(int leftDir, int leftSpeed, int rightDir, int rightSpeed) {
  digitalWrite(LEFT_DIR_PIN, leftDir);
  digitalWrite(RIGHT_DIR_PIN, rightDir);
  analogWrite(LEFT_SPEED_PIN, leftSpeed);
  analogWrite(RIGHT_SPEED_PIN, rightSpeed);
}

// Требование 1: шкала «чёрное — 0, белое — 100».
int level(int value, int white, int black) {
  return 0;
}

void setup() {
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_SPEED_PIN, OUTPUT);
  drive(FORWARD, 0, FORWARD, 0);

  // Без измерений робот не поедет. Эту защиту не удаляй.
  if (LEFT_WHITE == LEFT_BLACK || RIGHT_WHITE == RIGHT_BLACK) {
    while (true) {
    }
  }
  delay(2000);
}

void loop() {
  // Требования 2 и 3: ошибка, поправка и скорости колёс.
  drive(FORWARD, 0, FORWARD, 0);
}
