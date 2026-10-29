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

// Напиши диагностику по требованиям урока. При включении моторы стоят.
void setup() {
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
}

void loop() {
}
