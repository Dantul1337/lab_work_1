#include "input_utils.h"

#include <iostream>
#include <limits>
#include <sstream>

void clearInputStream(){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

namespace{
    std::string trim(const std::string& text){
        const std::string whitespace = " \t\r\n";
        const size_t start = text.find_first_not_of(whitespace);
        if(start == std::string::npos){
            return "";
        }
        const size_t end = text.find_last_not_of(whitespace);
        return text.substr(start, end - start + 1);
    }
}

std::string readNonEmptyLine(const std::string& prompt){
    std::string line;
    while (true){
        std::cout << prompt;
        if(!std::getline(std::cin, line)){
            clearInputStream();
            continue;
        }
        line = trim(line);
        if(!line.empty()){
            return line;
        }
        std::cout << "Значение не может быть пустым. Попробуйте ещё раз.\n";
    }
}

int readInt(const std::string& prompt, int minValue, int maxValue){
    while (true){
        std::string line = readNonEmptyLine(prompt);
        std::istringstream iss(line);
        int value;
        char leftover;
        if ((iss >> value) && !(iss >> leftover)) {
            if (value >= minValue && value <= maxValue){
                return value;
            }
            std::cout << "Значение должно быть в диапазоне [" << minValue << ", " << maxValue << "].\n";
        } else {
            std::cout << "Некорректный ввод: ожидалось целое число.\n";
        }
    }
}

double readDouble(const std::string& prompt, double minValue, double maxValue){
    while(true){
        std::string line = readNonEmptyLine(prompt);
        std::istringstream iss(line);
        double value;
        char leftover;
        if((iss >> value) && !(iss >> leftover)){
            if(value >= minValue && value <= maxValue){
                return value;
            }
            std::cout << "Значение должно быть в диапазоне [" << minValue << ", " << maxValue << "].\n";
        } else{
            std::cout << "Некорректный ввод: ожидалось число.\n";
        }
    }
}

bool readYesNo(const std::string& prompt){
    while(true){
        std::string line = readNonEmptyLine(prompt + " (y/n): ");
        if(line == "y" || line == "Y"){
            return true;
        }
        if (line == "n" || line == "N"){
            return false;
        }
        std::cout << "Введите 'y' или 'n'.\n";
    }
}