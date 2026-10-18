#include "input_utils.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>

std::string readNonEmptyLine(const std::string& prompt){
    std::string line;
    while (true){
        std::cout << prompt;
        if(!std::getline(std::cin, line)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        const bool blank = std::all_of(line.begin(), line.end(),
                                       [](unsigned char c){ return std::isspace(c); });
        if(!blank){
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
        std::istringstream iss(line);
        char answer;
        char leftover;
        if((iss >> answer) && !(iss >> leftover)){
            if(answer == 'y' || answer == 'Y'){
                return true;
            }
            if(answer == 'n' || answer == 'N'){
                return false;
            }
        }
        std::cout << "Введите 'y' или 'n'.\n";
    }
}