
// Макросы #define не занимают памяти, так как просто заменяют значения в коде на этапе компиляции
#define CONTROLLER_VERSION '1.0'

#define ROZGIG_VENT_DELAY 10000        // Задержка включения перед розжигом
#define ROZGIG_TRANS_DELAY_PERED 3000  // Задержка перед включением трансформатора перед зажиганием
#define ROZGIG_TRANS_DELAY_POSLE 3000  // Задержка перед выключением трансформатора после зажигания
#define ROZGIG_TIME_FLAME_CONTROL 3000
#define OPERATIONAL_DELAY 30  // Операционная задержка для стабилизации после выполнения операций
#define DP_READ_COUNT 3
#define ROZGIG_ATTEMPT_COUNT 5

// Определение пинов
#define ROZGIG_TRANS_PIN 1  // Пин для управления трансформатором
#define KLAPAN_ZAPAL_PIN 2  // Пин для управления запальником
#define DP_PIN 3            // Пин датчика пламени

void setup() {

  Serial.begin(9600);
  Serial.println('Kotel start. Version:' + CONTROLLER_VERSION);
  pinMode(ROZGIG_TRANS_PIN, OUTPUT);    // Настраиваем пин розжиг-трансформатора как выходной.
  digitalWrite(ROZGIG_TRANS_PIN, LOW);  // Устанавливаем начальное состояние пина розжига в LOW
  pinMode(DP_PIN, INPUT);
}

void loop() {
}

// Функция розжига
void rozgig() {
  bool flag = false;
  for (byte i = 0; i < ROZGIG_ATTEMPT_COUNT; i++) {
    if (rozgig_attempt()) {
      flag = true;
      break;
    }
  }
  if (flag){
    //действия при успешном розжиге
  } else {
    //ействия при неудачном розжиге
}

}

bool rozgig_attempt() {

  delay(ROZGIG_VENT_DELAY);    // Ждём заданное время перед началом розжига, для вентиляции
  relay_on(ROZGIG_TRANS_PIN);  // Включаем трансформатор розжига

  delay(ROZGIG_TRANS_DELAY_PERED);  // Ждём задержку перед открытием клапана запальника
  relay_on(KLAPAN_ZAPAL_PIN);       // Открываем клапан запальника

  delay(ROZGIG_TRANS_DELAY_POSLE);  // Задержка после открытия клапана
  relay_off(ROZGIG_TRANS_PIN);      // Выключаем трансформатор розжига

  delay(OPERATIONAL_DELAY);  // Задержка для стабилизации

  unsigned long currentMillis = millis();
  while (millis() - currentMillis <= ROZGIG_TIME_FLAME_CONTROL) {
    byte dp_count = 0;
    for (byte i = 0; i < DP_READ_COUNT; i++) {
      if (digitalRead(DP_PIN) == 1) {
        dp_count++;
      }
      delay(OPERATIONAL_DELAY);
    }
    if (DP_READ_COUNT == dp_count) {
      return true;
    }
  }
  return false;
}

// Включение или отключение реле в зависимости от параметров
void relay_switch(bool mode, byte relay_pin) {
  if (mode) {
    digitalWrite(relay_pin, HIGH);  // Если mode true, включаем реле (HIGH)
  } else {
    digitalWrite(relay_pin, LOW);  // Если mode == false, выключаем реле (LOW)
  }
  // relay_status = mode;  // Здесь можно было бы обновить состояние реле, если это требуется для отслеживания
}

// Вспомогательные функции для упрощённого включения/выключения реле

// Функция relay_on() вызывает relay_switch() с параметром true, что включает реле
void relay_on(byte relay_pin) {
  relay_switch(true, relay_pin);
}

// Функция relay_off() вызывает relay_switch() с параметром false, что выключает реле
void relay_off(byte relay_pin) {
  relay_switch(false, relay_pin);
}