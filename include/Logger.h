//
// Created by User on 6/10/2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include "String.h"

class Logger {
private:
    std::ofstream logFile;
public:
    Logger(const std::string& filename = "docs/logs.txt");
    ~Logger();

    template<typename T>
    void logEvent(const T& message) {
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }
};
#endif //LOGGER_H