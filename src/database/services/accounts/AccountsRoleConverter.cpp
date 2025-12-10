#include "AccountsRoleConverter.h"
#include <stdexcept>

AccountRole AccountsRoleConverter::toAccountRole(int role) {
    switch (role) {
    case 0:
        return AccountRole::USER;
    case 1:
        return AccountRole::ADMIN;
    default:
        throw std::invalid_argument("Invalid identifier of a role.");
    }
}

int AccountsRoleConverter::toDatabaseRole(AccountRole role) {
    switch (role) {
    case AccountRole::USER:
        return 0;
    case AccountRole::ADMIN:
        return 1;
    default:
        throw std::invalid_argument("Invalid identifier of a role.");
    }
}
