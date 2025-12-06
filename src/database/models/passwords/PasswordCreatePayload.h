#pragma once

#include <string>

struct PasswordCreatePayload {
    std::string name;
    std::string password;
    std::string url;
    unsigned int securityPin;
};
