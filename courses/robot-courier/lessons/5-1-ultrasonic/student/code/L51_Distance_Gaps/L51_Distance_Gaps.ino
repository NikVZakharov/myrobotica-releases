// Шаблон среднего уровня. Напиши код в разделе «Твоя часть» по целям в комментариях.

// Контакты ультразвукового датчика: впиши номера из таблицы проводки своего робота.
const int TRIG_PIN = -1;
const int ECHO_PIN = -1;

// ===== Твоя часть: напиши сам =====

int readDistanceCm() {
  // Щёлкнуть датчиком и вернуть расстояние до груза в сантиметрах.
  // Если эхо не вернулось за 25 000 мкс, вернуть -1.
  return -1;
}

// ===== Готовое: настройка датчика и печать — не меняй =====

void setupSonar() {
  // Без контактов датчика программа дальше не пойдёт.
  if (TRIG_PIN < 0 || ECHO_PIN < 0) {
    while (true) {
    }
  }
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void setup() {
  Serial.begin(9600);
  setupSonar();
}

void loop() {
  int distance = readDistanceCm();
  if (distance < 0) {
    Serial.println("нет эха");
  } else {
    Serial.print(distance);
    Serial.println(" см");
  }
  delay(200);
}
