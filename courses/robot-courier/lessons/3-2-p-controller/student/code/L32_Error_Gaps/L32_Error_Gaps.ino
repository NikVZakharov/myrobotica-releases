// Шаблон среднего уровня. Напиши код в разделе «Твоя часть» по целям в комментариях.

const int LEFT_SENSOR_PIN = {{pins.leftSensor}};
const int RIGHT_SENSOR_PIN = {{pins.rightSensor}};

// Измерения белого и чёрного из журнала (урок 3.1).
const int LEFT_WHITE = 0;
const int LEFT_BLACK = 0;
const int RIGHT_WHITE = 0;
const int RIGHT_BLACK = 0;

// ===== Твоя часть: напиши сам =====

int level(int value, int white, int black) {
  // Шкала: чёрное — 0, белое — 100, между ними — по прямой.
  // Работает и когда у датчика чёрное — большое число, и когда маленькое; не выходит за 0…100.
  return 0;
}

void loop() {
  int leftLevel = level(analogRead(LEFT_SENSOR_PIN), LEFT_WHITE, LEFT_BLACK);
  int rightLevel = level(analogRead(RIGHT_SENSOR_PIN), RIGHT_WHITE, RIGHT_BLACK);

  // Ошибка: насколько и в какую сторону линия ушла от середины; линия посередине — 0.
  int error = 0;

  Serial.print("L=");
  Serial.print(leftLevel);
  Serial.print("  R=");
  Serial.print(rightLevel);
  Serial.print("  ошибка=");
  Serial.println(error);
  delay(200);
}

// ===== Готовое: настройка и защита — не меняй =====

void setup() {
  Serial.begin(9600);
  if (LEFT_WHITE == LEFT_BLACK || RIGHT_WHITE == RIGHT_BLACK) {
    Serial.println("Впиши измерения белого и чёрного");
    while (true) {
    }
  }
}
