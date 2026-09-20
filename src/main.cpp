#include "pipe.h"
#include "compressor_station.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "Лабораторная: трубопроводный транспорт\n\n";

    Pipe pipe = inputPipe();
    std::cout << "\nВведённые данные трубы:\n";
    printPipe(pipe);

    editPipeRepairStatus(pipe);
    std::cout << "\nПосле редактирования:\n";
    printPipe(pipe);

    std::cout << "\n----------------------------------------\n\n";

    CompressorStation station = inputCompressorStation();
    std::cout << "\nВведённые данные КС:\n";
    printCompressorStation(station);

    startShop(station);
    printCompressorStation(station);

    stopShop(station);
    printCompressorStation(station);

    return 0;
}