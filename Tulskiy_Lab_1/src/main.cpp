#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

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
    while (true)
    {
        if (std::getline(std::cin, line))
        {
            return line;
        }
        std::cout << "\nОшибка ввода! Пожалуйста, повторите попытку: ";
        std::cin.clear();
        // std::cin.ignore(10000, '\n'); 
    }
}

std::string readNonEmptyString(const std::string& prompt)
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

int readInt(const std::string& prompt, int min, int max)
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

double readDouble(const std::string& prompt, double min, double max)
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

bool readBool(const std::string& prompt)
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
    return pipe;
}

void printPipe(const Pipe& pipe)
{
    std::cout << "--- Труба ---\n"
        << "Название: " << pipe.name << "\n"
        << "Длина: " << pipe.length << " км\n"
        << "Диаметр: " << pipe.diameter << " мм\n"
        << "В ремонте: " << (pipe.underRepair ? "да" : "нет") << "\n";
}

void editPipe(Pipe& pipe)
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

void printStation(const CompressorStation& station)
{
    std::cout << "--- КС ---\n"
        << "Название: " << station.name << "\n"
        << "Цехов всего: " << station.totalShops << "\n"
        << "Цехов в работе: " << station.activeShops << "\n"
        << "Класс станции: " << station.stationClass << "\n";
}

void startShop(CompressorStation& station)
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

void stopShop(CompressorStation& station)
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

void editStation(CompressorStation& station)
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
        << "6. Сохранить\n"
        << "7. Загрузить\n"
        << "0. Выход\n";
}

void savePipe(std::ofstream& file, const Pipe& pipe)
{
    file << pipe.name << "\n"
        << pipe.length << " " << pipe.diameter << " " << pipe.underRepair << "\n";
}

void saveStation(std::ofstream& file, const CompressorStation& station)
{
    file << station.name << "\n"
        << station.totalShops << " " << station.activeShops << " "
        << station.stationClass << "\n";
}

bool saveToFile(const std::string& fileName, const Pipe& pipe, bool hasPipe, const CompressorStation& station, bool hasStation)
{
    std::ofstream file(fileName);
    if (!file)
    {
        return false;
    }
    if (hasPipe)
    {
        file << "PIPE\n";
        savePipe(file, pipe);
    }
    if (hasStation)
    {
        file << "STATION\n";
        saveStation(file, station);
    }
    return file.good();
}

bool loadPipe(std::ifstream& file, Pipe& pipe)
{
    std::string numbers;
    if (!std::getline(file, pipe.name) || pipe.name.empty() || !std::getline(file, numbers))
    {
        return false;
    }
    std::istringstream stream(numbers);
    int repair;
    if (!(stream >> pipe.length >> pipe.diameter >> repair))
    {
        return false;
    }
    pipe.underRepair = (repair == 1);
    return pipe.length > 0 && pipe.diameter > 0 && (repair == 0 || repair == 1);
}

bool loadStation(std::ifstream& file, CompressorStation& station)
{
    std::string numbers;
    if (!std::getline(file, station.name) || station.name.empty())
    {
        return false;
    }
    //std::istringstream stream(numbers);
    if (!(file >> station.totalShops >> station.activeShops >> station.stationClass))
    {
        return false;
    }
    return station.totalShops >= 1 && station.activeShops >= 0 && station.activeShops <= station.totalShops && station.stationClass >= 1 && station.stationClass <= 5;
}

bool loadFromFile(const std::string& fileName, Pipe& pipe, bool& hasPipe, CompressorStation& station, bool& hasStation)
{
    std::ifstream file(fileName);
    if (!file)
    {
        return false;
    }
    Pipe newPipe;
    CompressorStation newStation;
    bool newHasPipe = false;
    bool newHasStation = false;
    std::string header;
    while (std::getline(file, header))
    {
        if (header == "PIPE" && !newHasPipe)
        {
            if (!loadPipe(file, newPipe))
            {
                return false;
            }
            newHasPipe = true;
        }
        else if (header == "STATION" && !newHasStation)
        {
            if (!loadStation(file, newStation))
            {
                return false;
            }
            newHasStation = true;
        }
        else
        {
            return false;
        }
    }
    if (!newHasPipe && !newHasStation)
    {
        return false;
    }
    pipe = newPipe;
    hasPipe = newHasPipe;
    station = newStation;
    hasStation = newHasStation;
    return true;
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Pipe pipe;
    CompressorStation station;
    bool hasPipe = false;
    bool hasStation = false;
    const std::string fileName = "data.txt";

    while (true)
    {
        printMenu();
        int choice = readInt("Выберите пункт: ", 0, 7);
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
                std::cout << "Объектов нет\n";
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
        case 6:
            if (!hasPipe && !hasStation)
                std::cout << "Нечего сохранять.\n";
            else if (saveToFile(fileName, pipe, hasPipe, station, hasStation))
                std::cout << "Сохранено в " << fileName << "\n";
            else
                std::cout << "Ошибка записи в файл!\n";
            break;
        case 7:
            if (loadFromFile(fileName, pipe, hasPipe, station, hasStation))
                std::cout << "Загружено из " << fileName << "\n";
            else
                std::cout << "Не удалось загрузить: файл отсутствует или повреждён.\n";
            break;
        case 0:
            return 0;
        }
    }
    return 0;
}