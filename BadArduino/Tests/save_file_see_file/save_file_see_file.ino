#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SD.h>

#define SCREEN_WIDTH 128 // Ширина дисплея
#define SCREEN_HEIGHT 64  // Высота дисплея

// Создайте объект дисплея
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // -1 для использования стандартного I2C

// Пины для SD-карты
const int chipSelect = D3; // CS SD-карты

void setup() {
  Serial.begin(115200);

  // Инициализация дисплея
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Настройка текста на дисплее
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  // Инициализация SD-карты
  if (!SD.begin(chipSelect)) {
    display.println("SD Card Error!");
    display.display();
    while (true); // Остановить выполнение, если ошибка
  } else {
    display.println("SD Card OK!");
    display.display();
    delay(2000);
    display.clearDisplay();

    // Создание и запись файла
    createAndWriteFile("/test.txt", "Hello, SD Card!");

    // Считывание и отображение содержимого директории
    listDirectory(SD.open("/"), 0);
  }
}

void loop() {
  // Ваш код
}
void createAndWriteFile(const char* path, const char* message) {
  File file = SD.open(path, FILE_WRITE);
  if (file) {
    file.println(message);
    file.close();
    display.println("File created:");
    display.println(path);
    display.display();
    delay(2000);
    display.clearDisplay();
  } else {
    display.println("File creation failed!");
    display.display();
    delay(2000);
    display.clearDisplay();
  }
}

void listDirectory(File dir, int numTabs) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      break; // Если больше нет файлов, выходим из цикла
    }

    // Отображаем имя файла
    for (int i = 0; i < numTabs; i++) {
      display.print("\t"); // Добавляем табуляцию
    }
    display.print(entry.name());

    if (entry.isDirectory()) {
      display.println("/"); // Если это директория, добавляем слэш
      listDirectory(entry, numTabs + 1); // Рекурсивно вызываем для поддиректорий
    } else {
      display.print("  "); // Пробел для разделения
      display.print(entry.size()); // Отображаем размер файла
      display.println(" bytes");
    }
    entry.close(); // Закрываем файл
  }
  dir.close(); // Закрываем директорию
}
