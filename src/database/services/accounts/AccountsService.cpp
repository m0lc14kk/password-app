#include "AccountsService.h"
#include "../../../globals/managers/data/UUIDManager.h"
#include "../../../globals/managers/security/EncryptionManager.h"
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
        account.securityPin =
            pinText ? EncryptionManager::decrypt(reinterpret_cast<const char*>(pinText)) : "";
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
        account.securityPin =
            pinText ? EncryptionManager::decrypt(reinterpret_cast<const char*>(pinText)) : "";
        account.avatarId = sqlite3_column_int(stmt, 3);
        sqlite3_finalize(stmt);
        return account;
    }

    sqlite3_finalize(stmt);
    return std::nullopt;
}

std::optional<Account> AccountsService::createAccount(const AccountCreatePayload& payload) {
    for (int i = 0; i < AccountsService::MAX_CREATION_ATTEMPTS; i++) {
        const std::string id = UUIDManager::generateUUID();
        if (this->getAccountById(id) != std::nullopt)
            continue;

        const std::string encryptedSecurityPin = EncryptionManager::encrypt(payload.securityPin);

        sqlite3* database = DatabaseManager::getInstance()->getDatabase();
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(
            database,
            "INSERT INTO accounts (id, name, encryptedSecurityPin, avatarId) VALUES (?, ?, ?, ?)",
            -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, id.c_str(), id.size(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, payload.name.c_str(), payload.name.size(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, encryptedSecurityPin.c_str(), encryptedSecurityPin.size(),
                          SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, payload.avatarId);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        Account account = {
            .id = id,
            .name = payload.name,
            .securityPin = payload.securityPin,
            .avatarId = payload.avatarId,
        };

        return account;
    }

    return std::nullopt;
}

std::optional<Account> AccountsService::updateAccount(const std::string& id,
                                                      const AccountUpdatePayload& payload) {
    if (this->getAccountById(id) == std::nullopt)
        return std::nullopt;

    const std::string encryptedSecurityPin = EncryptionManager::encrypt(payload.securityPin);

    sqlite3* database = DatabaseManager::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database,
                       "UPDATE accounts SET name = ?, securityPin = ?, avatarId = ? WHERE id = ?",
                       -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, payload.name.c_str(), payload.name.size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, encryptedSecurityPin.c_str(), encryptedSecurityPin.size(),
                      SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, payload.avatarId);
    sqlite3_bind_text(stmt, 4, id.c_str(), id.size(), SQLITE_STATIC);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    Account account = {
        .id = id,
        .name = payload.name,
        .securityPin = payload.securityPin,
        .avatarId = payload.avatarId,
    };

    return account;
}

bool AccountsService::deleteAccount(const std::string& id) {
    if (this->getAccountById(id) == std::nullopt)
        return false;

    sqlite3* database = DatabaseManager::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, "DELETE FROM accounts WHERE id = ?", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, id.c_str(), id.size(), SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return true;
}
