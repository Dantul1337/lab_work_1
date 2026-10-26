#include <string>
#include <iostream>

struct Pipe{
    std::string name;
    double length = 0.0;
    int diameter = 0;
    bool underRepair = false;
};

struct CompressorStation{
    std::string name;
    int totalShops = 0;
    int activeShops = 0;
    int stationClass = 1;
};

std::string readLine(){
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::string readNonEmptyString(const std::string& prompt){
    while (true)
    {
        std::cout << prompt;
        std::string line = readLine();
        if (!line.empty()){
            return line;
        }
        std::cout << "Строка не должна быть пустой!\n";
    }   
}

int readInt(const std::string& prompt, int min, int max){
    while (true)
    {
        std::cout << prompt;
        std::string line = readLine();
        try{
            size_t pos = 0;
            int value = std::stoi(line, &pos);
            if(pos == line.size() && value >= min && value <= max){
                return value;
            }
        }
        catch(...){}
        std::cout << "Неверный ввод! Введите целое число от " << min << " до " << max << "\n";
    }
}

double readDouble(const std::string& prompt, double min, double max){
    while (true){
        std::cout << prompt;
        std::string line = readLine();
        try{
            size_t pos = 0;
            double value = std::stod(line, &pos);
            if (pos == line.size() && value >= min && value <= max){
                return value;
            }
        }
        catch (...){}
        std::cout << "Неверный ввод! Введите число от " << min << " до " << max << "\n";
    }
}

bool readBool(const std::string& prompt){
    while (true)
    {
        std::cout << prompt << " (y/n): ";
        std::string line = readLine();
        if (line == "y" || line == "Y"){
            return true;
        }
        if (line == "n" || line == "N"){
            return false;
        }
        std::cout << "Неверный ввод! Введите y или n\n";
    }
}



int main(){
    return 0;
}