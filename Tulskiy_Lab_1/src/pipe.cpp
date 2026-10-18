#include "pipe.h"
#include "input_utils.h"

#include <iostream>

void inputPipe(Pipe &pipe)
{
    std::cout << "--- Ввод данных трубы --- \n";
    pipe.mark = readNonEmptyLine("Километровая отметка (название участка): ");
    pipe.lengthKm = readDouble("Длина трубы, км (> 0): ", 0.001, 100000.0);
    pipe.diameterMm = readInt("Диаметр трубы, мм (> 0): ", 1, 100000);
    pipe.underRepair = readYesNo("Труба в ремонте?");
}

void inputPipe(Pipe &pipe)
{
    std::cout << "--- Ввод данных трубы --- \n";
    pipe.mark = readNonEmptyLine("Километровая отметка (название участка): ");
    pipe.lengthKm = readDouble("Длина трубы, км (> 0): ", 0.001, 100000.0);
    pipe.diameterMm = readInt("Диаметр трубы, мм (> 0): ", 1, 100000);
    pipe.underRepair = readYesNo("Труба в ремонте?");
}

void editPipeRepairStatus(Pipe &pipe)
{
    std::cout << "Текущий статус ремонта трубы [" << pipe.mark << "]: "
              << (pipe.underRepair ? "в ремонте" : "не в ремонте") << "\n";
    pipe.underRepair = readYesNo("Установить признак 'в ремонте'?");
    std::cout << "Статус обновлён.\n";
}