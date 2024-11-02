#define RELAY_PIN 13  // Определяем пин для реле как 13. Этот макрос будет заменен на число 13 в коде.

void setup() {
  pinMode(RELAY_PIN, OUTPUT);  // Настраиваем пин реле как выходной.
  digitalWrite(RELAY_PIN, LOW);  // Изначально реле выключено (LOW).
}

void loop() {
  // Основной цикл программы, который выполняется бесконечно.
  relay_on(RELAY_PIN);  // Включаем реле с помощью функции relay_on.
  delay(1000);  // Ждем 1 секунду.
  
  relay_off(RELAY_PIN);  // Выключаем реле с помощью функции relay_off.
  delay(1000);  // Ждем 1 секунду.
}

/*
 Функция для переключения состояния реле на указанном пине.
*/
void relay_switch(bool mode, byte relay_pin) {
  if (mode) {
    digitalWrite(relay_pin, HIGH);  // Если mode = true, включаем реле (HIGH).
  } else {                      
    digitalWrite(relay_pin, LOW);   // Если mode = false, выключаем реле (LOW).
  }
}

// Функция relay_on() включает реле на указанном пине.
void relay_on(byte relay_pin) { 
  relay_switch(true, relay_pin);  // Включаем реле через вызов relay_switch с mode = true.
}

// Функция relay_off() выключает реле на указанном пине.
void relay_off(byte relay_pin) { 
  relay_switch(false, relay_pin);  // Выключаем реле через вызов relay_switch с mode = false.
}
