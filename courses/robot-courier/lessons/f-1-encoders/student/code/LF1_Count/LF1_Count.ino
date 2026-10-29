// Контакты энкодеров: впиши номера из таблицы проводки своего робота.
// На Arduino Uno счёт по прерыванию работает только на контактах 2 и 3.
const int LEFT_ENCODER_PIN = -1;
const int RIGHT_ENCODER_PIN = -1;

// Счётчики импульсов. volatile: их меняет прерывание.
volatile long leftTicks = 0;
volatile long rightTicks = 0;

// Arduino вызывает её сама на каждый импульс левого энкодера.
void countLeft() {
  leftTicks++;
}

// То же для правого энкодера.
void countRight() {
  rightTicks++;
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
  setupEncoders();
}

void loop() {
  // Читаем оба счётчика, пока прерывания выключены: число не изменится посередине чтения.
  noInterrupts();
  long left = leftTicks;
  long right = rightTicks;
  interrupts();

  Serial.print("Левое: ");
  Serial.print(left);
  Serial.print("  правое: ");
  Serial.println(right);
  delay(200);
}
