#pragma once

#include <string>

struct RawAccount {
    std::string id;
    std::string name;
    std::string encryptedSecurityPin;
    int avatarId;
};
