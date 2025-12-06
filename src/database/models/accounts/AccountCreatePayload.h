#pragma once

#include "AccountRole.h"
#include <string>

struct AccountCreatePayload {
    std::string name;
    std::string securityPin;
    int avatarId;
    AccountRole role;
};
