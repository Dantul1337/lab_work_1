#ifndef STORAGE_H
#define STORAGE_H

#include <string>

#include "pipe.h"
#include "compressor_station.h"

bool saveToFile(const std::string &filename, const Pipe *pipe,
                const CompressorStation *station);

bool loadFromFile(const std::string &filename, Pipe &pipe, bool &hasPipe,
                  CompressorStation &station, bool &hasStation);

#endif