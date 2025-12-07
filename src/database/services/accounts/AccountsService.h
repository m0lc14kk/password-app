#pragma once

#include "../../models/accounts/Account.h"
#include "../../models/accounts/AccountCreatePayload.h"
#include "../../models/accounts/AccountUpdatePayload.h"
#include "../base/BaseDatabaseService.h"
#include <optional>
#include <string>
#include <vector>

class AccountsService : public BaseDatabaseService {
public:
    ~AccountsService() = default;

    static std::vector<Account> getAllAccounts();
    static std::optional<Account> getAccountById(const std::string& id);
    static std::optional<Account> createAccount(const AccountCreatePayload& payload);
    static std::optional<Account> updateAccount(const std::string& id,
                                                const AccountUpdatePayload& payload);
    static bool deleteAccount(const std::string& id);
};
