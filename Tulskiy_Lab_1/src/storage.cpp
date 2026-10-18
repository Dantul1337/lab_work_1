#include "storage.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <stdexcept>

namespace
{
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

        void checkPipe(const Pipe &p)
    {
        if (p.mark.empty())
            throw std::runtime_error("Пустая километровая отметка");
        if (!(p.lengthKm >= 0.001 && p.lengthKm <= 100000.0))
            throw std::runtime_error("Длина трубы должна быть от 0.001 до 100000");
        if (p.diameterMm < 1 || p.diameterMm > 100000)
            throw std::runtime_error("Диаметр трубы должен быть от 1 до 100000");
    }

    void checkStation(const CompressorStation &s)
    {
        if (s.name.empty())
            throw std::runtime_error("Пустое название КС");
        if (s.totalShops < 1 || s.totalShops > 1000)
            throw std::runtime_error("Количество цехов должно быть от 1 до 1000");
        if (s.shopsInOperation < 0 || s.shopsInOperation > s.totalShops)
            throw std::runtime_error("Цехов в работе должно быть от 0 до количества цехов");
        if (s.stationClass < 1 || s.stationClass > 10)
            throw std::runtime_error("Класс станции должен быть от 1 до 10");
    }
}

bool saveToFile(const std::string &filename, const Pipe *pipe,
                const CompressorStation *station)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        std::cout << "Не удалось открыть файл '" << filename << "' для записи.\n";
        return false;
    }

    if (pipe)
    {
        out << "[PIPE]\n";
        out << "mark=" << pipe->mark << "\n";
        out << "lengthKm=" << std::to_string(pipe->lengthKm) << "\n";
        out << "diameterMm=" << std::to_string(pipe->diameterMm) << "\n";
        out << "underRepair=" << (pipe->underRepair ? "1" : "0") << "\n";
    }

    if (station)
    {
        out << "[STATION]\n";
        out << "name=" << station->name << "\n";
        out << "totalShops=" << std::to_string(station->totalShops) << "\n";
        out << "shopsInOperation=" << std::to_string(station->shopsInOperation) << "\n";
        out << "stationClass=" << std::to_string(station->stationClass) << "\n";
    }

    if (!out.good())
    {
        std::cout << "Ошибка при записи в файл '" << filename << "'.\n";
        return false;
    }

    std::cout << "Данные успешно сохранены в файл '" << filename << "'.\n";
    return true;
}

bool loadFromFile(const std::string &filename, Pipe &pipe, bool &hasPipe,
                  CompressorStation &station, bool &hasStation)
{
    std::ifstream in(filename);
    if (!in.is_open())
    {
        std::cout << "Не удалось открыть файл '" << filename << "' для чтения.\n";
        return false;
    }

    try
    {
        Pipe loadedPipe;
        CompressorStation loadedStation;
        bool pipeInFile = false;
        bool stationInFile = false;

        std::string header;
        if (!std::getline(in, header))
        {
            throw std::runtime_error("Файл пуст");
        }

        if (header == "[PIPE]")
        {
            loadedPipe.mark = readLine(in, "mark");
            loadedPipe.lengthKm = parseDouble(readLine(in, "lengthKm"));
            loadedPipe.diameterMm = parseInt(readLine(in, "diameterMm"));
            loadedPipe.underRepair = parseBool(readLine(in, "underRepair"));
            checkPipe(loadedPipe);
            pipeInFile = true;

            if (!std::getline(in, header))
            {
                header.clear(); // файл закончился: КС в нём нет
            }
        }

        if (header == "[STATION]")
        {
            loadedStation.name = readLine(in, "name");
            loadedStation.totalShops = parseInt(readLine(in, "totalShops"));
            loadedStation.shopsInOperation = parseInt(readLine(in, "shopsInOperation"));
            loadedStation.stationClass = parseInt(readLine(in, "stationClass"));
            checkStation(loadedStation);
            stationInFile = true;
        }
        else if (!pipeInFile || !header.empty())
        {
            throw std::runtime_error("Ожидался заголовок [PIPE] или [STATION], получено: '" + header + "'");
        }

        // загрузка заменяет текущее состояние целиком: чего нет в файле, того нет и в памяти
        if (pipeInFile)
        {
            pipe = std::move(loadedPipe);
        }
        if (stationInFile)
        {
            station = std::move(loadedStation);
        }
        hasPipe = pipeInFile;
        hasStation = stationInFile;
    }
    catch (const std::exception &ex)
    {
        std::cout << "Ошибка при загрузке файла '" << filename << "': " << ex.what() << "\n";
        return false;
    }

    std::cout << "Данные успешно загружены из файла '" << filename << "'.\n";
    return true;
}