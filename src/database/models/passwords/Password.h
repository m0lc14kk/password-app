#pragma once

#include <string>

struct Password {
    std::string id;
    std::string accountId;
    std::string name;
    std::string password;
    std::string url;
    unsigned int securityPin;
};
