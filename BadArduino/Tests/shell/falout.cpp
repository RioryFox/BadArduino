#include <iostream>
#include <windows.h>
#include <string>
#include <cstdio>

void sendToSerial(HANDLE hSerial, const std::string& data) {
    DWORD bytesWritten;
    WriteFile(hSerial, data.c_str(), data.size(), &bytesWritten, NULL);
}

std::string readFromSerial(HANDLE hSerial) {
    char buffer[256];
    DWORD bytesRead;
    ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
    buffer[bytesRead] = '\0'; // Null-terminate the string
    return std::string(buffer);
}

int main() {
    std::cout << "Запуск программы..." << std::endl;

    // Настройка последовательного порта
    HANDLE hSerial = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Ошибка открытия порта! Код ошибки: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Порт открыт успешно." << std::endl;

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600; // Задайте скорость передачи данных
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: " << GetLastError() << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    std::cout << "Done." << std::endl;

    while (true) {
        std::string command = readFromSerial(hSerial);
        if (!command.empty()) {
            // Выполнение команды
            char result[256];
            snprintf(result, sizeof(result), "Command: %s\n", command.c_str());
            sendToSerial(hSerial, result);

            // Выполнение системной команды
            FILE* pipe = popen(command.c_str(), "r");
            if (!pipe) {
                sendToSerial(hSerial, "Failed to run command\n");
                continue;
            }

            // Чтение результата
            while (fgets(result, sizeof(result), pipe) != NULL) {
                sendToSerial(hSerial, result);
            }
            pclose(pipe);
        }
    }

    CloseHandle(hSerial);
    return 0;
}
