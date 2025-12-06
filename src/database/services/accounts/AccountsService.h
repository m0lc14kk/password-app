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

    std::vector<Account> getAllAccounts();
    std::optional<Account> getAccountById(const std::string& id);
    std::optional<Account> createAccount(const AccountCreatePayload& payload);
    std::optional<Account> updateAccount(const std::string& id,
                                         const AccountUpdatePayload& payload);
    bool deleteAccount(const std::string& id);
};
