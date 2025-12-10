#include "PasswordsService.h"
#include "../../../globals/managers/data/UUIDManager.h"
#include "../../../globals/managers/security/EncryptionManager.h"
#include "../../DatabaseManager.h"
#include <sqlite3.h>

std::optional<RawPassword> PasswordsService::getPasswordById(const std::string& id) {
    sqlite3* database = DatabaseManager::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, "SELECT * FROM passwords WHERE id = ?", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, id.c_str(), id.size(), SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        RawPassword password;
        password.id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        password.accountId = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        password.title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        password.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        password.url = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        password.encryptedPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        password.encryptedSecurityPin = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        return password;
    }

    sqlite3_finalize(stmt);
    return std::nullopt;
}

std::vector<RawPassword> PasswordsService::getPasswordsByAccountId(const std::string& accountId) {
    std::vector<RawPassword> passwords;
    sqlite3* database = DatabaseManager::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, "SELECT * FROM passwords WHERE accountId = ?", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, accountId.c_str(), accountId.size(), SQLITE_STATIC);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        RawPassword password;
        password.id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        password.accountId = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        password.title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        password.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        password.url = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        password.encryptedPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        password.encryptedSecurityPin = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        passwords.push_back(password);
    }

    sqlite3_finalize(stmt);
    return passwords;
}

std::optional<Password> PasswordsService::createPassword(const PasswordCreatePayload& payload) {
    for (int i = 0; i < PasswordsService::MAX_CREATION_ATTEMPTS; i++) {
        const std::string id = UUIDManager::generateUUID();
        if (PasswordsService::getPasswordById(id) != std::nullopt)
            continue;

        const std::string encryptedPassword = EncryptionManager::encrypt(payload.password);
        const std::string encryptedSecurityPin =
            EncryptionManager::encrypt(std::to_string(payload.securityPin));

        sqlite3* database = DatabaseManager::getInstance()->getDatabase();
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(database,
                           "INSERT INTO passwords (id, accountId, title, username, url, "
                           "encryptedPassword, encryptedSecurityPin) VALUES (?, ?, ?, ?, ?, ?, ?)",
                           -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, id.c_str(), id.size(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, payload.accountId.c_str(), payload.accountId.size(),
                          SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, payload.title.c_str(), payload.title.size(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, payload.username.c_str(), payload.username.size(),
                          SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, payload.url.c_str(), payload.url.size(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, encryptedPassword.c_str(), encryptedPassword.size(),
                          SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, encryptedSecurityPin.c_str(), encryptedSecurityPin.size(),
                          SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        Password password = {
            .id = id,
            .accountId = payload.accountId,
            .title = payload.title,
            .username = payload.username,
            .password = payload.password,
            .url = payload.url,
            .securityPin = payload.securityPin,
        };

        return password;
    }

    return std::nullopt;
}

std::optional<Password> PasswordsService::updatePassword(const std::string& id,
                                                         const PasswordUpdatePayload& payload) {
    const std::optional<RawPassword> rawPassword = PasswordsService::getPasswordById(id);
    if (rawPassword == std::nullopt)
        return std::nullopt;

    const std::string encryptedPassword = EncryptionManager::encrypt(payload.password);
    const std::string encryptedSecurityPin =
        EncryptionManager::encrypt(std::to_string(payload.securityPin));

    sqlite3* database = DatabaseManager::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database,
                       "UPDATE passwords SET title = ?, username = ?, url = ?, encryptedPassword = "
                       "?, encryptedSecurityPin = ? WHERE id = ?",
                       -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, payload.title.c_str(), payload.title.size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, payload.username.c_str(), payload.username.size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, payload.url.c_str(), payload.url.size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, encryptedPassword.c_str(), encryptedPassword.size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, encryptedSecurityPin.c_str(), encryptedSecurityPin.size(),
                      SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, id.c_str(), id.size(), SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    Password password = {
        .id = id,
        .accountId = payload.accountId,
        .title = payload.title,
        .username = payload.username,
        .password = payload.password,
        .url = payload.url,
        .securityPin = payload.securityPin,
    };

    return password;
    return std::nullopt;
}

bool PasswordsService::deletePassword(const std::string& id) {
    const std::optional<RawPassword> rawPassword = PasswordsService::getPasswordById(id);
    if (rawPassword == std::nullopt)
        return false;

    sqlite3* database = DatabaseManager::getInstance()->getDatabase();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database, "DELETE FROM passwords WHERE id = ?", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, id.c_str(), id.size(), SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return true;
}

bool PasswordsService::deletePasswordsByAccountId(const std::string& accountId) {
    const std::vector<RawPassword> passwords = PasswordsService::getPasswordsByAccountId(accountId);
    for (const RawPassword& password : passwords) {
        if (!PasswordsService::deletePassword(password.id))
            return false;
    }

    return true;
}
