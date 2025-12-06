#pragma once

#include <string>

struct AccountUpdatePayload {
    std::string name;
    std::string encryptedSecurityPin;
    int avatarId;
};
