#pragma once

#include <string>

struct Account {
    std::string id;
    std::string name;
    std::string encryptedSecurityPin;
    int avatarId;
};
