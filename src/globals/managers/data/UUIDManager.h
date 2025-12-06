#pragma once

#include <random>
#include <regex>
#include <sstream>
#include <string>

class UUIDManager {
private:
    UUIDManager();
    ~UUIDManager();
    static const std::regex UUID_REGEX;
    static std::random_device randomDevice;
    static std::mt19937 randomGenerator;
    static std::uniform_int_distribution<> randomDistribution;
    static std::uniform_int_distribution<> randomDistributionSecond;

public:
    static std::string generateUUID();
    bool isUUID(const std::string& uuid);
};
