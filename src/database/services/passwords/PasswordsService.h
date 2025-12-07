#pragma once

#include "../../models/passwords/Password.h"
#include "../../models/passwords/PasswordCreatePayload.h"
#include "../../models/passwords/PasswordUpdatePayload.h"
#include "../../models/passwords/RawPassword.h"
#include "../base/BaseDatabaseService.h"
#include <optional>
#include <string>
#include <vector>

class PasswordsService : public BaseDatabaseService {
public:
    ~PasswordsService() = default;

    static std::optional<RawPassword> getPasswordById(const std::string& id);
    static std::vector<RawPassword> getPasswordsByAccountId(const std::string& accountId);
    static std::optional<Password> createPassword(const PasswordCreatePayload& payload);
    static std::optional<Password> updatePassword(const std::string& id,
                                                  const PasswordUpdatePayload& payload);
    static bool deletePassword(const std::string& id);
    static bool deletePasswordsByAccountId(const std::string& accountId);
};
