#pragma once

#include <string>

struct PasswordUpdatePayload {
    std::string accountId;
    std::string title;
    std::string username;
    std::string url;
    std::string password;
    unsigned int securityPin;
};
