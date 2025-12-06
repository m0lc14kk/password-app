#pragma once

#include "AccountRole.h"
#include <string>

struct RawAccount {
    std::string id;
    std::string name;
    std::string encryptedSecurityPin;
    int avatarId;
    AccountRole role;
};
