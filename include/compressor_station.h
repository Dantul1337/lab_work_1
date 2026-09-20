#ifndef COMPRESSOR_STATION_H
#define COMPRESSOR_STATION_H

#include <string>

struct CompressorStation {
    std::string name;
    int totalShops = 0;
    int shopsInOperation = 0;
    int stationClass = 0;
};

CompressorStation inputCompressorStation();

void printCompressorStation(const CompressorStation& station);
void startShop(CompressorStation& station);
void stopShop(CompressorStation& station);

#endif