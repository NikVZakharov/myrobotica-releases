#include <EEPROM.h>

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

// Регулятор заезда: 0 — релейный, 1 — П, 2 — ПД, 3 — ПИД.
const int MODE = 1;
int baseSpeed = 100; // одна скорость для всех регуляторов
float kp = 0.5;      // твой kp из урока 3.2
float kd = 0;        // Д: реакция на то, как быстро уходит линия
float ki = 0;        // И: реакция на ошибку, которая копится
const long SUM_LIMIT = 3000;       // предел накопленной ошибки
const unsigned long RUN_MS = 6000; // длина заезда: робот должен остановиться до конца дорожки
const unsigned long STEP_MS = 10;  // шаг регулятора: 100 раз в секунду

int lastError = 0;
long errorSum = 0;

// Итоги заезда: хранятся в памяти Arduino и после выключения.
struct Result {
  int marker;
  int mode;
  int baseSpeed;
  float kp;
  float kd;
  float ki;
  long steps;
  long sumAbs;
  int maxAbs;
  int crossings;
};

// Переводит показание в шкалу: чёрное — 0, белое — 100.
int level(int value, int white, int black) {
  long result = (long)(value - black) * 100 / (white - black);
  return constrain(result, 0, 100);
}

void drive(int leftDir, int leftSpeed, int rightDir, int rightSpeed) {
  digitalWrite(LEFT_DIR_PIN, leftDir);
  digitalWrite(RIGHT_DIR_PIN, rightDir);
  analogWrite(LEFT_SPEED_PIN, leftSpeed);
  analogWrite(RIGHT_SPEED_PIN, rightSpeed);
}

// Поправка П-, ПД- или ПИД-регулятора по ошибке этого шага.
int controller(int mode, int error) {
  float correction = kp * error;
  if (mode >= 2) {
    correction += kd * (error - lastError);
  }
  if (mode == 3) {
    errorSum = constrain(errorSum + error, -SUM_LIMIT, SUM_LIMIT);
    correction += ki * errorSum;
  }
  lastError = error;
  return correction;
}

// ===== Измерение заезда =====

const int MARKER = 2610; // признак того, что в памяти записан заезд
Result run;
int lastSide = 0;
unsigned long startTime;
unsigned long nextStep;

// Добавляет ошибку шага к итогам заезда.
void record(int error) {
  run.steps++;
  run.sumAbs += abs(error);
  if (abs(error) > run.maxAbs) {
    run.maxAbs = abs(error);
  }
  int side = 0;
  if (error > 10) {
    side = 1;
  }
  if (error < -10) {
    side = -1;
  }
  if (side != 0 && lastSide != 0 && side != lastSide) {
    run.crossings++;
  }
  if (side != 0) {
    lastSide = side;
  }
}

void printResult(Result r) {
  const char *names[] = {"релейный", "П", "ПД", "ПИД"};
  Serial.print("Регулятор: ");
  Serial.print(names[r.mode]);
  Serial.print("  скорость=");
  Serial.print(r.baseSpeed);
  Serial.print("  kp=");
  Serial.print(r.kp);
  Serial.print("  kd=");
  Serial.print(r.kd);
  Serial.print("  ki=");
  Serial.println(r.ki, 3);
  Serial.print("Средняя ошибка: ");
  Serial.println(r.steps > 0 ? (float)r.sumAbs / r.steps : 0, 1);
  Serial.print("Наибольшая ошибка: ");
  Serial.println(r.maxAbs);
  Serial.print("Переходов через линию: ");
  Serial.println(r.crossings);
}

// Ждёт, пока робот стоит на старте: оба датчика видят белое 1 секунду подряд.
void waitForStart() {
  Serial.println("Поставь робота на старт: линия между датчиками");
  unsigned long whiteSince = millis();
  while (millis() - whiteSince < 1000) {
    int leftLevel = level(analogRead(LEFT_SENSOR_PIN), LEFT_WHITE, LEFT_BLACK);
    int rightLevel = level(analogRead(RIGHT_SENSOR_PIN), RIGHT_WHITE, RIGHT_BLACK);
    if (leftLevel < 70 || rightLevel < 70) {
      whiteSince = millis();
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_SPEED_PIN, OUTPUT);
  drive(FORWARD, 0, FORWARD, 0);

  Result last;
  EEPROM.get(0, last);
  if (last.marker == MARKER && last.mode >= 0 && last.mode <= 3) {
    Serial.println("Прошлый заезд:");
    printResult(last);
  } else {
    Serial.println("Записанных заездов нет");
  }

  // Без измерений робот не поедет.
  if (LEFT_WHITE == LEFT_BLACK || RIGHT_WHITE == RIGHT_BLACK) {
    Serial.println("Впиши измерения белого и чёрного");
    while (true) {
    }
  }
  waitForStart();
  delay(2000); // время убрать руки от робота

  run = {MARKER, MODE, baseSpeed, kp, kd, ki, 0, 0, 0, 0};
  startTime = millis();
  nextStep = startTime;
}

void loop() {
  if (millis() - startTime >= RUN_MS) {
    drive(FORWARD, 0, FORWARD, 0);
    EEPROM.put(0, run);
    Serial.println("Заезд окончен:");
    printResult(run);
    while (true) {
    }
  }
  while (millis() < nextStep) {
  }
  nextStep += STEP_MS;

  int leftLevel = level(analogRead(LEFT_SENSOR_PIN), LEFT_WHITE, LEFT_BLACK);
  int rightLevel = level(analogRead(RIGHT_SENSOR_PIN), RIGHT_WHITE, RIGHT_BLACK);
  int error = leftLevel - rightLevel;
  record(error);

  int leftSpeed;
  int rightSpeed;
  if (MODE == 0) {
    // Релейный, как в уроке 3.1: колесо над линией стоит.
    leftSpeed = leftLevel < 50 ? 0 : baseSpeed;
    rightSpeed = rightLevel < 50 ? 0 : baseSpeed;
  } else {
    int correction = controller(MODE, error);
    leftSpeed = constrain(baseSpeed + correction, 0, 255);
    rightSpeed = constrain(baseSpeed - correction, 0, 255);
  }
  drive(FORWARD, leftSpeed, FORWARD, rightSpeed);
}
