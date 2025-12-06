#pragma once

#include "AccountRole.h"
#include <string>

struct AccountUpdatePayload {
    std::string name;
    std::string securityPin;
    int avatarId;
    AccountRole role;
};
