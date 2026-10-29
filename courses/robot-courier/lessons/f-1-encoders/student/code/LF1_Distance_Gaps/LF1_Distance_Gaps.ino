// Шаблон среднего уровня. Напиши код в разделе «Твоя часть» по целям в комментариях.

// Контакты энкодеров: впиши номера из таблицы проводки своего робота.
// На Arduino Uno счёт по прерыванию работает только на контактах 2 и 3.
const int LEFT_ENCODER_PIN = -1;
const int RIGHT_ENCODER_PIN = -1;

const int LEFT_DIR_PIN = {{pins.leftDir}};
const int LEFT_SPEED_PIN = {{pins.leftPwm}};
const int RIGHT_DIR_PIN = {{pins.rightDir}};
const int RIGHT_SPEED_PIN = {{pins.rightPwm}};
const int FORWARD = {{values.forwardLevel}};

const int TICKS_PER_REV = 0; // импульсов на оборот колеса: измерь и впиши
const int WHEEL_DIAMETER_MM = {{values.wheelDiameterMm}};
const int DISTANCE_MM = 500; // сколько проехать
int speed = 100;

volatile long leftTicks = 0;
volatile long rightTicks = 0;

// ===== Твоя часть: напиши сам =====

long ticksFor(int mm, int ticksPerRev, int diameterMm) {
  // Сколько оборотов колеса нужно на mm миллиметров: один оборот — длина окружности колеса.
  // Сколько это импульсов, округлённо до целого. Число PI в Arduino уже есть.
  return 0;
}

long averageTicks() {
  // Среднее двух счётчиков. Читай их так, чтобы прерывание не изменило число посередине.
  return 0;
}

// ===== Готовое: энкодеры, моторы и поездка — не меняй =====

void countLeft() {
  leftTicks++;
}

void countRight() {
  rightTicks++;
}

void drive(int leftDir, int leftSpeed, int rightDir, int rightSpeed) {
  digitalWrite(LEFT_DIR_PIN, leftDir);
  digitalWrite(RIGHT_DIR_PIN, rightDir);
  analogWrite(LEFT_SPEED_PIN, leftSpeed);
  analogWrite(RIGHT_SPEED_PIN, rightSpeed);
}

void setupEncoders() {
  // Без контактов энкодеров программа дальше не пойдёт.
  if (LEFT_ENCODER_PIN < 0 || RIGHT_ENCODER_PIN < 0) {
    Serial.println("Впиши контакты энкодеров");
    while (true) {
    }
  }
  pinMode(LEFT_ENCODER_PIN, INPUT);
  pinMode(RIGHT_ENCODER_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_PIN), countLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_PIN), countRight, RISING);
}

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_SPEED_PIN, OUTPUT);
  drive(FORWARD, 0, FORWARD, 0);
  setupEncoders();

  // Без числа импульсов на оборот робот не поедет.
  if (TICKS_PER_REV <= 0) {
    Serial.println("Впиши число импульсов на оборот");
    while (true) {
    }
  }
  delay(2000); // время убрать руки от робота

  long target = ticksFor(DISTANCE_MM, TICKS_PER_REV, WHEEL_DIAMETER_MM);
  drive(FORWARD, speed, FORWARD, speed);
  while (averageTicks() < target) {
  }
  drive(FORWARD, 0, FORWARD, 0);
  delay(1000); // робот докатывается

  Serial.print("Цель, импульсов: ");
  Serial.println(target);
  Serial.print("Насчитано после остановки: ");
  Serial.println(averageTicks());
}

void loop() {
}
