#pragma once

#include <string>

struct RawPassword {
    std::string id;
    std::string accountId;
    std::string title;
    std::string username;
    std::string url;
    std::string encryptedPassword;
    std::string encryptedSecurityPin;
};
