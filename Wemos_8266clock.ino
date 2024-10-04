const int sensorPin = A1; // Пин, к которому подключен датчик

// Обновленный массив сопротивлений и соответствующих температур
const int RESISTANCE_DTOJ[] = {
  100700, 52700, 28680, 21450, 16180, 12300, 9420, 7280, 5670, 5260, 4970, 4735, 4500, 4340, 
  4170, 3980, 3780, 3580, 3450, 3270, 3140, 3010, 2890, 2760, 2640, 2530, 2410, 2300, 2190, 
  2100, 2010, 1949, 1870, 1790, 1718, 1642, 1580, 1519, 1451, 1396, 1343, 1291, 1243, 1195, 
  1147, 1103, 1063, 1022, 982, 942, 902, 870, 839
};

const int TEMP_DTOJ[] = {
  -40, -30, -20, -15, -10, -4, 0, 5, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 
  24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 
  47, 48, 49, 50, 51, 52, 53, 54
};

// Функция для пересчета сопротивления в температуру
float r2t(int r) {
  // Пройти по массиву и найти соответствующий диапазон
  for (int i = 0; i < sizeof(RESISTANCE_DTOJ) / sizeof(RESISTANCE_DTOJ[0]) - 1; i++) {
    if (r >= RESISTANCE_DTOJ[i + 1] && r <= RESISTANCE_DTOJ[i]) {
      // Линейная интерполяция
      float t = TEMP_DTOJ[i] + 
                (TEMP_DTOJ[i + 1] - TEMP_DTOJ[i]) * 
                (float)(r - RESISTANCE_DTOJ[i]) / (RESISTANCE_DTOJ[i + 1] - RESISTANCE_DTOJ[i]);
      return t;
    }
  }
  
  return -1;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Чтение значения с аналогового пина
  int sensorValue = analogRead(sensorPin);
  
  int resistorNominal = 1000; // Номинал резистора делителя напряжения
  float voltage = sensorValue * (5.0 / 1023.0);
  float resistance = resistorNominal * (5.0 / voltage - 1.0);
  
  // Пересчет сопротивления в температуру
  float temperature = r2t(resistance);

  // Округление температуры до ближайшего целого числа
  int roundedTemperature = round(temperature);

  // Вывод результата
  if (temperature != -1) {
    Serial.print("Temperature: ");
    Serial.print(roundedTemperature);
    Serial.println(" C");
  } else {
    Serial.println("ошибка");
  }

  delay(1000); // Задержка между измерениями
}
