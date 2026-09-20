#include "pipe.h"

#include <iostream>

int main()
{
    std::cout << "Лабораторная: трубопроводный транспорт\n";

    Pipe pipe = inputPipe();
    std::cout << "\nВведённые данные:\n";
    printPipe(pipe);

    editPipeRepairStatus(pipe);
    std::cout << "\nПосле редактирования:\n";
    printPipe(pipe);

    return 0;
}