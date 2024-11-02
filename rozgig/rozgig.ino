
// Макросы #define не занимают памяти, так как просто заменяют значения в коде на этапе компиляции
#define ROZGIG_VENT_DELAY 10000         // Задержка включения перед розжигом
#define ROZGIG_TRANS_DELAY_PERED 3000   // Задержка перед включением трансформатора перед зажиганием
#define ROZGIG_TRANS_DELAY_POSLE 3000   // Задержка перед выключением трансформатора после зажигания
#define OPERATIONAL_DELAY 30            // Операционная задержка для стабилизации после выполнения операций

// Определение пинов
#define ROZGIG_TRANS_PIN 1              // Пин для управления трансформатором
#define KLAPAN_ZAPAL_PIN 2              // Пин для управления запальником
#define DP_PIN 3                        // Пин датчика пламени

void setup() {
    
  pinMode(ROZGIG_TRANS_PIN, OUTPUT);      // Настраиваем пин розжиг-трансформатора как выходной.
  digitalWrite(ROZGIG_TRANS_PIN, LOW);    // Устанавливаем начальное состояние пина розжига в LOW
}

void loop() {

}

// Функция розжига
void rozgig() {
  delay(ROZGIG_VENT_DELAY);            // Ждём заданное время перед началом розжига, для вентиляции
  relay_on(ROZGIG_TRANS_PIN);          // Включаем трансформатор розжига
  
  delay(ROZGIG_TRANS_DELAY_PERED);     // Ждём задержку перед открытием клапана запальника
  relay_on(KLAPAN_ZAPAL_PIN);          // Открываем клапан запальника

  delay(ROZGIG_TRANS_DELAY_POSLE);     // Задержка после открытия клапана
  relay_off(ROZGIG_TRANS_PIN);         // Выключаем трансформатор розжига
  
  delay(OPERATIONAL_DELAY);            // Задержка для стабилизации
  
  /*
  unsigned long currentMillis = millis();
  while(millis() - currentMillis <= loopTime) {
    if(условие)
      действие
  }
  */
 
}

// Включение или отключение реле в зависимости от параметров
void relay_switch(bool mode, byte relay_pin) {   
  if (mode) {
    digitalWrite(relay_pin, HIGH);  // Если mode true, включаем реле (HIGH)
  } else {                      
    digitalWrite(relay_pin, LOW);   // Если mode == false, выключаем реле (LOW)
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