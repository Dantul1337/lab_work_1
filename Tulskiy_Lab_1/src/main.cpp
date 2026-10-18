#include "pipe.h"
#include "compressor_station.h"
#include "storage.h"
#include "input_utils.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace
{

    void printMenu()
    {
        std::cout << "\n===== МЕНЮ =====\n"
                  << "1. Добавить трубу\n"
                  << "2. Добавить КС\n"
                  << "3. Просмотр всех объектов\n"
                  << "4. Редактировать трубу (признак 'в ремонте')\n"
                  << "5. Редактировать КС (запуск/останов цеха)\n"
                  << "6. Сохранить в файл\n"
                  << "7. Загрузить из файла\n"
                  << "0. Выход\n"
                  << "Выберите пункт: ";
    }

    void handleAddPipe(Pipe &pipe, bool &pipeExists)
    {
        inputPipe(pipe); // было: pipe = inputPipe();
        pipeExists = true;
        std::cout << "Труба добавлена.\n";
    }

    void handleAddStation(CompressorStation &station, bool &stationExists)
    {
        station = inputCompressorStation();
        stationExists = true;
        std::cout << "КС добавлена.\n";
    }

    void handleViewAll(const Pipe &pipe, bool pipeExists,
                       const CompressorStation &station, bool stationExists)
    {
        if (!pipeExists && !stationExists)
        {
            std::cout << "Объектов пока нет. Сначала добавьте трубу и/или КС.\n";
            return;
        }
        if (pipeExists)
        {
            printPipe(pipe);
        }
        else
        {
            std::cout << "Труба ещё не добавлена.\n";
        }
        if (stationExists)
        {
            printCompressorStation(station);
        }
        else
        {
            std::cout << "КС ещё не добавлена.\n";
        }
    }

    void handleEditPipe(Pipe &pipe, bool pipeExists)
    {
        if (!pipeExists)
        {
            std::cout << "Труба ещё не добавлена. Сначала выберите пункт 1.\n";
            return;
        }
        editPipeRepairStatus(pipe);
    }

    void handleEditStation(CompressorStation &station, bool stationExists)
    {
        if (!stationExists)
        {
            std::cout << "КС ещё не добавлена. Сначала выберите пункт 2.\n";
            return;
        }
        std::cout << "1 - Запустить цех\n2 - Остановить цех\nВыберите действие: ";
        int action = readInt("", 1, 2);
        if (action == 1)
        {
            startShop(station);
        }
        else
        {
            stopShop(station);
        }
    }

    void handleSave(const Pipe &pipe, bool pipeExists,
                    const CompressorStation &station, bool stationExists)
    {
        if (!pipeExists && !stationExists)
        {
            std::cout << "Нечего сохранять: сначала добавьте трубу и/или КС "
                         "(пункты 1 и 2).\n";
            return;
        }
        std::string filename = readNonEmptyLine("Имя файла для сохранения: ");
        saveToFile(filename, pipeExists ? &pipe : nullptr,
                   stationExists ? &station : nullptr);
    }

    void handleLoad(Pipe &pipe, bool &pipeExists,
                    CompressorStation &station, bool &stationExists)
    {
        std::string filename = readNonEmptyLine("Имя файла для загрузки: ");
        loadFromFile(filename, pipe, pipeExists, station, stationExists);
    }

}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Pipe pipe;
    CompressorStation station;
    bool pipeExists = false;
    bool stationExists = false;

    std::cout << "=== Лабораторная: трубопроводный транспорт ===\n";

    while (true)
    {
        printMenu();
        int choice = readInt("", 0, 7);

        switch (choice)
        {
        case 1:
            handleAddPipe(pipe, pipeExists);
            break;
        case 2:
            handleAddStation(station, stationExists);
            break;
        case 3:
            handleViewAll(pipe, pipeExists, station, stationExists);
            break;
        case 4:
            handleEditPipe(pipe, pipeExists);
            break;
        case 5:
            handleEditStation(station, stationExists);
            break;
        case 6:
            handleSave(pipe, pipeExists, station, stationExists);
            break;
        case 7:
            handleLoad(pipe, pipeExists, station, stationExists);
            break;
        case 0:
            std::cout << "Выход из программы.\n";
            return 0;
        }
    }
}