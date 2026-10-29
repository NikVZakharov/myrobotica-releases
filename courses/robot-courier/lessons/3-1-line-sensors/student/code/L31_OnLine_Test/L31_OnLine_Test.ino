// Проверка функции onLine. Напиши функцию здесь, загрузи и открой монитор порта.
// Когда все строки PASS, перенеси onLine в свою программу.

// Требование 1: true, если показание ближе к чёрному, чем к белому.
bool onLine(int value, int white, int black) {
  return false;
}

int failed = 0;

void expect(int value, int white, int black, bool expected) {
  bool actual = onLine(value, white, black);
  Serial.print(actual == expected ? "PASS " : "FAIL ");
  Serial.print("onLine(");
  Serial.print(value);
  Serial.print(", ");
  Serial.print(white);
  Serial.print(", ");
  Serial.print(black);
  Serial.print(") = ");
  Serial.print(actual ? "true" : "false");
  Serial.print(", ожидаем ");
  Serial.println(expected ? "true" : "false");
  if (actual != expected) {
    failed++;
  }
}

void setup() {
  Serial.begin(9600);

  // Датчик, у которого чёрное — большое число, а белое — маленькое.
  expect(780, 120, 780, true);
  expect(120, 120, 780, false);
  expect(600, 120, 780, true);
  expect(300, 120, 780, false);
  // За пределами измерений.
  expect(900, 120, 780, true);
  expect(50, 120, 780, false);
  // Датчик, у которого наоборот: белое — большое число, чёрное — маленькое.
  expect(300, 900, 120, true);
  expect(700, 900, 120, false);

  if (failed == 0) {
    Serial.println("Все проверки пройдены");
  } else {
    Serial.print("Ошибок: ");
    Serial.println(failed);
  }
}

void loop() {
}
