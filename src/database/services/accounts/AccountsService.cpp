#include "AccountsService.h"
#include "../../DatabaseManager.h"
#include <vector>

std::vector<Account> AccountsService::getAllAccounts() {
    std::vector<Account> accounts;
    sqlite3* database = DatabaseManager::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, "SELECT * FROM accounts", -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Account account;
        const unsigned char* idText = sqlite3_column_text(stmt, 0);
        const unsigned char* nameText = sqlite3_column_text(stmt, 1);
        const unsigned char* pinText = sqlite3_column_text(stmt, 2);

        account.id = idText ? reinterpret_cast<const char*>(idText) : "";
        account.name = nameText ? reinterpret_cast<const char*>(nameText) : "";
        account.encryptedSecurityPin = pinText ? reinterpret_cast<const char*>(pinText) : "";
        account.avatarId = sqlite3_column_int(stmt, 3);

        accounts.push_back(account);
    }

    sqlite3_finalize(stmt);
    return accounts;
}

std::optional<Account> AccountsService::getAccountById(const std::string& id) {
    sqlite3* database = DatabaseManager::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, "SELECT * FROM accounts WHERE id = ?", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, id.c_str(), id.size(), SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Account account;
        const unsigned char* idText = sqlite3_column_text(stmt, 0);
        const unsigned char* nameText = sqlite3_column_text(stmt, 1);
        const unsigned char* pinText = sqlite3_column_text(stmt, 2);

        account.id = idText ? reinterpret_cast<const char*>(idText) : "";
        account.name = nameText ? reinterpret_cast<const char*>(nameText) : "";
        account.encryptedSecurityPin = pinText ? reinterpret_cast<const char*>(pinText) : "";
        account.avatarId = sqlite3_column_int(stmt, 3);
        sqlite3_finalize(stmt);
        return account;
    }

    sqlite3_finalize(stmt);
    return std::nullopt;
}

std::optional<Account> AccountsService::createAccount(const AccountCreatePayload& payload) {
    for (int i = 0; i < AccountsService::MAX_CREATION_ATTEMPTS; i++) {
    }

    return std::nullopt;
}

std::optional<Account> AccountsService::updateAccount(const AccountUpdatePayload& payload) {
    return std::nullopt;
}

bool AccountsService::deleteAccount(const std::string& id) {
    return false;
}
