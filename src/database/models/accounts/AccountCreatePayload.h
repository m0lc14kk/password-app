#pragma once

#include <string>

struct AccountCreatePayload {
    std::string name;
    std::string securityPin;
    int avatarId;
};
