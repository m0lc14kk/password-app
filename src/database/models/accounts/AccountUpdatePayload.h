#pragma once

#include <string>

struct AccountUpdatePayload {
    std::string name;
    std::string securityPin;
    int avatarId;
};
