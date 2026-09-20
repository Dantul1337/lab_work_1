#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <string>

std::string readNonEmptyLine(const std::string& prompt);

int readInt(const std::string& prompt, int minValue, int maxValue);
double readDouble(const std::string& prompt, double minValue, double maxValue);
bool readYesNo(const std::string& prompt);

void clearInputStream();

#endif