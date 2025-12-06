#pragma once

#include "AccountRole.h"
#include <string>

struct Account {
    std::string id;
    std::string name;
    std::string securityPin;
    int avatarId;
    AccountRole role;
};
