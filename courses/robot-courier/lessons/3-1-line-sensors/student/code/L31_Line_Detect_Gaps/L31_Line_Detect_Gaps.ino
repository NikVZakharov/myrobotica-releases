// Шаблон среднего уровня. Напиши код в разделе «Твоя часть» по целям в комментариях.

const int LEFT_SENSOR_PIN = {{pins.leftSensor}};
const int RIGHT_SENSOR_PIN = {{pins.rightSensor}};

// Впиши свои измерения из бортового журнала.
const int LEFT_WHITE = 0;
const int LEFT_BLACK = 0;
const int RIGHT_WHITE = 0;
const int RIGHT_BLACK = 0;

// ===== Твоя часть: напиши сам =====

void loop() {
  int leftValue = analogRead(LEFT_SENSOR_PIN);
  int rightValue = analogRead(RIGHT_SENSOR_PIN);

  // Для каждого датчика реши, линия ли под ним (правило «ближе к чёрному»): leftOnLine и rightOnLine.
  // Печатай строку L=… R=…, а если под датчиком линия — допиши «слева линия» или «справа линия».
  // Пять строк в секунду.
}

// ===== Готовое из прошлого шага — не меняй =====

void setup() {
  Serial.begin(9600);
}
