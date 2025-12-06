#include "UUIDManager.h"

const std::regex UUIDManager::UUID_REGEX(
    "^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-4[0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$");
std::random_device UUIDManager::randomDevice;
std::mt19937 UUIDManager::randomGenerator(UUIDManager::randomDevice());
std::uniform_int_distribution<> UUIDManager::randomDistribution(0, 15);
std::uniform_int_distribution<> UUIDManager::randomDistributionSecond(8, 11);
UUIDManager::UUIDManager() {}
UUIDManager::~UUIDManager() {}

std::string UUIDManager::generateUUID() {
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << std::hex << UUIDManager::randomDistribution(UUIDManager::randomGenerator);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << std::hex << UUIDManager::randomDistribution(UUIDManager::randomGenerator);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << std::hex << UUIDManager::randomDistribution(UUIDManager::randomGenerator);
    }
    ss << "-";
    ss << std::hex << UUIDManager::randomDistributionSecond(UUIDManager::randomGenerator);
    for (i = 0; i < 3; i++) {
        ss << std::hex << UUIDManager::randomDistribution(UUIDManager::randomGenerator);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << std::hex << UUIDManager::randomDistribution(UUIDManager::randomGenerator);
    }

    return ss.str();
}

bool UUIDManager::isUUID(const std::string& uuid) {
    return std::regex_match(uuid, UUIDManager::UUID_REGEX);
}
