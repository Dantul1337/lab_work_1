#include <string>

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

int main(){
    return 0;
}