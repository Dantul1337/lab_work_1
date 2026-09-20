#include "storage.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace
{

    void writeLine(std::ofstream &out, const std::string &key, const std::string &value)
    {
        out << key << "=" << value << "\n";
    }

    std::string readLine(std::ifstream &in, const std::string &expectedKey)
    {
        std::string line;
        if (!std::getline(in, line))
        {
            throw std::runtime_error("Неожиданный конец файла (ожидалось: " + expectedKey + ")");
        }
        const size_t pos = line.find('=');
        if (pos == std::string::npos)
        {
            throw std::runtime_error("Некорректная строка в файле: " + line);
        }
        const std::string key = line.substr(0, pos);
        if (key != expectedKey)
        {
            throw std::runtime_error("Ожидался ключ '" + expectedKey + "', получен '" + key + "'");
        }
        return line.substr(pos + 1);
    }

    int parseInt(const std::string &text)
    {
        size_t consumed = 0;
        int value = std::stoi(text, &consumed);
        if (consumed != text.size())
        {
            throw std::runtime_error("Некорректное целое число: " + text);
        }
        return value;
    }

    double parseDouble(const std::string &text)
    {
        size_t consumed = 0;
        double value = std::stod(text, &consumed);
        if (consumed != text.size())
        {
            throw std::runtime_error("Некорректное вещественное число: " + text);
        }
        return value;
    }

    bool parseBool(const std::string &text)
    {
        if (text == "1")
            return true;
        if (text == "0")
            return false;
        throw std::runtime_error("Некорректное булево значение: " + text);
    }

}

bool saveToFile(const std::string &filename, const Pipe &pipe,
                const CompressorStation &station)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        std::cout << "Не удалось открыть файл '" << filename << "' для записи.\n";
        return false;
    }

    out << "[PIPE]\n";
    writeLine(out, "mark", pipe.mark);
    writeLine(out, "lengthKm", std::to_string(pipe.lengthKm));
    writeLine(out, "diameterMm", std::to_string(pipe.diameterMm));
    writeLine(out, "underRepair", pipe.underRepair ? "1" : "0");

    out << "[STATION]\n";
    writeLine(out, "name", station.name);
    writeLine(out, "totalShops", std::to_string(station.totalShops));
    writeLine(out, "shopsInOperation", std::to_string(station.shopsInOperation));
    writeLine(out, "stationClass", std::to_string(station.stationClass));

    if (!out.good())
    {
        std::cout << "Ошибка при записи в файл '" << filename << "'.\n";
        return false;
    }

    std::cout << "Данные успешно сохранены в файл '" << filename << "'.\n";
    return true;
}

bool loadFromFile(const std::string &filename, Pipe &pipe,
                  CompressorStation &station)
{
    std::ifstream in(filename);
    if (!in.is_open())
    {
        std::cout << "Не удалось открыть файл '" << filename << "' для чтения.\n";
        return false;
    }

    try
    {
        std::string header;

        if (!std::getline(in, header) || header != "[PIPE]")
        {
            throw std::runtime_error("Отсутствует или повреждён заголовок [PIPE]");
        }
        Pipe loadedPipe;
        loadedPipe.mark = readLine(in, "mark");
        loadedPipe.lengthKm = parseDouble(readLine(in, "lengthKm"));
        loadedPipe.diameterMm = parseInt(readLine(in, "diameterMm"));
        loadedPipe.underRepair = parseBool(readLine(in, "underRepair"));

        if (!std::getline(in, header) || header != "[STATION]")
        {
            throw std::runtime_error("Отсутствует или повреждён заголовок [STATION]");
        }
        CompressorStation loadedStation;
        loadedStation.name = readLine(in, "name");
        loadedStation.totalShops = parseInt(readLine(in, "totalShops"));
        loadedStation.shopsInOperation = parseInt(readLine(in, "shopsInOperation"));
        loadedStation.stationClass = parseInt(readLine(in, "stationClass"));

        pipe = loadedPipe;
        station = loadedStation;
    }
    catch (const std::exception &ex)
    {
        std::cout << "Ошибка при загрузке файла '" << filename << "': " << ex.what() << "\n";
        return false;
    }

    std::cout << "Данные успешно загружены из файла '" << filename << "'.\n";
    return true;
}