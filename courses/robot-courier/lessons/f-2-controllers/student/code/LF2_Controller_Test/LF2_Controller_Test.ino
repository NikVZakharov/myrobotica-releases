// Проверка функции controller. Напиши функцию здесь, загрузи и открой монитор порта.
// Когда все строки PASS, перенеси controller в свою программу.
// Коэффициенты в тесте свои, удобные для счёта; на дорожке будут твои.

float kp = 0.5;
float kd = 2.0;
float ki = 0.25;
const long SUM_LIMIT = 200;

int lastError = 0;
long errorSum = 0;

// Требование 2: режим 1 — П, 2 — ПД, 3 — ПИД.
int controller(int mode, int error) {
  return 0;
}

int failed = 0;

void reset() {
  lastError = 0;
  errorSum = 0;
}

void expect(const char *name, int actual, int expected) {
  Serial.print(actual == expected ? "PASS " : "FAIL ");
  Serial.print(name);
  Serial.print(": получили ");
  Serial.print(actual);
  Serial.print(", ожидаем ");
  Serial.println(expected);
  if (actual != expected) {
    failed++;
  }
}

void setup() {
  Serial.begin(9600);

  reset();
  expect("П, ошибка 40", controller(1, 40), 20);
  expect("П, ошибка -40", controller(1, -40), -20);

  reset();
  expect("ПД, первый шаг 10", controller(2, 10), 25);
  expect("ПД, ошибка выросла до 20", controller(2, 20), 30);
  expect("ПД, ошибка осталась 20", controller(2, 20), 10);

  reset();
  expect("ПИД, первый шаг 10", controller(3, 10), 27);
  expect("ПИД, снова 10", controller(3, 10), 10);

  // Накопленная ошибка не выходит за SUM_LIMIT.
  reset();
  int last = 0;
  for (int i = 0; i < 5; i++) {
    last = controller(3, 100);
  }
  expect("ПИД, пять шагов по 100", last, 100);
  reset();
  for (int i = 0; i < 5; i++) {
    last = controller(3, -100);
  }
  expect("ПИД, пять шагов по -100", last, -100);

  // В режиме П ошибка не копится, но прошлая ошибка запоминается.
  reset();
  controller(1, 100);
  controller(1, 100);
  controller(1, 100);
  expect("ПИД после трёх шагов П", controller(3, 100), 75);

  if (failed == 0) {
    Serial.println("Все проверки пройдены");
  } else {
    Serial.print("Ошибок: ");
    Serial.println(failed);
  }
}

void loop() {
}
