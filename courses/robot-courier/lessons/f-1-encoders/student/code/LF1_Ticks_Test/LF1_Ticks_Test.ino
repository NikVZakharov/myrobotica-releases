// Проверка функции ticksFor. Напиши функцию здесь, загрузи и открой монитор порта.
// Когда все строки PASS, перенеси ticksFor в свою программу.

// Требование 2: сколько импульсов нужно, чтобы проехать mm миллиметров (округлённо).
long ticksFor(int mm, int ticksPerRev, int diameterMm) {
  return 0;
}

int failed = 0;

void expect(int mm, int ticksPerRev, int diameterMm, long expected) {
  long actual = ticksFor(mm, ticksPerRev, diameterMm);
  Serial.print(actual == expected ? "PASS " : "FAIL ");
  Serial.print("ticksFor(");
  Serial.print(mm);
  Serial.print(", ");
  Serial.print(ticksPerRev);
  Serial.print(", ");
  Serial.print(diameterMm);
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

  expect(0, 20, 45, 0);
  expect(141, 20, 45, 20);   // почти ровно один оборот
  expect(500, 20, 45, 71);   // 70.7 округляется вверх
  expect(1000, 20, 65, 98);  // другое колесо
  expect(1000, 40, 45, 283);
  expect(2000, 40, 45, 566); // 2000 × 40 не помещается в int

  if (failed == 0) {
    Serial.println("Все проверки пройдены");
  } else {
    Serial.print("Ошибок: ");
    Serial.println(failed);
  }
}

void loop() {
}
