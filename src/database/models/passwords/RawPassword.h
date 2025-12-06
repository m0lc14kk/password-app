#pragma once

#include <string>

struct RawPassword {
    std::string id;
    std::string accountId;
    std::string name;
    std::string encryptedPassword;
    std::string encryptedSecurityPin;
    std::string url;
};
