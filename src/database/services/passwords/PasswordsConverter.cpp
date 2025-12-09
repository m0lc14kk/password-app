#include "PasswordsConverter.h"
#include "../../../globals/managers/security/EncryptionManager.h"

RawPassword PasswordsConverter::convertToRawPassword(const Password& password) {
    RawPassword rawPassword;
    rawPassword.id = password.id;
    rawPassword.accountId = password.accountId;
    rawPassword.title = password.title;
    rawPassword.url = password.url;
    rawPassword.encryptedPassword = EncryptionManager::encrypt(password.password);
    rawPassword.encryptedSecurityPin =
        EncryptionManager::encrypt(std::to_string(password.securityPin));
    return rawPassword;
}

Password PasswordsConverter::convertToPassword(const RawPassword& rawPassword) {
    Password password;
    password.id = rawPassword.id;
    password.accountId = rawPassword.accountId;
    password.title = rawPassword.title;
    password.url = rawPassword.url;
    password.password = EncryptionManager::decrypt(rawPassword.encryptedPassword);
    password.securityPin = std::stoi(EncryptionManager::decrypt(rawPassword.encryptedSecurityPin));
    return password;
}
