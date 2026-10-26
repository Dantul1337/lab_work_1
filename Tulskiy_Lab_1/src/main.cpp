#include <string>
#include <iostream>

struct Pipe
{
    std::string name;
    double length = 0.0;
    int diameter = 0;
    bool underRepair = false;
};

struct CompressorStation
{
    std::string name;
    int totalShops = 0;
    int activeShops = 0;
    int stationClass = 1;
};

std::string readLine()
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::string readNonEmptyString(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt;
        std::string line = readLine();
        if (!line.empty())
        {
            return line;
        }
        std::cout << "Строка не должна быть пустой!\n";
    }
}

int readInt(const std::string &prompt, int min, int max)
{
    while (true)
    {
        std::cout << prompt;
        std::string line = readLine();
        try
        {
            size_t pos = 0;
            int value = std::stoi(line, &pos);
            if (pos == line.size() && value >= min && value <= max)
            {
                return value;
            }
        }
        catch (...)
        {
        }
        std::cout << "Неверный ввод! Введите целое число от " << min << " до " << max << "\n";
    }
}

double readDouble(const std::string &prompt, double min, double max)
{
    while (true)
    {
        std::cout << prompt;
        std::string line = readLine();
        try
        {
            size_t pos = 0;
            double value = std::stod(line, &pos);
            if (pos == line.size() && value >= min && value <= max)
            {
                return value;
            }
        }
        catch (...)
        {
        }
        std::cout << "Неверный ввод! Введите число от " << min << " до " << max << "\n";
    }
}

bool readBool(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt << " (y/n): ";
        std::string line = readLine();
        if (line == "y" || line == "Y")
        {
            return true;
        }
        if (line == "n" || line == "N")
        {
            return false;
        }
        std::cout << "Неверный ввод! Введите y или n\n";
    }
}

Pipe readPipe()
{
    Pipe pipe;
    pipe.name = readNonEmptyString("Название участка: ");
    pipe.length = readDouble("Длина (км): ", 0.001, 10000);
    pipe.diameter = readInt("Диаметр (мм): ", 1, 3000);
    pipe.underRepair = readBool("Труба в ремонте?");
}

void printPipe(const Pipe &pipe)
{
    std::cout << "--- Труба ---\n"
              << "Название: " << pipe.name << "\n"
              << "Длина: " << pipe.length << " км\n"
              << "Диаметр: " << pipe.diameter << " мм\n"
              << "В ремонте: " << (pipe.underRepair ? "да" : "нет") << "\n";
}

void editPipe(Pipe &pipe)
{
    pipe.underRepair = readBool("Труба в ремонте?");
    std::cout << "Признак изменён.\n";
}

CompressorStation readStation()
{
    CompressorStation station;
    station.name = readNonEmptyString("Название КС: ");
    station.totalShops = readInt("Количество цехов: ", 1, 1000);
    station.activeShops = readInt("Количество цехов в работе: ", 0, station.totalShops);
    station.stationClass = readInt("Класс станции (1-5): ", 1, 5);
    return station;
}

void printStation(const CompressorStation &station)
{
    std::cout << "--- КС ---\n"
              << "Название: " << station.name << "\n"
              << "Цехов всего: " << station.totalShops << "\n"
              << "Цехов в работе: " << station.activeShops << "\n"
              << "Класс станции: " << station.stationClass << "\n";
}

void startShop(CompressorStation &station)
{
    if (station.activeShops >= station.totalShops)
    {
        std::cout << "Все цеха уже работают!\n";
    }
    else
    {
        ++station.activeShops;
        std::cout << "Цех запущен.\n";
    }
}

void stopShop(CompressorStation &station)
{
    if (station.activeShops <= 0)
    {
        std::cout << "Все цеха уже остановлены!\n";
    }
    else
    {
        --station.activeShops;
        std::cout << "Цех остановлен.\n";
    }
}

void editStation(CompressorStation &station)
{
    int choice = readInt("1 - запустить цех, 2 - остановить цех: ", 1, 2);
    if (choice == 1)
    {
        startShop(station);
    }
    else
    {
        stopShop(station);
    }
}

void printMenu()
{
    std::cout << "\n===== МЕНЮ =====\n"
              << "1. Добавить трубу\n"
              << "2. Добавить КС\n"
              << "3. Просмотр всех объектов\n"
              << "4. Редактировать трубу\n"
              << "5. Редактировать КС\n"
              << "0. Выход\n";
}

int main()
{
    Pipe pipe;
    CompressorStation station;
    bool hasPipe = false;
    bool hasStation = false;

    while (true)
    {
        printMenu();
        int choice = readInt("Выберите пункт: ", 0, 5);
        switch (choice)
        {
        case 1:
            pipe = readPipe();
            hasPipe = true;
            break;
        case 2:
            station = readStation();
            hasStation = true;
            break;
        case 3:
            if (!hasPipe && !hasStation)
            {
                std::cout << "Объектов нет";
            }
            if (hasPipe)
            {
                printPipe(pipe);
            }
            if (hasStation)
            {
                printStation(station);
            }
            break;
        case 4:
            if (hasPipe)
            {
                editPipe(pipe);
            }
            else
            {
                std::cout << "Труба не создана!\n";
            }
            break;
        case 5:
            if (hasStation)
                editStation(station);
            else
                std::cout << "КС не создана!\n";
            break;
        case 0:
            return 0;
        }
    }
    return 0;
}