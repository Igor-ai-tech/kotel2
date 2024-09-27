const int sensorPin = A1; // Пин, к которому подключен датчик
/*
R     t   a            b
9420	0 	-0,002336449	22,00934579
7280	5 	-0,00310559 	27,60869565
5670	10	-0,004098361	33,23770492
4450	15	-0,005376344	38,92473118
3520	20	-0,006896552	44,27586207
2795	25	-0,008976661	50,08976661
2238	30	-0,011415525	55,54794521
1800	35	-0,014619883	61,31578947
1458	40	-0,018115942	66,41304348
1182	45	-0,023809524	73,14285714
972	  50	-0,032894737	81,97368421
668  	60	-0,047619048	91,80952381
458 	70	-0,079365079	106,3492063
332 	80	-0,108695652	116,0869565
240 	90	-0,15625	    127,5
176 	100	 расчет не возможен, нет следующих диапазона
*/
const int RESISTANCE_DTOJ[] = {9420, 5670, 3520, 2238, 1458, 972, 668, 458, 332, 240, 176};

/* пересчет сопротивления в температуру для датчика ДТОЖ */
int r2t(int *r)
{
  *r += 1;
  Serial.print("R: ");
  Serial.print(*r);
  Serial.println(" Ohm");
  for (int i = 0; i < sizeof(RESISTANCE_DTOJ) / sizeof(int); ++i)
  {
    if (RESISTANCE_DTOJ[i] == r)
    {
      return i * 10;
    }
  }
  return 42;
}

void setup() {
  Serial.begin(9600); // Инициализация последовательной связи
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Считываем значение с датчика
//  float voltage = sensorValue * (5.0 / 1023.0); // Пересчитываем значение в напряжение (при предположении, что используется 5 вольт)
  Serial.print("Resistance0: ");
  Serial.print(sensorValue);
  Serial.println(" Ohm");
  int t = r2t(&sensorValue);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" C");
  Serial.print("Resistance: ");
  Serial.print(sensorValue);
  Serial.println(" Ohm");
  Serial.println("");
  delay(4000); // Задержка для устранения эффекта "дребезга"
}
