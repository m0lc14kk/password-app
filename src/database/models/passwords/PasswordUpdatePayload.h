#pragma once

#include <string>

struct PasswordUpdatePayload {
    std::string name;
    std::string password;
    std::string url;
    unsigned int securityPin;
};
