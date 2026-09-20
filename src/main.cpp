#include "pipe.h"
#include "compressor_station.h"
#include "storage.h"
#include "input_utils.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "=== Лабораторная: трубопроводный транспорт (сборка №3) ===\n\n";

    Pipe pipe = inputPipe();
    CompressorStation station = inputCompressorStation();

    std::cout << "\n--- Введённые данные ---\n";
    printPipe(pipe);
    printCompressorStation(station);

    std::string filename = readNonEmptyLine("\nИмя файла для сохранения: ");
    saveToFile(filename, pipe, station);

    Pipe emptyPipe;
    CompressorStation emptyStation;

    std::cout << "\n--- Загружаем обратно из файла ---\n";
    if (loadFromFile(filename, emptyPipe, emptyStation)) {
        printPipe(emptyPipe);
        printCompressorStation(emptyStation);
    }

    return 0;
}