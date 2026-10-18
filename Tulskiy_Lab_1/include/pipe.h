#ifndef PIPE_H
#define PIPE_H

#include <string>

struct Pipe
{
    std::string mark;
    double lengthKm = 0.0;
    int diameterMm = 0;
    bool underRepair = false;
};

void inputPipe(Pipe& pipe);

void printPipe(const Pipe& pipe);

void editPipeRepairStatus(Pipe& pipe);


#endif