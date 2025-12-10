#pragma once

#include "../../models/accounts/AccountRole.h"

class AccountsRoleConverter {
public:
    ~AccountsRoleConverter() = default;

    static AccountRole toAccountRole(int role);
    static int toDatabaseRole(AccountRole role);
};
