// Проверка функции level. Напиши функцию здесь, загрузи и открой монитор порта.
// Когда все строки PASS, перенеси level в свою программу.

// Требование 1: шкала «чёрное — 0, белое — 100».
int level(int value, int white, int black) {
  return 0;
}

int failed = 0;

void expect(int value, int white, int black, int expected) {
  int actual = level(value, white, black);
  Serial.print(actual == expected ? "PASS " : "FAIL ");
  Serial.print("level(");
  Serial.print(value);
  Serial.print(", ");
  Serial.print(white);
  Serial.print(", ");
  Serial.print(black);
  Serial.print(") = ");
  Serial.print(actual);
  Serial.print(", ожидаем ");
  Serial.println(expected);
  if (actual != expected) {
    failed++;
  }
}

void setup() {
  Serial.begin(9600);

  // Датчик, у которого чёрное — большое число, а белое — маленькое.
  expect(780, 120, 780, 0);
  expect(120, 120, 780, 100);
  expect(450, 120, 780, 50);
  // За пределами шкалы.
  expect(900, 120, 780, 0);
  expect(50, 120, 780, 100);
  // Датчик, у которого наоборот: белое — большое число, чёрное — маленькое.
  expect(120, 900, 120, 0);
  expect(510, 900, 120, 50);
  expect(900, 900, 120, 100);

  if (failed == 0) {
    Serial.println("Все проверки пройдены");
  } else {
    Serial.print("Ошибок: ");
    Serial.println(failed);
  }
}

void loop() {
}
