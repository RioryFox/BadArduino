#include <SPI.h>
#include <SD.h>

const int chipSelect = 4; // Пин CS для SD-карты (D2 соответствует GPIO 4)

void setup() {
  Serial.begin(115200);
  Serial.println("Инициализация SD-карты...");

  // Инициализация SPI
  SPI.begin();

  // Инициализация SD-карты
  if (!SD.begin(chipSelect)) {
    Serial.println("Не удалось инициализировать SD-карту!");
    return;
  }
  Serial.println("SD-карта инициализирована.");

  // Пример записи файла
  File dataFile = SD.open("test.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Hello, World!");
    dataFile.close();
    Serial.println("Данные записаны в файл.");
  } else {
    Serial.println("Не удалось открыть файл для записи.");
  }
}

void loop() {
  // Ваш код
}
