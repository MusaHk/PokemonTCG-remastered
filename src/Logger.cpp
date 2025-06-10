//
// Created by User on 6/10/2025.
//
#include "Logger.h"

Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile) {
        throw std::runtime_error("Failed to open log file.");
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
