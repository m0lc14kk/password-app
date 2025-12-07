#pragma once

#include <string>

struct Password {
    std::string id;
    std::string accountId;
    std::string title;
    std::string username;
    std::string password;
    std::string url;
    unsigned int securityPin;
};
