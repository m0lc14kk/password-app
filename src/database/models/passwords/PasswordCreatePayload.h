#pragma once

#include <string>

struct PasswordCreatePayload {
    std::string accountId;
    std::string title;
    std::string username;
    std::string url;
    std::string password;
    unsigned int securityPin;
};
