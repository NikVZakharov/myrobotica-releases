// Программа проверки для робота курса (Arduino Uno + шилд L298P).
// Робот стоит на подставке: колёса висят в воздухе.
// Колесо крутится со скоростью 120 из 255 около 0,3 секунды.
const int LEFT_DIR = {{pins.leftDir}};
const int LEFT_PWM = {{pins.leftPwm}};
const int RIGHT_DIR = {{pins.rightDir}};
const int RIGHT_PWM = {{pins.rightPwm}};
const int LEFT_SENSOR = {{pins.leftSensor}};
const int RIGHT_SENSOR = {{pins.rightSensor}};
const int FORWARD = {{values.forwardLevel}};
const int BACKWARD = LOW;
const int TEST_PWM = 120;
const unsigned long PULSE_MS = 300;
bool running = false;
unsigned long startedAt = 0;

void reportSensors() {
  Serial.print("LEFT=");
  Serial.print(analogRead(LEFT_SENSOR));
  Serial.print(" RIGHT=");
  Serial.println(analogRead(RIGHT_SENSOR));
}

void beginPulse(int dirPin, int pwmPin, int direction) {
  digitalWrite(dirPin, direction);
  analogWrite(pwmPin, TEST_PWM);
}

// ===== Готовая оболочка — не меняй =====
void stopMotors() {
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
  running = false;
}

void setup() {
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  stopMotors();
  pinMode(LEFT_DIR, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
  Serial.begin(9600);
  Serial.println("READY: 1=L forward, 2=L backward, 3=R forward, 4=R backward, d=sensors, s=stop");
}

void loop() {
  if (running && millis() - startedAt >= PULSE_MS) {
    stopMotors();
    Serial.println("PWM=0; verify physical stop");
  }
  if (!Serial.available()) return;
  char command = Serial.read();
  if (command == 's') {
    stopMotors();
    Serial.println("PWM=0; verify physical stop");
    return;
  }
  // Пока идёт импульс, новые команды не продлевают и не перезапускают его.
  if (running) return;
  if (command == 'd') {
    reportSensors();
    return;
  }
  if (command < '1' || command > '4') return;
  // Удаляем накопленные команды: один ввод не должен запускать очередь движений.
  while (Serial.available()) Serial.read();
  stopMotors();
  startedAt = millis();
  running = true;
  if (command == '1') beginPulse(LEFT_DIR, LEFT_PWM, FORWARD);
  if (command == '2') beginPulse(LEFT_DIR, LEFT_PWM, BACKWARD);
  if (command == '3') beginPulse(RIGHT_DIR, RIGHT_PWM, FORWARD);
  if (command == '4') beginPulse(RIGHT_DIR, RIGHT_PWM, BACKWARD);
  Serial.println("Observe wheel; no automatic hardware PASS");
}
