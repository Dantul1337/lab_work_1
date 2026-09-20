#include "compressor_station.h"
#include "input_utils.h"

#include <iostream>

CompressorStation inputCompressorStation()
{
    CompressorStation station;

    std::cout << "Ввод данных КС\n";
    station.name = readNonEmptyLine("Название станции: ");
    station.totalShops = readInt("Количество цехов (> 0): ", 1, 1000);
    station.shopsInOperation = readInt(
        "Количество цехов в работе (0.." + std::to_string(station.totalShops) + "): ",
        0, station.totalShops);
    station.stationClass = readInt("Класс станции (1..10): ", 1, 10);

    return station;
}

void printCompressorStation(const CompressorStation &station)
{
    std::cout << "КС [" << station.name << "]\n"
              << "  Всего цехов:    " << station.totalShops << "\n"
              << "  В работе:       " << station.shopsInOperation << "\n"
              << "  Класс станции:  " << station.stationClass << "\n";
}

void startShop(CompressorStation &station)
{
    if (station.shopsInOperation >= station.totalShops)
    {
        std::cout << "Нельзя запустить цех: все " << station.totalShops
                  << " цехов уже в работе.\n";
        return;
    }
    ++station.shopsInOperation;
    std::cout << "Цех запущен. Теперь в работе: " << station.shopsInOperation
              << " из " << station.totalShops << ".\n";
}

void stopShop(CompressorStation &station)
{
    if (station.shopsInOperation <= 0)
    {
        std::cout << "Нельзя остановить цех: все цехи уже остановлены.\n";
        return;
    }
    --station.shopsInOperation;
    std::cout << "Цех остановлен. Теперь в работе: " << station.shopsInOperation
              << " из " << station.totalShops << ".\n";
}