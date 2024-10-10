#define relay 13  // Определяем пин для реле как 13. Этот макрос будет заменен на число 13 в коде.
// const int relay = 13; // Альтернативный вариант определения пина через переменную, но он закомментирован.

bool relay_status = false;  // Переменная для хранения текущего состояния реле (включено или выключено).

void setup() {
  pinMode(relay, OUTPUT);  // Настраиваем пин реле как выходной.
  digitalWrite(relay, LOW);  // Изначально реле выключено (LOW).
}

void loop() {
  // Основной цикл программы, который выполняется бесконечно.
  relay_on();  // Включаем реле с помощью функции relay_on.
  delay(1000);  // Ждем 1 секунду.
  
  relay_switch(false);  // Выключаем реле с помощью функции relay_switch, передавая ей параметр false.
  delay(1000);  // Ждем 1 секунду.
}

void relay_switch(bool mode) {
  // Функция для переключения реле.
  if (mode) {
    digitalWrite(relay, HIGH);  // Если mode == true, включаем реле (HIGH).
  } else {                      
    digitalWrite(relay, LOW);  // Если mode == false, выключаем реле (LOW).
  }
  relay_status = mode;  // Обновляем переменную relay_status в соответствии с текущим состоянием реле.
}

void relay_on() {
 
  relay_switch(true);  // Включаем реле через вызов функции relay_switch с параметром true.
}